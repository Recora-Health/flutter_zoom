/**
 * @file MobileRTCMeetingUserInfo.h
 * @brief User information and participant data structures.
 */

#import <Foundation/Foundation.h>

/**
 * @class MobileRTCVideoStatus
 * @brief The object of video status of the current user in the meeting.
 */
@interface MobileRTCVideoStatus : NSObject
/**
 * @brief Query if the user is sending video.
 */
@property (nonatomic, assign) BOOL  isSending;
/**
 * @brief Query if the user is receiving video.
 */
@property (nonatomic, assign) BOOL  isReceiving;
/**
 * @brief Check if the camera is connected to the current meeting. 
 */
@property (nonatomic, assign) BOOL  isSource;

@end

/**
 * @brief Enumeration of the type of a user's audio connection.
 */
typedef NS_ENUM(NSUInteger, MobileRTCAudioType) {
    /** Connected via VoIP (Voice over Internet Protocol). */
    MobileRTCAudioType_VoIP   = 0,
    /** Connected via phone call. */
    MobileRTCAudioType_Telephony,
    /** Unknown audio connection type. */
    MobileRTCAudioType_None,
};
/**
 * @class MobileRTCAudioStatus
 * @brief The object of the audio status of the current user in the meeting.
 */
@interface MobileRTCAudioStatus : NSObject
/**
 * @brief Query if the audio of the current user is muted.
 */
@property (nonatomic, assign) BOOL  isMuted;
/**
 * @brief Query if the current user is speaking.
 * @warning Webinar attenddee can not get the property.
 */
@property (nonatomic, assign) BOOL  isTalking;
/**
 * @brief Check the audio type of the current meeting.
 */
@property (nonatomic, assign) MobileRTCAudioType  audioType;

@end

/**
 * @class MobileRTCVirtualNameTag
 * @brief Represents a virtual name tag.
 */
@interface MobileRTCVirtualNameTag : NSObject
/**
 * @brief Tag ID. tagID is the unique identifier. The range of tagID is 0-1024.
 */
@property (nonatomic, assign)       NSInteger tagID;
/**
 * @brief Tag name.
 */
@property (nonatomic, copy)         NSString * _Nullable tagName;
@end

/**
 * @class MobileRTCGrantCoOwnerAssetsInfo
 * @brief This interface provides properties to specify and manage the privileges associated with different types of assets when assigning roles such as co-host or host in a meeting.
 * @note {@link MobileRTCGrantCoOwnerAssetsInfo} objects must be obtained through the {@link -[MobileRTCMeetingUserInfo getGrantCoOwnerAssetsInfo]} interface provided by the SDK, manual creation is not allowed.
 */

@interface MobileRTCGrantCoOwnerAssetsInfo : NSObject

/**
 * @brief Get the asset type.
 */
@property (nonatomic, assign, readonly) MobileRTCDGrantCoOwnerAssetsType type;
/**
 * @brief Query if the asset is locked.
 * @return the lock status of the asset.
 *
 * @note When the asset is locked, changing the grant property through the {@link MobileRTCGrantCoOwnerAssetsInfo.isGranted } interface is invalid.
 */
@property (nonatomic, assign, readonly) BOOL isAssetsLocked;
/**
 * @brief Query or Set  if the asset is granted.
 * @return grant YES means grant,NO means not grant.
 */
@property (nonatomic, assign) BOOL isGranted;

@end


/**
 * @class MobileRTCMeetingUserInfo
 * @brief The information of the current user in the meeting.
 */
@interface MobileRTCMeetingUserInfo : NSObject
/**
 * @brief The ID of user.
 */
@property (nonatomic, assign) NSUInteger       userID;
/**
 * @brief Get the user persistent ID matched with the current user information.This ID persists for the duration of the main meeting.Once the main meeting ends, the ID will be discarded.
 */
@property (nonatomic, copy) NSString* _Nullable       persistentId;
/**
 * @brief Determine if the information corresponds to the current user.
 */
@property (nonatomic, assign) BOOL             isMySelf;
/**
 * @brief The customer key that need the app intergrated with sdk to specify. The SDK will set this value when the associated settings are turned on. The max length of customer_key is 35.
 */
@property (nonatomic, copy) NSString* _Nullable       customerKey;
/**
 * @brief The screen name of user.
 */
@property (nonatomic, copy) NSString* _Nullable        userName;
/**
 * @brief The path to store the head portrait.
 */
@property (nonatomic, copy) NSString* _Nullable       avatarPath;
/**
 * @brief User's video status in the meeting.
 */
@property (nonatomic, retain) MobileRTCVideoStatus* _Nullable videoStatus;
/**
 * @brief User's audio status in the meeting.
 */
@property (nonatomic, retain) MobileRTCAudioStatus* _Nullable audioStatus;
/**
 * @brief The user raised his hand.
 */
@property (nonatomic, assign) BOOL             handRaised;
/**
 * @brief Query if the participant has a camera.
 */
@property (nonatomic, assign) BOOL             hasCamera;
/**
 * @brief User enter the waiting room when joins the meeting.
 */
