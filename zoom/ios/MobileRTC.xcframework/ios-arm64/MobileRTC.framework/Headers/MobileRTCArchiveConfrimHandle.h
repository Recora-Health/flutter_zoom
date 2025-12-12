/**
 * @file MobileRTCArchiveConfrimHandle.h
 * @brief Archive confirmation handler for meeting recordings.
 */

#import <Foundation/Foundation.h>
#import <MobileRTC/MobileRTCConstants.h>

/**
 * @class MobileRTCArchiveConfrimHandle
 * @brief The interface for user to handle confirm whether start archive after joining the meeting.
 */
@interface MobileRTCArchiveConfrimHandle : NSObject
/**
 * @brief join the meeting.
 * @param startArchive true means start the archive when join meeting, false means not start the archive then join meeting.
 * @return If the function succeeds, the return value is MobileRTCSDKError_Success. Otherwise fails.
 */
- (MobileRTCSDKError)joinWithArchive:(BOOL)startArchive;

/**
 * @brief The content that notify user to confirm start archive when join meeting.
 * @return The content that notify user to confirm start archive when join meeting.
 */
- (NSString * _Nullable)getArchiveConfirmContent;
@end

/**
 * @class MobileRTCRecoverMeetingHandle
 * @brief The interface for host user to handle recover meeting or not when start a deleted or expired meeting.
 */
@interface MobileRTCRecoverMeetingHandle : NSObject
/**
 * @brief Join the meeting.
 * @param toRecover YES means to recover the meeting and start the meeting. NO means not recover the meeting and leave the start meeting process.
 * @return If the function succeeds, the return value is MobileRTCSDKError_Success. Otherwise fails.
 */
- (MobileRTCSDKError)recoverMeeting:(BOOL)toRecover;

/**
 * @brief The content that notify the host user to recover the meeting.
 * @return The content that notify the host user to recover the meeting.
 */
- (NSString * _Nullable)getRecoverMeetingContent;
@end
