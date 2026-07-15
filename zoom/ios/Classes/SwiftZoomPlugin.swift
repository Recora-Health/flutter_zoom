import Flutter
import UIKit
import MobileRTC

@objc(SwiftZoomPlugin) public class SwiftZoomPlugin: NSObject, FlutterPlugin,FlutterStreamHandler , MobileRTCMeetingServiceDelegate{
  struct MeetingViewOptions { 
    static let NO_BUTTON_AUDIO = 2
    static let NO_BUTTON_LEAVE = 128
    static let NO_BUTTON_MORE = 16
    static let NO_BUTTON_PARTICIPANTS = 8
    static let NO_BUTTON_SHARE = 4
    static let NO_BUTTON_SWITCH_AUDIO_SOURCE = 512
    static let NO_BUTTON_SWITCH_CAMERA = 256
    static let NO_BUTTON_VIDEO = 1
    static let NO_TEXT_MEETING_ID = 32
    static let NO_TEXT_PASSWORD = 64
  }

  var authenticationDelegate: AuthenticationDelegate
  var eventSink: FlutterEventSink?
  var qualitySink: FlutterEventSink?
  public static func register(with registrar: FlutterPluginRegistrar) {
    let messenger = registrar.messenger()
    let channel = FlutterMethodChannel(name: "plugins.webcare/zoom_channel", binaryMessenger: messenger)
    let instance = SwiftZoomPlugin()
    registrar.addMethodCallDelegate(instance, channel: channel)

    let eventChannel = FlutterEventChannel(name: "plugins.webcare/zoom_event_stream", binaryMessenger: messenger)
    eventChannel.setStreamHandler(instance)

    // In-meeting network quality events (onUserNetworkStatusChanged), kept on a
    // separate channel so the status stream's [status, message] shape is untouched.
    let qualityChannel = FlutterEventChannel(name: "plugins.webcare/zoom_quality_stream", binaryMessenger: messenger)
    qualityChannel.setStreamHandler(ZoomQualityStreamHandler(plugin: instance))

    // Forward UIKit rotation events to MobileRTC during meetings (see ZoomOrientationGate).
    ZoomRotationForwarding.install()
  }

  override init(){
    authenticationDelegate = AuthenticationDelegate()
  }


 
  public func handle(_ call: FlutterMethodCall, result: @escaping FlutterResult) {
        switch call.method {
        case "init":
            self.initZoom(call: call, result: result)
        case "join":
            self.joinMeeting(call: call, result: result)
        case "start":
            self.startMeeting(call: call, result: result)
        case "meeting_status":
            self.meetingStatus(call: call, result: result)
        case "leave":
            self.leaveMeeting(call: call, result: result)
        default:
            result(FlutterMethodNotImplemented)
        }
  }

    
    public func onMethodCall(call: FlutterMethodCall, result: @escaping FlutterResult) {
        
        switch call.method {
        case "init":
            self.initZoom(call: call, result: result)
        case "join":
            self.joinMeeting(call: call, result: result)
        case "start":
            self.startMeeting(call: call, result: result)
        case "meeting_status":
            self.meetingStatus(call: call, result: result)
         case "leave":
            self.leaveMeeting(call: call, result: result)
        default:
            result(FlutterMethodNotImplemented)
        }
    }
    