@property (nonatomic, assign) BOOL             inWaitingRoom;
/**
 * @brief Query if the current user is the co-host.
 */
@property (nonatomic, assign) BOOL             isCohost;
/**
 * @brief Query if the current user is the host.
 */
@property (nonatomic, assign) BOOL             isHost;
/**
 * @brief Query if the current user is h323 user.
 */
@property (nonatomic, assign) BOOL             isH323User;
/**
 * @brief Query if the current user is Telephone user.
 */
@property (nonatomic, assign) BOOL             isPureCallInUser;
/**
 * @brief Query if the user is sharing only the sounds of computer.
 */
@property (nonatomic, assign) BOOL             isSharingPureComputerAudio;
/**
 * @brief The emoji feedback type from the user.
 */
@property (nonatomic, assign) MobileRTCEmojiFeedbackType  emojiFeedbackType;
/**
 * @brief The type of role of the user specified by the current information.
 */
@property (nonatomic, assign) MobileRTCUserRole  userRole;
/**
 * @brief Determine if user is interpreter.
 */
@property (nonatomic, assign) BOOL             isInterpreter;
/**
 * @brief Determine whether the user specified by the current information is a sign language interpreter or not.
 * @return YES indicates that the specified user is a sign language  interpreter, otherwise false.
 */
@property (nonatomic, assign) BOOL             isSignLanguageInterpreter;
/**
 * @brief Get interpreter active language.
 */
@property (nonatomic, copy) NSString* _Nullable   interpreterActiveLanguage;

/**
 * @brief Determine whether the user has started a raw live stream.
 * @return YES indicates that the specified user has started a raw live stream, otherwise false.
 */
@property (nonatomic, assign) BOOL             isRawLiveStreaming;
/**
 * @brief Determine whether the user has raw live stream privilege.
 * @return YES indicates that the specified user has raw live stream privilege, otherwise false.
 */
@property (nonatomic, assign) BOOL             hasRawLiveStreamPrivilege;

/**
 * @brief Determine whether the user corresponding to the current information is the sender of Closed Caption or not.
 * @return YES indicates that the user is the sender of Closed Caption.
 */
@property (nonatomic, assign) BOOL       isClosedCaptionSender;

/**
 * @return Whether the user is production studio user.
 */
@property (nonatomic, assign) BOOL  isProductionStudioUser;

/**
 * @brief Determine whether the user specified by the current information in companion mode or not.
 */
@property (nonatomic, assign) BOOL  isCompanionModeUser;
/**
 * @return The ID of the parent user of this production user.
 */
@property (nonatomic, assign) NSInteger  productionStudioParent;
/**
 * @brief Determine whether the user specified by the current information is in the webinar backstage or not.
 * @return YES indicates that the specified user is in the webinar backstage.
 */
@property (nonatomic, assign) BOOL  isInWebinarBackstage;

/**
 * @brief Determine whether the user specified by the current information is bot user or not.
 */
@property (nonatomic, assign) BOOL isBotUser;

/**
 * @brief Get the bot app name.
 */
@property (nonatomic, copy) NSString* _Nullable        botAppName;

/**
 * @brief Query if the participant enabled virtual name tag.
 * @return YES means enabled. Otherwise not.
 */
- (BOOL)isVirtualNameTagEnabled;

/**
 * @brief Query the virtual name tag roster infomation.
 * @return If the function succeeds, it return the list of user's virtual name tag roster info.
 */
- (NSArray<MobileRTCVirtualNameTag*> * _Nullable)getVirtualNameTagArray;

/**
 * @brief Query the granted assets info when assign a co-owner.
 * @return If the function succeeds, it returns the list of user's grant assets info. For more details, see {@link MobileRTCGrantCoOwnerAssetsInfo} object.
 *
 * @note If not granted any assets privilege, the default configuration of the web will be queried. If has granted assets privilege, the result after granting will be queried.
 */
- (nullable NSArray <MobileRTCGrantCoOwnerAssetsInfo*> *)getGrantCoOwnerAssetsInfo;

@end

/**
 * @class MobileRTCMeetingWebinarAttendeeInfo
 * @brief The information of user in the webinar.
 */
@interface MobileRTCMeetingWebinarAttendeeInfo : NSObject
/**
 * @brief The ID of user.
 */
@property (nonatomic, assign) NSUInteger userID;
/**
 * @brief Determine if the information corresponds to the current user.
 */
@property (nonatomic, assign) BOOL             isMySelf;
/**
 * @brief The screen name of user.
 */
@property (nonatomic, copy) NSString * _Nullable userName;
/**
 * @brief The type of role of the user specified by the current information.
 */
@property (nonatomic, assign) MobileRTCUserRole  userRole;
/**
 * @brief The user raised his hand.
 */
@property (nonatomic, assign) BOOL             handRaised;
/**
 * @brief Attendee can talk or not.
 */
@property (nonatomic, assign) BOOL             isAttendeeCanTalk;
/**
 * @brief User's audio status in the webinar meeting.
 */
@property (nonatomic, retain) MobileRTCAudioStatus* _Nullable audioStatus;

@end
