//
//  MobileRTCBORole.h
//  MobileRTC
//
//  Created by Zoom Communications on 2020/2/11.
//  Copyright © Zoom Communications, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * @brief Enumeration of breakout meeting user status.
 */
typedef enum : NSUInteger {
    /** The breakout meeting status is unknown. */
    BOUserStatusUnknown      = 0,
    /** The user is unassigned to any breakout meeting. */
    BOUserStatusUnassigned  = 1,
    /** The user is assigned but has not joined the breakout meeting. */
    BOUserStatusNotJoin     = 2,
    /** The user is currently in the breakout meeting. */
    BOUserStatusInBO        = 3,
} MobileRTCBOUserStatus;

/**
 * @class MobileRTCBOUser
 * @brief Interface for user in Breakout Room.
 */
@interface MobileRTCBOUser : NSObject
/**
 * @brief Get bo meeting user id.
 */
- (NSString * _Nullable)getUserId;

/**
 * @brief Get bo meeting user name.
 */
- (NSString * _Nullable)getUserName;

@end

/**
 * @class MobileRTCBOMeeting
 * @brief Provides functions for breakout meetings.
 */
@interface MobileRTCBOMeeting : NSObject
/**
 * @brief Get bo meeting id.
 */
- (NSString * _Nullable)getBOMeetingId;

/**
 * @brief Get bo meeting name.
 */
- (NSString * _Nullable)getBOMeetingName;

/**
 * @brief Get bo meeting user array.
 */
- (NSArray <NSString *>* _Nullable)getBOMeetingUserList;

/**
 * @brief Get breakout meeting user status.
 * @param userID The user's user ID.
 * @return If the function succeeds,will return user status.
 */
-(MobileRTCBOUserStatus)getBOUserStatusWithUserID:(NSString *_Nonnull)userID;
@end

/**
 * @brief Enumeration of Breakout Room (BO) stop countdown durations.
 */
typedef NS_ENUM(NSUInteger, MobileRTCBOStopCountDown) {
    /** No countdown. Breakout Rooms stop immediately. */
    MobileRTCBOStopCountDown_Not_CountDown  = 0,
    /** Countdown duration: 10 seconds before BO stops. */
    MobileRTCBOStopCountDown_Seconds_10,
    /** Countdown duration: 15 seconds before BO stops. */
    MobileRTCBOStopCountDown_Seconds_15,
    /** Countdown duration: 30 seconds before BO stops. */
    MobileRTCBOStopCountDown_Seconds_30,
    /** Countdown duration: 60 seconds before BO stops. */
    MobileRTCBOStopCountDown_Seconds_60,
    /** Countdown duration: 120 seconds before BO stops. */
    MobileRTCBOStopCountDown_Seconds_120,
};

/**
 * @class MobileRTCBOOption
 * @brief BO option.
 */
@interface MobileRTCBOOption : NSObject
/**
 * @brief BO Count Down Second.
 */
@property (nonatomic, assign) MobileRTCBOStopCountDown countdownSeconds;
/**
 * @brief Enable/Disable that participant can choose breakout room.
 */
@property (nonatomic, assign) BOOL isParticipantCanChooseBO;
/**
 * @brief Enable/Disable that participant can return to main session at any time.
 */
@property (nonatomic, assign) BOOL isParticipantCanReturnToMainSessionAtAnyTime;
/**
 * @brief Enable/Disable that auto move all assigned participants to breakout room.
 */
@property (nonatomic, assign) BOOL isAutoMoveAllAssignedParticipantsEnabled;
/**
 * @brief YES: it's timer BO NO: not timer BO.
 */
@property (nonatomic, assign) BOOL isBOTimerEnabled;
/**
 * @brief YES: if time is up, will stop BO auto. NO: don't auto stop.
 */
@property (nonatomic, assign) BOOL isTimerAutoStopBOEnabled;
/**
 * @brief Seconds of BO timer duration.
 * @warning When timerDuration is 0, it means that the BO duration is 30*60 seconds.
 */
@property (nonatomic, assign) NSInteger timerDuration;

//  WebinarBo
/**
 * @brief Enable or disable webinar attendee join webinar BO. When it changes, the BO data will be reset.
 */
