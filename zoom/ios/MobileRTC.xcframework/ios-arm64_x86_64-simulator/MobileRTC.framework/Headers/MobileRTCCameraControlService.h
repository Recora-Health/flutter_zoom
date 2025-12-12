/**
 * @file MobileRTCCameraControlService.h
 * @brief Camera control and management service.
 */

#import <Foundation/Foundation.h>

/**
 * @brief Enumeration of camera control requests types.
 */
typedef NS_ENUM(NSInteger, MobileRTCCameraControlRequestType) {
    /** Request to take control of the camera. */
    MobileRTCCameraControlRequestType_RequestControl,
    /** Give up control of the camera. */
    MobileRTCWhiteboardStatus_GiveUpControl,
};

/**
 * @brief Enumeration of the results of a camera control request.
 */
typedef NS_ENUM(NSInteger, MobileRTCCameraControlRequestResult) {
    /** The camera control request was approved. */
    MobileRTCCameraControlRequestResult_Approve,
    /** The camera control request was declined. */
    MobileRTCCameraControlRequestResult_Decline,
    /** The previously approved camera control was revoked. */
    MobileRTCCameraControlRequestResult_Revoke
};

/**
 * @protocol MobileRTCCameraControlDelegate
 * @brief Callback event of receiving remote control.
 */
@protocol MobileRTCCameraControlDelegate <NSObject>
@optional
/**
 * @brief Callback for when the current user is granted camera control access.
 * @param userId  The user ID that accepted the request.
 * @param isApproved The result of the camera control request.
 * @note Once the current user sends the camera control request, this callback will be triggered with the result of the request.
 */
- (void)onCameraControlRequestResult:(NSUInteger)userId isApproved:(MobileRTCCameraControlRequestResult)isApproved;

@end

/**
 * @class MobileRTCCameraControlService
 * @brief Provides APIs to control the remote camera, including pan, tilt, and zoom operations.
 */
@interface MobileRTCCameraControlService : NSObject

/**
 * @brief Callback event of receiving camera control.
 */
@property (weak, nonatomic) id<MobileRTCCameraControlDelegate> _Nullable delegate;

/**
 * @brief The current controlled user id.
 * @return The current controlled user id.
 */
-(NSInteger)getUserId;

/**
 * @brief Used to determine whether the camera can be controlled or not.
 * @return YES means can control camera.
 */
- (BOOL)canControlCamera;

/**
 * @brief Request to control remote camera.
 * @return If the function succeeds, the return value is MobileRTCSDKError.
 */
- (MobileRTCSDKError)requestControlRemoteCamera;

/**
 * @brief Give up control of the remote camera.
 * @return If the function succeeds, the return value is MobileRTCSDKError.
 */
- (MobileRTCSDKError)giveUpControlRemoteCamera;

/**
 * @brief Turn the camera to the left.
 * @param range Rotation range, range is between 10 and 100.
 * @return If the function succeeds, the return value is MobileRTCSDKError.
 */
- (MobileRTCSDKError)turnLeft:(NSInteger)range;

/**
 * @brief Turn the camera to the right.
 * @param range Rotation range, range is between 10 and 100.
 * @return If the function succeeds, the return value is MobileRTCSDKError.
 */
- (MobileRTCSDKError)turnRight:(NSInteger)range;

/**
 * @brief Turn the camera up.
 * @param range Rotation range, range is between 10 and 100.
 * @return If the function succeeds, the return value is MobileRTCSDKError.
 */
- (MobileRTCSDKError)turnUp:(NSInteger)range;

/**
 * @brief Turn the camera down.
 * @param range Rotation range, range is between 10 and 100.
 * @return If the function succeeds, the return value is MobileRTCSDKError.
 */
- (MobileRTCSDKError)turnDown:(NSInteger)range;

/**
 * @brief Zoom the camera in.
 * @param range Rotation range, range is between 10 and 100.
 * @return If the function succeeds, the return value is MobileRTCSDKError.
 */
- (MobileRTCSDKError)zoomIn:(NSInteger)range;

/**
 * @brief Zoom the camera out.
 * @param range Rotation range, range is between 10 and 100.
 * @return If the function succeeds, the return value is MobileRTCSDKError.
 */
- (MobileRTCSDKError)zoomOut:(NSInteger)range;

@end