    public func initZoom(call: FlutterMethodCall, result: @escaping FlutterResult)  {
        
        let pluginBundle = Bundle(for: type(of: self))
        let pluginBundlePath = pluginBundle.bundlePath
        let arguments = call.arguments as! Dictionary<String, String>
        
        let context = MobileRTCSDKInitContext()
        context.domain = arguments["domain"]!
        context.enableLog = true
        context.bundleResPath = pluginBundlePath
        MobileRTC.shared().initialize(context)

        // Clear any persisted "Always show this preview when joining" preference.
        // The SDK's default-UI green room writes that checkbox to UserDefaults and
        // reads it back on launch, which can override disableShowVideoPreview(...)
        // and make the preview stick across restarts (reproducible on BrowserStack,
        // where keychain/defaults state is unreliable).
        clearPersistedVideoPreviewPreference()

        // Set up root navigation controller for Zoom UI mode
        if let window = UIApplication.shared.windows.first(where: { $0.isKeyWindow }),
           let rootViewController = window.rootViewController {

            // Check if root is already a navigation controller
            if let navController = rootViewController as? UINavigationController {
                MobileRTC.shared().setMobileRTCRootController(navController)
                print("ZoomPlugin: Root navigation controller set")
            } else {
                // Try to find a navigation controller in the hierarchy
                if let navController = findNavigationController(in: rootViewController) {
                    MobileRTC.shared().setMobileRTCRootController(navController)
                    print("ZoomPlugin: Found and set navigation controller from hierarchy")
                } else {
                    // No nav controller found - acceptable, Zoom will use its own window
                    print("ZoomPlugin: No UINavigationController found, Zoom will use its own window")
                }
            }
        } else {
            print("ZoomPlugin: Could not access window or root controller")
        }

        let auth = MobileRTC.shared().getAuthService()
        auth?.delegate = self.authenticationDelegate.onAuth(result)
        if let jwtToken = arguments["jwtToken"] {
            auth?.jwtToken = jwtToken
        }
        
        auth?.sdkAuth()
    }
    
    // Remove the persisted video-preview-when-joining preference from UserDefaults
    // so a previously-checked "Always show this preview when joining" box can't keep
    // forcing the green room after the user (or our API call) has disabled it.
    private func clearPersistedVideoPreviewPreference() {
        let defaults = UserDefaults.standard
        for key in defaults.dictionaryRepresentation().keys {
            let lower = key.lowercased()
            if lower.contains("preview") && (lower.contains("video") || lower.contains("join")) {
                defaults.removeObject(forKey: key)
            }
        }
        defaults.synchronize()
    }

    public func meetingStatus(call: FlutterMethodCall, result: FlutterResult) {
        
        let meetingService = MobileRTC.shared().getMeetingService()
        if meetingService != nil {
            
            let meetingState = meetingService?.getMeetingState()
            result(getStateMessage(meetingState))
        } else {
            result(["MEETING_STATUS_UNKNOWN", ""])
        }
    }

    public func leaveMeeting(call: FlutterMethodCall, result: FlutterResult) {
        
        let meetingService = MobileRTC.shared().getMeetingService()
        if meetingService != nil {
            meetingService?.leaveMeeting(with: LeaveMeetingCmd.leave)
            result(true)
        } else {
            result(false)
        }
    }
    
    public func joinMeeting(call: FlutterMethodCall, result: FlutterResult) {
        
        let meetingService = MobileRTC.shared().getMeetingService()
        let meetingSettings = MobileRTC.shared().getMeetingSettings()
        
        if meetingService != nil {
            
            let arguments = call.arguments as! Dictionary<String, String?>
            
            meetingSettings?.disableDriveMode(parseBoolean(data: arguments["disableDrive"]!, defaultValue: false))
            meetingSettings?.disableCall(in: parseBoolean(data: arguments["disableDialIn"]!, defaultValue: false))
            meetingSettings?.setAutoConnectInternetAudio(true)
            meetingSettings?.disableShowVideoPreview(whenJoinMeeting: true)
            meetingSettings?.setMuteAudioWhenJoinMeeting(parseBoolean(data: arguments["noAudio"]!, defaultValue: false))
            meetingSettings?.meetingShareHidden = parseBoolean(data: arguments["disableShare"]!, defaultValue: false)
            meetingSettings?.meetingInviteHidden = parseBoolean(data: arguments["disableDrive"]!, defaultValue: false)

            if  arguments["meetingViewOptions"] != nil{
                let meetingViewOptions = parseInt(data: arguments["meetingViewOptions"]!, defaultValue: 0)
                if (meetingViewOptions & MeetingViewOptions.NO_BUTTON_AUDIO) != 0 {
                    meetingSettings?.meetingAudioHidden = true
                }
                if (meetingViewOptions & MeetingViewOptions.NO_BUTTON_LEAVE) != 0 {
                    meetingSettings?.meetingLeaveHidden = true
                }
                if (meetingViewOptions & MeetingViewOptions.NO_BUTTON_MORE) != 0 {
                    meetingSettings?.meetingMoreHidden = true
                }
                if (meetingViewOptions & MeetingViewOptions.NO_BUTTON_PARTICIPANTS) != 0 {
                    meetingSettings?.meetingParticipantHidden = true
                }
                if (meetingViewOptions & MeetingViewOptions.NO_BUTTON_SWITCH_AUDIO_SOURCE) != 0 {
                   
                }
                if (meetingViewOptions & MeetingViewOptions.NO_BUTTON_SWITCH_CAMERA) != 0 {
                    
                }
                if (meetingViewOptions & MeetingViewOptions.NO_BUTTON_VIDEO) != 0 {
                    meetingSettings?.meetingVideoHidden = true
                }
                if (meetingViewOptions & MeetingViewOptions.NO_TEXT_MEETING_ID) != 0 {
                    meetingSettings?.meetingTitleHidden = true
                }
                if (meetingViewOptions & MeetingViewOptions.NO_TEXT_PASSWORD) != 0 {
                    meetingSettings?.meetingPasswordHidden = true
                }
            }
            let joinMeetingParameters = MobileRTCMeetingJoinParam()
            joinMeetingParameters.userName = arguments["userId"]!!
            joinMeetingParameters.meetingNumber = arguments["meetingId"]!!
            joinMeetingParameters.password = arguments["meetingPassword"]!!
            joinMeetingParameters.webinarToken = arguments["webToken"]!!
            joinMeetingParameters.noAudio = parseBoolean(data: arguments["noAudio"]!, defaultValue: false)
            joinMeetingParameters.noVideo = parseBoolean(data: arguments["noVideo"]!, defaultValue: false)

            let response = meetingService?.joinMeeting(with: joinMeetingParameters)

            meetingService?.showMeetingControlBar()

            if let response = response {
                print("Got response from join: \(response)")
            }
            result(true)
        } else {
            result(false)
        }
    }