@property(nonatomic,assign) BOOL isAttendeeContained;

/**
 * @brief Enable or disable that panelist can choose breakout room.
 */
@property(nonatomic,assign) BOOL isPanelistCanChooseBO;

/**
 * @brief Enable or disable that Attendee can choose breakout room, invalid when attendee is not contained.
 */
@property(nonatomic,assign) BOOL isAttendeeCanChooseBO;

/**
 * @brief Enable or disable that max roomUser limits in BO room.
 */
@property(nonatomic,assign) BOOL isUserConfigMaxRoomUserLimitsEnabled;

/**
 * @brief Numbers of max roomUser limits in BO room, default is 20.
 */
@property(nonatomic,assign)unsigned int nUserConfigMaxRoomUserLimits;

@end

/**
 *    //////////////////////////// Creator ////////////////////////////
 *    1. Main Functions:
 *        1) create|delete|rename BO
 *        2) assign|remove user to BO
 *       3) set BO option
 *    2. Remarks:
 *       1) These editing can only be done before BO is started
 *
 *    //////////////////////////// Admin ////////////////////////////
 *   1. Main Functions:
 *        1) after BO is started, assign new user to BO,
 *        2) after BO is started, switch user from BO-A to BO-B
 *       3) stop BO
 *        4) start BO
 *
 *    //////////////////////////// Assistant ////////////////////////////
 *    1. Main Functions:
 *        1) join BO with BO id
 *        2) leave BO
 *
 *   //////////////////////////// Attendee ////////////////////////////
 *   1. Main Functions:
 *        1) join BO
 *       2) leave BO
 *       3) request help
 *
 *    //////////////////////////// DataHelper ////////////////////////////
 *    1. Main Functions:
 *        1) get unassigned user list
 *        2) get BO list
 *       3) get BO object
 *
 *
 *    host in master conference     : creator + admin + assistant + dataHelper
 *    host in BO conference         : admin + assistant + dataHelper
 *    CoHost in master conference   : [attendee] or [creator + admin + assistant + dataHelper]
 *    CoHost in BO conference       : [attendee] or [admin + assistant + dataHelper]
 *    attendee in master conference : attendee + [assistant + dataHelper]
 *   attendee in BO conference     : attendee + [assistant + dataHelper]
 *
 *   Import Remarks:
 *   1. attendee in master conference/attendee in BO conference
 *       1) if BOOption.IsParticipantCanChooseBO is YES, attendee has objects:  [attendee + assistant + dataHelper]
 *      2) if BOOption.IsParticipantCanChooseBO is NO, attendee has object:  [attendee]
 *   2. CoHost in master conference
 *       1) if CoHost is desktop client, and host is desktop client, the CoHost has objects: [creator + admin + assistant + dataHelper]
 *      2) if CoHost is desktop client, and host is mobile client, the CoHost has object: [attendee]
 *      3) if CoHost is mobile client, the CoHost has object: [attendee]
 */

/**
 * @class MobileRTCBOCreator
 * @brief Interface for creating and managing breakout rooms.
 */
@interface MobileRTCBOCreator : NSObject
/**
 * @brief Create a bo meeting.
 * @param boName the BO name.
 * @return Bo meeting id.
 * @deprecated Use createBreakoutRoom: instead.
 */
- (NSString * _Nullable)createBO:(NSString * _Nonnull)boName DEPRECATED_MSG_ATTRIBUTE("Use createBreakoutRoom: instead");

/**
 * @brief Create a breakout room.
 * @param boName the BO name.
 * @return If success the return value is YES, otherwise NO.
 * @note 1. This function is compatible with meeting breakout room and webinar breakout room.
 * @note 2. This function is asynchronous, the callback is: 'onCreateBOResponse:BOID:'.
 * @note 3. Webinar breakout room only support in Zoomui Mode.
 */
- (BOOL)createBreakoutRoom:(NSString * _Nonnull)boName;

/**
 * @brief Create bo meetings in batches.
 * @param boNameList the BO name list.
 * @return Batch bo create success or not.
 */
