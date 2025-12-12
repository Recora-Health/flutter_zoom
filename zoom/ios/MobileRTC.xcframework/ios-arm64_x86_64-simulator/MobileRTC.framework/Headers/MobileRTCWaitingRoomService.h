/**
 * @file MobileRTCWaitingRoomService.h
 * @brief Waiting room management and participant handling.
 */

#import <Foundation/Foundation.h>

/**
 * @brief Enumeration of waiting room layout type. For more information, please visit <https://support.zoom.com/hc/en/article?id=zm_kb&sysparm_article=KB0059359>.
 */
typedef NS_ENUM(NSUInteger, MobileRTCWaitingRoomLayoutType) {
    /** Default layout. */
    MobileRTCWaitingRoomLayoutType_Default = 0,
    /** Layout displaying a logo. */
    MobileRTCWaitingRoomLayoutType_Logo,
    /** Layout displaying a video. */
    MobileRTCWaitingRoomLayoutType_Video,
};

/**
 * @brief Enumeration for the status of custom waiting room data.
 */
typedef NS_ENUM(NSUInteger, MobileRTCCustomWaitingRoomDataStatus) {
    /** Initial state, before any download has started. */
    MobileRTCCustomWaitingRoomDataStatus_Init,
    /** Custom waiting room data is currently being downloaded. */
    MobileRTCCustomWaitingRoomDataStatus_Downloading,
    /** Custom waiting room data has been successfully downloaded. */
    MobileRTCCustomWaitingRoomDataStatus_Download_OK,
    /** Failed to download custom waiting room data. */
    MobileRTCCustomWaitingRoomDataStatus_Download_Fail,
};

/**
 * @class MobileRTCCustomWaitingRoomData
 * @brief The WaitingRoom Customize Data Info.
 */
@interface MobileRTCCustomWaitingRoomData : NSObject
@property (nonatomic, retain) NSString * _Nullable title;

@property (nonatomic, retain) NSString * _Nullable descriptionString;

@property (nonatomic, retain) NSString * _Nullable logoPath;

@property (nonatomic, retain) NSString * _Nullable imagePath;

@property (nonatomic, retain) NSString * _Nullable videoPath;

@property (nonatomic, assign) MobileRTCWaitingRoomLayoutType type;

@property (nonatomic, assign) MobileRTCCustomWaitingRoomDataStatus status;

@end

/**
 * @protocol MobileRTCWaitingRoomServiceDelegate
 * @brief Meeting host enabled the waiting room feature, then the delegate will receive this notification  #only for custom UI#.
 */
@protocol MobileRTCWaitingRoomServiceDelegate <NSObject>

@optional

/**
 * @brief Meeting host enabled the waiting room feature, then the delegate will receive this notification, will notify the host someone entery the waiting room.
 * @note Only for custom UI.
 */
- (void)onWaitingRoomUserJoin:(NSUInteger)userId;

/**
 * @brief Meeting host enabled the waiting room feature, then the delegate will receive this notification, will notify the host someone left from waiting room.
 * @note Only for custom UI.
 */
- (void)onWaitingRoomUserLeft:(NSUInteger)userId;

/**
 * @brief During the waiting room, this callback event will be triggered when host change audio status.
 * @param audioCanTurnOn YES means audio can be turned on. Otherwise not.
 */
- (void)onWaitingRoomPresetAudioStatusChanged:(BOOL)audioCanTurnOn;

/**
 * @brief During the waiting room, this callback event will be triggered when host change video status.
 * @param videoCanTurnOn YES means video can be turned on. Otherwise not.
 */
- (void)onWaitingRoomPresetVideoStatusChanged:(BOOL)videoCanTurnOn;

/**
 * @brief During the waiting room, this callback event will be triggered when requestCustomWaitingRoomData called.
 * @param data The WaitingRoom Customize Data Info.
 */
- (void)onCustomWaitingRoomDataUpdated:(MobileRTCCustomWaitingRoomData *_Nullable)data;

/**
 * @brief Callback of that waiting room user name changed.
 * @param userID The ID of user whose user name has changed.
 * @param userName The new name of user.
 */
- (void)onWaitingRoomUserNameChanged:(NSInteger)userID userName:(nonnull NSString *)userName;

@end

/**
 * @class MobileRTCWaitingRoomService
 * @brief Interface for managing the waiting room during a meeting.
 */
@interface MobileRTCWaitingRoomService : NSObject

/**
 * @brief Waiting Room service delegate.
 */
@property (weak, nonatomic) id<MobileRTCWaitingRoomServiceDelegate> _Nullable delegate;

/**
 * @brief Is this meeting support Waiting Room feature.
 * @return Yes if support waiting room.
 */
-(BOOL)isSupportWaitingRoom;