    public func startMeeting(call: FlutterMethodCall, result: FlutterResult) {
        
        let meetingService = MobileRTC.shared().getMeetingService()
        let meetingSettings = MobileRTC.shared().getMeetingSettings()
        
        if meetingService != nil {
            
            let arguments = call.arguments as! Dictionary<String, String?>
            
            meetingSettings?.disableDriveMode(parseBoolean(data: arguments["disableDrive"]!, defaultValue: false))
            meetingSettings?.disableCall(in: parseBoolean(data: arguments["disableDialIn"]!, defaultValue: false))
            meetingSettings?.setAutoConnectInternetAudio(parseBoolean(data: arguments["noDisconnectAudio"]!, defaultValue: false))
            meetingSettings?.setMuteAudioWhenJoinMeeting(parseBoolean(data: arguments["noAudio"]!, defaultValue: false))
            meetingSettings?.meetingShareHidden = parseBoolean(data: arguments["disableShare"]!, defaultValue: false)
            meetingSettings?.meetingInviteHidden = parseBoolean(data: arguments["disableDrive"]!, defaultValue: false)
            if  arguments["meetingViewOptions"] != nil{
                let meetingViewOptions = parseInt(data: arguments["meetingViewOptions"]!, defaultValue: 0)   
                if (meetingViewOptions & MeetingViewOptions.NO_BUTTON_AUDIO) != 0 {
                    meetingSettings?.meetingAudioHidden = true
                }
                if (meetingViewOptions & MeetingViewOptions.NO_BUTTON_LEAVE) != 0 {
                    meetingSettings?.meetingLeaveHidden = true
                }
                if (meetingViewOptions & MeetingViewOptions.NO_BUTTON_MORE) != 0 {
                    meetingSettings?.meetingMoreHidden = true
                }
                if (meetingViewOptions & MeetingViewOptions.NO_BUTTON_PARTICIPANTS) != 0 {
                    meetingSettings?.meetingParticipantHidden = true
                }
                if (meetingViewOptions & MeetingViewOptions.NO_BUTTON_SWITCH_AUDIO_SOURCE) != 0 {
                   
                }
                if (meetingViewOptions & MeetingViewOptions.NO_BUTTON_SWITCH_CAMERA) != 0 {
                    
                }
                if (meetingViewOptions & MeetingViewOptions.NO_BUTTON_VIDEO) != 0 {
                    meetingSettings?.meetingVideoHidden = true
                }
                if (meetingViewOptions & MeetingViewOptions.NO_TEXT_MEETING_ID) != 0 {
                    meetingSettings?.meetingTitleHidden = true
                }
                if (meetingViewOptions & MeetingViewOptions.NO_TEXT_PASSWORD) != 0 {
                    meetingSettings?.meetingPasswordHidden = true
                }
            }
            let user: MobileRTCMeetingStartParam4WithoutLoginUser = MobileRTCMeetingStartParam4WithoutLoginUser.init()
            
            user.userType = .apiUser
            user.meetingNumber = arguments["meetingId"]!!
            user.userName = arguments["displayName"]!!
            user.zak = arguments["zoomAccessToken"]!!

            let param: MobileRTCMeetingStartParam = user
            
            let response = meetingService?.startMeeting(with: param)
            
            if let response = response {
                print("Got response from start: \(response)")
            }
            result(true)
        } else {
            result(false)
        }
    }
    
