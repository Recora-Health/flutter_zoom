/**
 * @file MobileRTCReminderHelper.h
 * @brief Helper for managing meeting reminders and notifications.
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class MobileRTCReminderContent;
@class MobileRTCReminderHandler;

/**
 * @protocol MobileRTCReminderDelegate
 * @brief Reminder callback event.
 */
@protocol MobileRTCReminderDelegate <NSObject>
@optional

/**
 * @brief Callback event when the reminder dialog show.
 * @param content the detail content in the reminder dialog.
 * @param handler the helper to handle the reminder dialog.
 */
- (void)onReminderNotify:(MobileRTCReminderContent * _Nullable)content handle:(MobileRTCReminderHandler * _Nullable)handler;

@end

/**
 * @class MobileRTCReminderContent
 * @brief The reminder dialog content.
 */
@interface MobileRTCReminderContent : NSObject
/**
 * @brief The type of the reminder.
 */
@property (nonatomic, assign) MobileRTCReminderType type;

/**
 * @brief The title of the reminder dialog.
 */
@property (nonatomic, copy, nullable) NSString *title;

/**
 * @brief The detail content of the reminder dialog.
 */
@property (nonatomic, copy, nullable) NSString *content;

/**
 * @brief Whether block the user join or stay in the meeting.
 */
@property (nonatomic, assign) BOOL isBlock;

/**
 * @brief Get the type of the action which user should take after receiving this reminder content.
 */
@property (nonatomic, assign) MobileRTCReminderActionType actionType;

/**
 * @brief Get a list of reminder’s type.
 * @return List of the reminder’s type.
 */
- (NSArray<NSNumber*>*_Nonnull)getMultiReminderTypes;

@end

/**
 * @class MobileRTCReminderHandler
 * @brief The interface to handle the reminder dialog.
 */
@interface MobileRTCReminderHandler : NSObject
/**
 * @brief accept the reminder.
 * @return If the function succeeds, the return value is MobileRTCSDKError_Success. Otherwise the function fails.
 */
- (MobileRTCSDKError)accept;

/**
 * @brief Declined the reminder.
 * @return If the function succeeds, the return value is MobileRTCSDKError_Success. Otherwise the function fails.
 */
- (MobileRTCSDKError)declined;

/**
 * @brief Ignore the reminder.
 * @return If the function succeeds, the return value is MobileRTCSDKError_Success. Otherwise the function fails.
 */
- (MobileRTCSDKError)ignore;

/**
 * @brief Set not show the disclaimer in subsequent meetings.
 * @return If the function succeeds, the return value is MobileRTCSDKError_Success. Otherwise the function fails. Fed,
 */
- (MobileRTCSDKError)setHideFeatureDisclaimers;

/**
 * @brief Is need explicit consent for AI custom Disclaimer. Only valid for \link @c MobileRTCReminderType_CustomAICompanionDisclaimer \endlink.
 * @return YES means explicit consent is required. Before agreeing to AIC disclaimer, the user's video and audio will be blocked. False means explicit consent is not required and video and audio will not be blocked.
 */
- (BOOL)isNeedExplicitConsent4AICustomDisclaimer;

@end


/**
 * @class MobileRTCDisclaimerBannerConfig
 * @brief Config for the simplify dislciamer banner.
 */
@interface MobileRTCDisclaimerBannerConfig: NSObject
/**
 * @brief Center of the simplify disclaimer banner.
 */
@property(nonatomic, assign) CGPoint center;
/**
 * @brief Background of the simplify disclaimer banner.
 */
@property(nonatomic, strong) UIColor * _Nullable backgroundColor;

@end

/**
 * @class MobileRTCReminderHelper
 */
@interface MobileRTCReminderHelper : NSObject

/**
 * @brief Callback to receive reminder events.
 */
@property (weak, nonatomic) id<MobileRTCReminderDelegate> _Nullable reminderDelegate;

/**
 * @brief Provide the simplify disclaimer banner UI's config for CustomUI.
 */
- (void)setDisclaimerBannerUIConfig:(MobileRTCDisclaimerBannerConfig *_Nonnull)config;

@end


