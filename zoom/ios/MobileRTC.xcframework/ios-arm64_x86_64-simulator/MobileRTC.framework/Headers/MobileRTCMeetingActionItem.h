/**
 * @file MobileRTCMeetingActionItem.h
 * @brief Action item data structure for meeting actions and tasks.
 */

#import <Foundation/Foundation.h>

/**
 * @brief Add custom invitation action items to the meeting.
 */
typedef void (^MobileRTCMeetingInviteActionItemBlock)(void);

/**
 * @class MobileRTCMeetingInviteActionItem
 * @brief Add custom invitation action items to the meeting.
 */
@interface MobileRTCMeetingInviteActionItem : NSObject
/**
 * @brief The title of the custom invitation items.
 */
@property (nonatomic, retain, readwrite) NSString * _Nullable actionTitle;
/**
 * @brief Callback event of clicking the invitation item.
 */
@property (nonatomic, copy, readwrite) MobileRTCMeetingInviteActionItemBlock _Nullable actionHandler;

+(id _Nonnull )itemWithTitle:(NSString * _Nullable )inTitle Action:(MobileRTCMeetingInviteActionItemBlock _Nullable )actionHandler;

@end

/**
 * @protocol MobileRTCMeetingShareActionItemDelegate
 * @brief Add custom share action item to the meeting.
 */
@protocol MobileRTCMeetingShareActionItemDelegate <NSObject>
@required
- (void)onShareItemClicked:(NSUInteger)tag completion:(BOOL(^_Nonnull)(UIViewController * _Nonnull shareView))completion;
@end

/**
 * @class MobileRTCMeetingShareActionItem
 * @brief Add custom sharing action items to the meeting.
 */
@interface MobileRTCMeetingShareActionItem : NSObject
/**
 * @brief The title of the custom content to share, like screen, application, photos, etc. 
 */ 
@property (nonatomic, retain, readwrite) NSString * _Nonnull actionTitle;

/**
 * @brief The tag of MobileRTCMeetingShareActionItem.
 */
@property (nonatomic, assign, readwrite) NSUInteger tag;
/**
 * @brief Enable the share via MobileRTCMeetingShareActionItemDelegate.
 */
@property (nonatomic, assign, readwrite) id<MobileRTCMeetingShareActionItemDelegate> _Nonnull delegate;

+(id _Nonnull )itemWithTitle:(NSString * _Nonnull)inTitle Tag:(NSUInteger)tag;
@end