    private func parseBoolean(data: String?, defaultValue: Bool) -> Bool {
        var result: Bool
        
        if let unwrappeData = data {
            result = NSString(string: unwrappeData).boolValue
        } else {
            result = defaultValue
        }
        return result
    }
    
    private func parseInt(data: String?, defaultValue: Int) -> Int {
        var result: Int
        
        if let unwrappeData = data {
            result = NSString(string: unwrappeData).integerValue
        } else {
            result = defaultValue
        }
        return result
    }
    
    
    public func onMeetingError(_ error: MobileRTCMeetError, message: String?) {
        
    }
    
    public func getMeetErrorMessage(_ errorCode: MobileRTCMeetError) -> String {
        
        let message = "" 
        return message
    }
    
    public func onMeetingStateChange(_ state: MobileRTCMeetingState) {

        // Tell the host AppDelegate to allow landscape only while the Zoom UI is on-screen.
        switch state {
        case .inMeeting, .inWaitingRoom, .waitingForHost, .webinarPromote, .webinarDePromote:
            ZoomOrientationGate.shared.setInMeeting(true)
        case .idle, .ended, .failed, .disconnecting:
            ZoomOrientationGate.shared.setInMeeting(false)
        default:
            break
        }

        guard let eventSink = eventSink else {
            return
        }

        eventSink(getStateMessage(state))
    }

    public func onUserNetworkStatusChanged(_ type: MobileRTCComponentType, level: MobileRTCNetworkQuality, userID: UInt, uplink: Bool) {
        guard let qualitySink = qualitySink else {
            return
        }

        let event: [String: Any] = [
            "component": componentName(type),
            "quality": qualityName(level),
            "uplink": uplink,
            "userId": userID,
        ]

        if Thread.isMainThread {
            qualitySink(event)
        } else {
            DispatchQueue.main.async { qualitySink(event) }
        }
    }

    private func componentName(_ type: MobileRTCComponentType) -> String {
        // Match on raw values: the Swift importer's renaming of the all-caps
        // ObjC cases (MobileRTCComponentType_AUDIO/VIDEO/SHARE) is unreliable.
        switch type.rawValue {
        case 3:
            return "audio"
        case 4:
            return "video"
        case 5:
            return "share"
        default:
            return "default"
        }
    }

    private func qualityName(_ level: MobileRTCNetworkQuality) -> String {
        switch level {
        case .veryBad:
            return "verybad"
        case .bad:
            return "bad"
        case .notGood:
            return "notgood"
        case .normal:
            return "normal"
        case .good:
            return "good"
        case .excellent:
            return "excellent"
        default:
            return "unknown"
        }
    }

    public func onListen(withArguments arguments: Any?, eventSink events: @escaping FlutterEventSink) -> FlutterError? {
        self.eventSink = events
        
        let meetingService = MobileRTC.shared().getMeetingService()
        if meetingService == nil {
            return FlutterError(code: "Zoom SDK error", message: "ZoomSDK is not initialized", details: nil)
        }
        meetingService?.delegate = self
        
        return nil
    }
     
    public func onCancel(withArguments arguments: Any?) -> FlutterError? {
        eventSink = nil
        return nil
    }
    