/**
 * @brief Is this meeting enabled Waiting Room feature.
 * @return Yes if enabled.
 */
-(BOOL)isWaitingRoomOnEntryFlagOn;

/**
 * @brief Query if enableWaitingRoomOnEntry feature locked.
 * @return YES means enabled. NO not.
 */
-(BOOL)isWaitingRoomOnEntryLocked;

/**
 * @brief Enable or disable waiting room feature of this meeting.
 * @return The result of this operation.
 */
- (MobileRTCMeetError)enableWaitingRoomOnEntry:(BOOL)bEnable;

/**
 * @brief Get the waiting room user id list.
 * @return Waiting room user list.
 */
- (nullable NSArray <NSNumber *> *)waitingRoomList;

/**
 * @brief Get the user detail information in waiting room.
 * @return Waiting room user information.
 */
- (nullable MobileRTCMeetingUserInfo*)waitingRoomUserInfoByID:(NSUInteger)userId;

/**
 * @brief Admit the user go to meeting fram waiting room.
 * @return The result of this operation.
 * @warning Only meeting host/co-host can run the function.
 */
- (MobileRTCSDKError)admitToMeeting:(NSUInteger)userId;

/**
 * @brief Permit all of the users currently in the waiting room to join the meeting.
 * @return If the function succeeds, the return value is MobileRTCSDKError_Success, otherwise failed, the return is error. For more details, see [MobileRTCSDKError] enum.
 */
- (MobileRTCSDKError)admitAllToMeeting;
/**
 * @brief Put the user to waiting room from meeting.
 * @return The result of this operation.
 * @warning Only meeting host/co-host can run the function.
 */
- (MobileRTCSDKError)putInWaitingRoom:(NSUInteger)userId;

/**
 * @brief Determine if the attendee is enabled to turn on audio when joining the meeting.
 * @return YES indicates to enable to turn on.
 */
- (BOOL)isAudioEnabledInWaitingRoom;

/**
 * @brief Determine if the attendee is enabled to turn on video when joining the meeting.
 * @return YES indicates to enable to turn on.
 */
- (BOOL)isVideoEnabledInWaitingRoom;

/**
 * @brief Pre-set audio mute or unmute status in waiting room.
 * @param muteAudio Pre-set audio mute or unmute status.
 * @return MobileRTCSDKError_Success means the pre-set success, otherwise failed.
 * @warning Only worked in waiting room.
 */
- (MobileRTCSDKError)presetAudioInWaitingRoom:(BOOL)muteAudio;

/**
 * @brief Get the audio pre-set mute or unmute status in the waiting room.
 * @return YES means pre-set unmute, NO means pre-set mute.
 * @warning Only worked in waiting room.
 */
- (BOOL)isPresetAudioUnmuteInWaitingRoom;

/**
 * @brief Pre-set video mute or unmute status in waiting room.
 * @param muteVideo Pre-set video mute or unmute status.
 * @return MobileRTCSDKError_Success means the pre-set succeeded, otherwise it failed.
 * @warning Only worked in waiting room.
 */
- (MobileRTCSDKError)presetVideoInWaitingRoom:(BOOL)muteVideo;

/**
 * @brief Get the video pre-set mute or unmute status in the waiting room.
 * @return YES means pre-set unmute, NO means pre-set mute.
 * @warning Only worked in waiting room.
 */
- (BOOL)isPresetVideoUnmuteInWaitingRoom;

/**
 * @brief Get the WaitingRoom CustomizeData information in the waiting room.
 * @return If the function succeeds, the return value is MobileRTCSDKError_Success. Otherwise failed. To get extended error information, see [MobileRTCSDKError].
 */
- (MobileRTCSDKError)requestCustomWaitingRoomData;

/**
 * @brief Determine if host or cohost is enabled to rename user in the waiting room.
 * @return YES indicates to enable to turn on.
 */
- (BOOL)canRenameUser;

/**
 * @brief Change user's screen name in the waiting room.
 * @param userID Tnto waiting room byhe ID of user who is put i host/co-host.
 * @param userName The new user name.
 * @return If the function succeeds, it will return MobileRTCSDKError_Success. Otherwise failed.
 */
- (MobileRTCSDKError)renameUser:(NSInteger)userID newUserName:(nonnull NSString * )userName;

/**
 * @brief Determine if host or cohost is enabled to expel user in the waiting room.
 * @return YES indicates can expel user.
 */
- (BOOL)canExpelUser;

/**
 * @brief Remove the specified user from waiting room.
 * @param userID The ID of user who is put into waiting room by host/co-host.
 * @return If the function succeeds, it will return MobileRTCSDKError_Success. Otherwise failed.
 */
- (MobileRTCSDKError)expelUser:(NSInteger)userID;

@end
