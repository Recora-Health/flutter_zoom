/**
 * @file MobileRTCVideoView.h
 * @brief Video view component for displaying and managing video content in meetings.
 */

#import <UIKit/UIKit.h>

/**
 * @brief Enumeration of the video aspect ratio.
 */
typedef enum {
    /** Display the captured data without any cropping or scaling. */
    MobileRTCVideoAspect_Original       = 0,
    /** Stretch both horizontally and vertically to fill the display (may cause distortion). */
    MobileRTCVideoAspect_Full_Filled    = 1,
    /** Add black bars to maintain aspect ratio (e.g., 16:9 content on a 4:3 display or vice versa). */
    MobileRTCVideoAspect_LetterBox  = 2,
    /** Crop the sides or top/bottom to fill the screen (e.g., cut sides for 16:9 on 4:3, or top/bottom for 4:3 on 16:9). */
    MobileRTCVideoAspect_PanAndScan = 3,
}MobileRTCVideoAspect;

/**
 * @class MobileRTCVideoView
 * @brief MobileRTCVideoView is designed for Render Attendee Video.
 */
@interface MobileRTCVideoView : UIView
/**
 * @brief Designated for get rendering user's ID.
 * @return Userid that rendering.
 */
- (NSInteger)getUserID;

/**
 * @brief Designated for Render Attendee Video.
 * @param userID user's video will be shown up.
 * @return If the function succeeds, it will return YES. Otherwise not.
 */
- (BOOL)showAttendeeVideoWithUserID:(NSUInteger)userID;

/**
 * @brief Designated for Stop Render.
 */
- (void)stopAttendeeVideo;

/**
 * @brief Designated for changing video aspect according to customer's requirement.
 */
- (void)setVideoAspect:(MobileRTCVideoAspect)aspect;

@end

/**
 * @class MobileRTCPreviewVideoView
 * @brief MobileRTCPreviewVideoView is designed for Preview Self Video.
 * @warning App need reponse to onSinkMeetingPreviewStopped, SDK handle start & stop Preview.
 */
@interface MobileRTCPreviewVideoView : MobileRTCVideoView
@end

/**
 * @class MobileRTCActiveVideoView
 * @brief MobileRTCActiveVideoView is designed for Render Active Video.
 */
@interface MobileRTCActiveVideoView : MobileRTCVideoView
@end

/**
 * @class MobileRTCActiveShareView
 * @brief MobileRTCActiveShareView is designed for Render Share Content.
 */
@interface MobileRTCActiveShareView : MobileRTCVideoView
/**
 * @brief Designated for Render Share Content.
 * @param shareSourceID user's shared content will be shown up.
 * @return If the function succeeds, it will return YES. Otherwise not.
 */
- (BOOL)showActiveShareWithShareSourceID:(NSUInteger)shareSourceID;

/**
 * @brief Designated for Stop Render Share Content.
 */
- (void)stopActiveShare;

/**
 * @brief Designated for Render Share Content Scale Change.
 * @param shareSourceID user's shared content scale change.
 */
- (void)changeShareScaleWithShareSourceID:(NSUInteger)shareSourceID;

/**
 * @brief Get MobileRTC Active Share View use share souce ID.
 * @return If the function succeeds, it will return share source ID.
 */
- (NSUInteger)getShareSourceID;

@end