- (BOOL)createGroupBO:(NSArray<NSString*> * _Nonnull)boNameList;

/**
 * @brief Creator webinar breakout meeting, available only For Zoomui Mode.
 * @param boNameList Breakout meeting name list，the element of nameList should less than 50 characters.
 * @return If the function succeeds,will return YES.
 */
- (BOOL)createWebinarBO:(NSArray<NSString*> * _Nonnull)boNameList;

/**
 * @brief Update bo meeting name with bo id, the callback is: 'onUpdateBONameResponse:BOID'.
 * @param boId the BO id.
 * @param boName the BO name.
 * @return Update success or not.
 */
- (BOOL)updateBO:(NSString * _Nonnull)boId name:(NSString * _Nonnull)boName;

/**
 * @brief Remove a bo meeting, the callback is: 'onRemoveBOResponse:BOID:'.
 * @param boId the BO id.
 * @return Remove bo meting success or not.
 */
- (BOOL)removeBO:(NSString * _Nonnull)boId;

/**
 * @brief Assign a user to a bo meeting.
 * @param boUserId the BO user id.
 * @param boId the BO id.
 * @return Assign success or not.
 */
- (BOOL)assignUser:(NSString * _Nonnull)boUserId toBO:(NSString * _Nonnull)boId;

/**
 * @brief Remove a user from a bo meeting.
 * @return Remove success or not.
 */
- (BOOL)removeUser:(NSString * _Nonnull)boUserId fromBO:(NSString * _Nonnull)boId;

/**
 * @brief Set BO option.
 * @param option the option that you want to set.
 * @return If success the return value is YES, otherwise NO.
 */
- (BOOL)setBOOption:(MobileRTCBOOption *_Nonnull)option;

/**
 * @brief Get BO option.
 * @return The BOOption value.
 */
- (MobileRTCBOOption * _Nullable)getBOOption;

/**
 * @brief Check whether web enabled the pre-assigned option when scheduling a meeting.
 * @return YES if it is enabled, otherwise NO.
 */
- (BOOL)isWebPreAssignBOEnabled;

/**
 * @brief Request web pre-assigned data and create those rooms.
 * @return If the function succeeds, the return value is MobileRTCSDKError_Success.Otherwise failed. To get extended error information, see [MobileRTCSDKError].
 */
- (MobileRTCSDKError)requestAndUseWebPreAssignBOList;

/**
 * @brief Get the downloading status of pre-assigned data.
 * @return The return value is a enum for download status. For more details, see [MobileRTCBOPreAssignBODataStatus].
 */
- (MobileRTCBOPreAssignBODataStatus)getWebPreAssignBODataStatus;

@end

/**
 * @class MobileRTCBOAdmin
 * @brief Interface for  managing breakout rooms.
 */
@interface MobileRTCBOAdmin : NSObject
/**
 * @brief Start bo meeting which assigned,  the callback is: 'onStartBOResponse:'.
 * @return Start success or not.
 */
- (BOOL)startBO;

/**
 * @brief Stop bo meeting which assigned, the callback is:' onStopBOResponse:'.
 * @return Stop success or not.
 */
- (BOOL)stopBO;

/**
 * @brief Assign a bo user to a started bo meeting.
 * @param boUserId the BO user id.
 * @param boId the BO id.
 * @return The result of call the method.
 */
- (BOOL)assignNewUser:(NSString * _Nonnull)boUserId toRunningBO:(NSString * _Nonnull)boId;

/**
 * @brief Switch a user to a new started bo meeting.
 * @param boUserId the BO user id.
 * @param boId the BO id.
 * @return The result of call the method.
 */
- (BOOL)switchUser:(NSString * _Nonnull)boUserId toRunningBO:(NSString * _Nonnull)boId;

/**
 * @brief Indicate that the bo can be start or not.
 * @return The result of call the method.
 */
- (BOOL)canStartBO;

/**
 * @brief Join bo meeting for designated bo user id.
 * @param boUserId the BO user id.
 * @return The result of call the method.
 */
- (BOOL)joinBOByUserRequest:(NSString * _Nonnull)boUserId;

/**
 * @brief Reply ignore for the help request from bo attendees.
 * @param boUserId the BO user id.
 * @return The result of call the method.
 */
