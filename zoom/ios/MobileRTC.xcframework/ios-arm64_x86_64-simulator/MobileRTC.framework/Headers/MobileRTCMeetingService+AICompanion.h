/**
 * @file MobileRTCMeetingService+AICompanion.h
 * @brief Meeting+AICompanion service functionality and management.
 */

#import <MobileRTC/MobileRTC.h>
#import <MobileRTC/MobileRTCAICQueryHelper.h>
#import <MobileRTC/MobileRTCAICSmartSummaryHelper.h>
NS_ASSUME_NONNULL_BEGIN

/**
 * @class MobileRTCAICompanionTurnOnAgainHandler
 * @brief AI Companion  in meeting.
 */
@interface MobileRTCAICompanionTurnOnAgainHandler : NSObject
/**
 * @brief Get the list of features list that the attendeeis turnsed off by attendee.
 * @return the  AI Companion feature list. see \link MobileRTCAICompanionType \endlink.
 */
- (NSArray *)getFeatureList;
/**
 * @brief Get the feature list that the assets are deleted when the feature is turned off by attendee.
 * @return The  AI Companion feature list. see \link MobileRTCAICompanionType \endlink.
 */
- (NSArray *)getAssetsDeletedFeatureList;
/**
 * @brief Rurn on the auto  AI Companion feature which was stopped by the attendee before the host or cohost joined meeting.
 * @return If the function succeeds, the return value is MobileRTCSDKError_Success. Otherwise the function fails.
 */
- (MobileRTCSDKError)turnOnAgain;
/**
 * @brief Agree the auto   AI Companion  feature turn off status. Keep the  AI Companion feature off.
 * @return If the function succeeds, the return value is MobileRTCSDKError_Success. the function fails.
 */
- (MobileRTCSDKError)agreeTurnOff;

@end

/**
 * @class MobileRTCAICompanionSwitchHandler
 * @brief The handler to handle a user request to turn the  AI Companion features on or off.
 */
@interface MobileRTCAICompanionSwitchHandler : NSObject
/**
 * @brief The user ID who requests the host to turn the  AI Companion features on or off.
 * @return The request user ID.
 */
-(NSUInteger)getRequestUserID;
/**
 * @brief Turn the  AI Companion features on or off.
 * @return YES means turn on the  AI Companion features.false means turn off the  AI Companion features.
 */
-(BOOL)isTurnOn;

/**
 * @brief Agree to the request to turn. the  AI Companion features on or off.
 * @param deleteAssets true means delete the meeting asserts when turning off the  AI Companion features.
 * @return If the function succeeds, the return value is SDKErr_Success. Otherwise the function fails.
 */
- (MobileRTCSDKError)agree:(BOOL)deleteAssets;

/**
 * @brief Decline the request to turn the  AI Companion features on or off.
 * @return If the function succeeds, the return value is SDKErr_Success. the function fails.
 */
- (MobileRTCSDKError)decline;

@end


/**
 * @brief AI Companion feature control class.
 */
@interface MobileRTCMeetingService (AICompanion)

/**
 * @brief Whether the meeting supports turning off the  AI Companion features.
 * @return YES means the meeting can support turning off the  AI Companion features. Otherwise the value is false.
 */
- (BOOL)isTurnoffAllAICompanionsSupported;
/**
 * @brief Whether the current user can turn off the  AI Companion features.
 * @return YES means the user can turn off the  AI Companion features.
 */
- (BOOL)canTurnOffAllAICompanions;
/**
 * @brief Turn off the  AI Companion features.
 * @remark All AI features includinge \link  @c MobileRTCAICompanionType_QUERY \endlink, \link  @c MobileRTCAICompanionType_SMART_SUMMARY \endlink, and \link  @c MobileRTCAICompanionType_SMART_RECORDING \endlink can be turned off at once.
 * @param deleteMeetingAssets true whether delete the meeting assets when turn off the  AI Companion features.
 * @return If the function succeeds, the return value is MobileRTCSDKError_Success. Otherwise the function fails.
 */
- (MobileRTCSDKError)turnOffAllAICompanion:(BOOL)deleteMeetingAssets;
/**
 * @brief Whether the meeting supports turning off the AI Companion features.
 * @return YES means the meeting can support turning on the  AI Companion features. Otherwise  the value is false.
 */
- (BOOL)isTurnOnAllAICompanionSupported;
/**
 * @brief Whether the current user can turn off the  AI Companion features.
 * @return YES means the user can turn off the  AI Companion features.
 */
- (BOOL)canTurnOnAllAICompanion;
/**
 * @brief Turn on all the  AI Companion features.
 * @return If the function succeeds, the return value is MobileRTCSDKError_Success. Otherwise  the function fails.
 */
- (MobileRTCSDKError)turnOnAllAICompanion;
/**
 * @brief Whether the current user can ask the host to turn off all started  AI Companion features.
 * @remark If the current user joins the meeting before the host, they can check \link MobileRTCMeetingService::canTurnOffAllAICompanions \endlink to turn off the AI Companion features by himself/herself.
 * @remark All AI features includinge \link @c MobileRTCAICompanionType_QUERY \endlink, \link @c MobileRTCAICompanionType_SMART_SUMMARY \endlink,, and \link @c MobileRTCAICompanionType_SMART_RECORDING \endlink can be turned off at once.
 * @return YES means the user can request host to turn off the  AI Companion features.
 */
- (BOOL)canRequestTurnoffAllAICompanion;
/**
 * @brief Ask host to turn off all started  AI Companion features.
 * @remark All AI features includinge \link @c MobileRTCAICompanionType_QUERY \endlink, \link  @c MobileRTCAICompanionType_SMART_SUMMARY \endlink, and \link  @c MobileRTCAICompanionType_SMART_RECORDING \endlink can be turned off at once.
 * @return If the function succeeds, the return value is MobileRTCSDKError_Success. Otherwise failed.
 */
- (MobileRTCSDKError)requestTurnoffAllAICompanion;
/**
 * @brief Whether the current user can ash the host to turn on all  AI Companion features if they are enabled for the current meeting.
 * @remark Only \link  @c MobileRTCAICompanionType_QUERY \endlink and \link @c MobileRTCAICompanionType_SMART_SUMMARY \endlink can be turned on at once.
 * @return YES means the user can ask the host to turn on the AI Companion features.
 */
- (BOOL)canRequestTurnOnAllAICompanion;
/**
 * @brief Ask host to turn on all  AI Companion features if they are enabled for the current meeting.
 * @remark Only \link @c MobileRTCAICompanionType_QUERY \endlink and \link @c MobileRTCAICompanionType_SMART_SUMMARY \endlink can be turned on at once.
 * @return If the function succeeds, the return value is MobileRTCSDKError_Success. Otherwise  the function fails.
 */
- (MobileRTCSDKError)requestTurnOnAllAICompanion;

/**
 * @brief Get  AI Companion Query Helper.
 * @return It returns a instance of MobileRTCAICompanionQueryHelper.
 */
- (MobileRTCAICompanionQueryHelper *)getQueryHelper;


/**
 * @brief Get the smart summary helper.
 * @return If the function succeeds, the return value is a pointer to MobileRTCAICompanionSmartSummaryHelper. Otherwise the function returns nil.
 */
- (MobileRTCAICompanionSmartSummaryHelper *)getSmartSummaryHelper;

@end

NS_ASSUME_NONNULL_END
