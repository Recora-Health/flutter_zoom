import Foundation
import UIKit
import MobileRTC

/// Bridges Zoom 7.0.5's meeting-window orientation to the host app.
///
/// Zoom 6.6.9 owned its own `UIWindow` and controlled rotation autonomously. In 7.0.5 the
/// SDK presents inside the host's window/scene (see `setMobileRTCPresentationScene`), so
/// the meeting UI inherits the host's `supportedInterfaceOrientations`. Host apps that
/// lock Flutter screens to portrait now also pin the meeting UI.
///
/// Usage in host AppDelegate:
///
///     override func application(
///       _ application: UIApplication,
///       supportedInterfaceOrientationsFor window: UIWindow?
///     ) -> UIInterfaceOrientationMask {
///       if ZoomOrientationGate.shared.isInMeeting { return .allButUpsideDown }
///       // …existing portrait-lock logic…
///     }
///
/// The plugin flips `isInMeeting` from `onMeetingStateChange` and forces a rotation
/// re-query via UIKit so iOS picks up the new mask without waiting for the next user
/// gesture.
@objc(ZoomOrientationGate) public class ZoomOrientationGate: NSObject {
    @objc public static let shared = ZoomOrientationGate()

    @objc public private(set) var isInMeeting: Bool = false

    @objc public func setInMeeting(_ value: Bool) {
        guard value != isInMeeting else { return }
        isInMeeting = value
        DispatchQueue.main.async { Self.refreshSupportedOrientations() }
    }

    private static func refreshSupportedOrientations() {
        if #available(iOS 16.0, *) {
            for scene in UIApplication.shared.connectedScenes {
                guard let windowScene = scene as? UIWindowScene else { continue }
                for window in windowScene.windows {
                    window.rootViewController?.setNeedsUpdateOfSupportedInterfaceOrientations()
                }
            }
        } else {
            UIViewController.attemptRotationToDeviceOrientation()
        }
    }
}

/// Forwards UIKit rotation events from the host's `FlutterViewController` into MobileRTC.
///
/// The Zoom 7.0.5 SDK relies on the host to relay `viewWillTransitionToSize:` and
/// `willTransitionToTraitCollection:` so its in-meeting layout can adapt (see
/// `MobileRTC.h` lines ~340–355). Without these calls the SDK may keep its prior layout
/// even after the window rotates. We swizzle once at plugin registration so the host
/// doesn't have to subclass `FlutterViewController`.
@objc public class ZoomRotationForwarding: NSObject {
    @objc public static func install() {
        DispatchQueue.once(token: "zoom.rotation.forwarding") {
            swizzle(
                #selector(UIViewController.viewWillTransition(to:with:)),
                with: #selector(UIViewController.zoom_viewWillTransition(to:with:))
            )
            swizzle(
                #selector(UIViewController.willTransition(to:with:)),
                with: #selector(UIViewController.zoom_willTransition(to:with:))
            )
        }
    }

    private static func swizzle(_ original: Selector, with replacement: Selector) {
        let cls: AnyClass = UIViewController.self
        guard
            let originalMethod = class_getInstanceMethod(cls, original),
            let swizzledMethod = class_getInstanceMethod(cls, replacement)
        else { return }
        method_exchangeImplementations(originalMethod, swizzledMethod)
    }
}

extension UIViewController {
    @objc fileprivate func zoom_viewWillTransition(
        to size: CGSize,
        with coordinator: UIViewControllerTransitionCoordinator
    ) {
        // After swizzling this call dispatches to the ORIGINAL implementation.
        self.zoom_viewWillTransition(to: size, with: coordinator)
        guard ZoomOrientationGate.shared.isInMeeting,
              self.zoom_isWindowRoot else { return }
        MobileRTC.shared()?.viewWillTransition(toSize: size, withTransitionCoordinator: coordinator)
    }

    @objc fileprivate func zoom_willTransition(
        to newCollection: UITraitCollection,
        with coordinator: UIViewControllerTransitionCoordinator
    ) {
        self.zoom_willTransition(to: newCollection, with: coordinator)
        guard ZoomOrientationGate.shared.isInMeeting,
              self.zoom_isWindowRoot else { return }
        MobileRTC.shared()?.willTransition(toTraitCollection: newCollection, withTransitionCoordinator: coordinator)
    }

    /// Only forward when *this* VC is the window's rootViewController — the SDK headers
    /// document forwarding from that point, and gating here avoids double-firing when
    /// presented children also receive the same UIKit transition events.
    fileprivate var zoom_isWindowRoot: Bool {
        guard let window = self.view.window else { return false }
        return window.rootViewController === self
    }
}

private extension DispatchQueue {
    private static var onceTokens: Set<String> = []
    private static let onceQueue = DispatchQueue(label: "zoom.dispatch.once")

    static func once(token: String, block: () -> Void) {
        onceQueue.sync {
            guard !onceTokens.contains(token) else { return }
            onceTokens.insert(token)
            block()
        }
    }
}
