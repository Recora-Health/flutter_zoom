/**
 * @file MobileRTCMeetingService+BO.h
 * @brief Meeting+BO service functionality and management.
 */

#import <MobileRTC/MobileRTC.h>
#import <MobileRTC/MobileRTCBORole.h>

/**
 * @brief Creates Breakout Room meetings-related objects and fetches Breakout Room-related status information.
 */
@interface MobileRTCMeetingService (BO)
/**
 * @brief Object for creating Breakout Room meetings defined in  [MobileRTCBOCreator].
 * @return If the function succeeds, it will return object MobileRTCBOCreator.
 */
- (MobileRTCBOCreator * _Nullable)getCreatorHelper;

/**
 * @brief Object for administrator management of Breakout Room meetings defined in [MobileRTCBOAdmin].
 * @return If the function succeeds, it will return object MobileRTCBOAdmin.
 */
- (MobileRTCBOAdmin * _Nullable)getAdminHelper;

/**
 * @brief Object for help assistant of Breakout Room meetings defined in [MobileRTCBOAssistant].
 * @return If the function succeeds, it will return object MobileRTCBOAssistant.
 */
- (MobileRTCBOAssistant * _Nullable)getAssistantHelper;

/**
 * @brief Object for attendee functionality of Breakout Room meetings defined in [MobileRTCBOAttendee].
 * @return If the function succeeds, it will return object MobileRTCBOAttendee.
 */
- (MobileRTCBOAttendee * _Nullable)getAttedeeHelper;

/**
 * @brief Object for Breakout Room meeting id information defined in [MobileRTCBOData].
 * @return If the function succeeds, it will return object MobileRTCBOData.
 */
- (MobileRTCBOData * _Nullable)getDataHelper;

/**
 * @brief Has Breakout Room meeting began.
 * @return If the function succeeds, it will return YES, otherwise not.
 */
- (BOOL)isBOMeetingStarted;

/**
 * @brief Is Breakout Room feature enabled in meeting.
 * @return If the function succeeds, it will return YES, otherwise not.
 */
- (BOOL)isBOMeetingEnabled;

/**
 * @brief Is currently in Breakout Room during meeting.
 * @return If the function succeeds, it will return YES, otherwise not.
 */
- (BOOL)isInBOMeeting;

/**
 * @brief Query if the host is broadcasting voice to BO.
 * @return YES means that the host is broadcasting, otherwise it's not broadcasting.
 */
- (BOOL)isBroadcastingVoiceToBO;

/**
 * @brief Get current Breakout status.
 * @return Enum for Breakout status. [MobileRTCBOStatus].
 */
- (MobileRTCBOStatus)getBOStatus;

/**
 * @brief Get the name of the BO you are going to.
 * @return The value is join bo name which you are going to.
 * @note When you enter a BO or are switched to another BO by the host, maybe you need the BO name to display on transfer UI.
 */
- (NSString * _Nullable)getJoiningBOName;

@end