    private func getStateMessage(_ state: MobileRTCMeetingState?) -> [String] {
        
        var message: [String]
        switch state {
        case  .idle:
            message = ["MEETING_STATUS_IDLE", "No meeting is running"]
            break
        case .connecting:
            message = ["MEETING_STATUS_CONNECTING", "Connect to the meeting server"]
            break
        case .inMeeting:
            message = ["MEETING_STATUS_INMEETING", "Meeting is ready and in process"]
            break
        case .webinarPromote:
            message = ["MEETING_STATUS_WEBINAR_PROMOTE", "Upgrade the attendees to panelist in webinar"]
            break
        case .webinarDePromote:
            message = ["MEETING_STATUS_WEBINAR_DEPROMOTE", "Demote the attendees from the panelist"]
            break
        case .disconnecting:
            message = ["MEETING_STATUS_DISCONNECTING", "Disconnect the meeting server, leave meeting status"]
            break;
        case .ended:
            message = ["MEETING_STATUS_ENDED", "Meeting ends"]
            break;
        case .failed:
            message = ["MEETING_STATUS_FAILED", "Failed to connect the meeting server"]
            break;
        case .reconnecting:
            message = ["MEETING_STATUS_RECONNECTING", "Reconnecting meeting server status"]
            break;
        case .waitingForHost:
            message = ["MEETING_STATUS_WAITINGFORHOST", "Waiting for the host to start the meeting"]
            break;
        case .inWaitingRoom:
            message = ["MEETING_STATUS_IN_WAITING_ROOM", "Participants who join the meeting before the start are in the waiting room"]
            break;
        default:
            message = ["MEETING_STATUS_UNKNOWN", "\(state?.rawValue ?? 9999)"]
        }
        
        return message
    }

    private func findNavigationController(in viewController: UIViewController) -> UINavigationController? {
        // Check if it's embedded in a navigation controller
        if let navController = viewController.navigationController {
            return navController
        }

        // Check children recursively
        for child in viewController.children {
            if let navController = child as? UINavigationController {
                return navController
            }
            if let found = findNavigationController(in: child) {
                return found
            }
        }

        return nil
    }
}


@objc(AuthenticationDelegate) public class AuthenticationDelegate: NSObject, MobileRTCAuthDelegate {
    
    private var result: FlutterResult?
    
    
    public func onAuth(_ result: FlutterResult?) -> AuthenticationDelegate {
        self.result = result
        return self
    }
    
    
    public func onMobileRTCAuthReturn(_ returnValue: MobileRTCAuthError) {

        if returnValue == .success {
            // Disable the pre-join video preview ("green room") as soon as auth
            // succeeds, while getMeetingSettings() is guaranteed non-nil. Doing it
            // only inside joinMeeting() races against SDK init: if settings is nil
            // there the call is a silent no-op, the preview appears with "Always
            // show this preview when joining" checked-by-default, and tapping Join
            // persists that preference so it sticks across app restarts.
            MobileRTC.shared().getMeetingSettings()?.disableShowVideoPreview(whenJoinMeeting: true)

            self.result?([0, 0])
        } else {
            self.result?([1, 0])
        }

        self.result = nil
    }
    
    public func onMobileRTCLoginReturn(_ returnValue: Int) {
        
    }
    
    public func onMobileRTCLogoutReturn(_ returnValue: Int) {
        
    }
    
    public func getAuthErrorMessage(_ errorCode: MobileRTCAuthError) -> String {
        
        let message = ""
         
        return message
    }
}

/// Stream handler for plugins.webcare/zoom_quality_stream. The plugin instance is
/// already the FlutterStreamHandler for the status channel, so the quality channel
/// needs its own handler; it just parks the sink on the plugin, whose
/// MobileRTCMeetingServiceDelegate implementation emits the events.
class ZoomQualityStreamHandler: NSObject, FlutterStreamHandler {
    private weak var plugin: SwiftZoomPlugin?

    init(plugin: SwiftZoomPlugin) {
        self.plugin = plugin
    }

    func onListen(withArguments arguments: Any?, eventSink events: @escaping FlutterEventSink) -> FlutterError? {
        plugin?.qualitySink = events
        // The delegate is normally set by the status channel's onListen; set it here
        // too so quality events don't depend on subscription order.
        MobileRTC.shared().getMeetingService()?.delegate = plugin
        return nil
    }

    func onCancel(withArguments arguments: Any?) -> FlutterError? {
        plugin?.qualitySink = nil
        return nil
    }
}