- (BOOL)ignoreUserHelpRequest:(NSString * _Nonnull)boUserId;

/**
 * @brief Broadcase message for all attendees in the meeting.
 * @param strMsg the bo message.
 * @return The result of call the method.
 */
- (BOOL)broadcastMessage:(NSString * _Nonnull)strMsg;

/**
 * @brief Host invite user return to main session, When BO is started and user is in BO.
 * @param boUserId the bo user id.
 * @return YES indicates success, otherwise fail.
 */
- (BOOL)inviteBOUserReturnToMainSession:(NSString * _Nonnull)boUserId;
/**
 * @brief Query if the current meeting supports broadcasting host's voice to BO.
 * @return YES means that the meeting supports this, otherwise it's not supported.
 */
- (BOOL)isBroadcastVoiceToBOSupport;

/**
 * @brief Query if the host now has the ability to broadcast voice to BO.
 * @return YES means that the host now has the ability, otherwise the host does not.
 */
- (BOOL)canBroadcastVoiceToBO;
/**
 * @brief Start or stop broadcasting voice to BO.
 * @param bStart YES for start and NO for stop.
 * @return YES means that the invocation succeeds., Otherwise, it fails.
 */
- (BOOL)broadcastVoiceToBO:(BOOL)bStart;
@end

/**
 * @class MobileRTCBOAssistant
 * @brief Manages operations for joining and leaving breakout meetings as an assistant.
 */
@interface MobileRTCBOAssistant : NSObject

/**
 * @brief Join a bo meeting with bo id.
 * @param boId the BO id.
 * @return The result of call the method.
 */
- (BOOL)joinBO:(NSString * _Nonnull)boId;

/**
 * @brief Leave joined bo meeting.
 * @return The result of call the method.
 */
- (BOOL)leaveBO;

@end

/**
 * @class MobileRTCBOAttendee
 * @brief Manages operations for attendees in breakout meetings.
 */
@interface MobileRTCBOAttendee : NSObject

/**
 * @brief Join to assined bo meeting.
 * @return The result of call the method.
 */
- (BOOL)joinBO;

/**
 * @brief Leave assined bo meeting.
 * @return The result of call the method.
 */
- (BOOL)leaveBO;

/**
 * @brief Get bo meeting name.
 * @return The bo name.
 */
- (NSString * _Nullable)getBOName;

/**
 * @brief Send help to admin.
 * @return The result of call the method.
 */
- (BOOL)requestForHelp;

/**
 * @brief If the host in current bo.
 * @return The result of call the method.
 */
- (BOOL)isHostInThisBO;

/**
 * @brief Determine if participant can return to main session.
 * @return YES if can, otherwise NO.
 */
- (BOOL)isCanReturnMainSession;

@end

/**
 * @class MobileRTCBOData
 * @brief Provides data helper functions for breakout meetings.
 */
@interface MobileRTCBOData : NSObject

/**
 * @brief Get un assined user list.
 * @return The unassigned user list.
 */
- (NSArray * _Nullable)getUnassignedUserList;

/**
 * @brief Get all bo meeting id list.
 * @return The BOMeeting id list.
 */
- (NSArray * _Nullable)getBOMeetingIDList;

/**
 * @brief Get bo user object by bo user id.
 * @param userId the user id.
 * @return The object of MobileRTCBOUser.
 */
- (MobileRTCBOUser * _Nullable)getBOUserByUserID:(NSString * _Nonnull)userId;

/**
 * @brief Get bo meeting object by bo meeting id.
 * @param boId the BO id.
 * @return The object of MobileRTCBOMeeting.
 */
- (MobileRTCBOMeeting * _Nullable)getBOMeetingByID:(NSString * _Nonnull)boId;

/**
 * @brief Get bo meeting name of current BO.
 * @return The current BO name.
 */
- (NSString  * _Nullable)getCurrentBOName;

/**
 * @brief Whether the boUserId is current user.
 * @param boUserId the bo user id.
 * @return The result of call the method.
 */
- (BOOL)isBOUserMyself:(NSString *_Nonnull)boUserId;

@end

