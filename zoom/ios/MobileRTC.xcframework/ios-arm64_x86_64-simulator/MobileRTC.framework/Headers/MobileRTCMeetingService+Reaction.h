/**
 * @file MobileRTCMeetingService+Reaction.h
 * @brief Meeting+Reaction service functionality and management.
 */

#import <MobileRTC/MobileRTC.h>

NS_ASSUME_NONNULL_BEGIN


/**
 * @brief Interface for managing emoji reactions and emoji feedback in Zoom SDK.
 */
@interface MobileRTCMeetingService (Reaction)

/**
 * @brief Determine if the Reaction feature is enabled.
 * @return YES means Reaction feature is enabled, otherwise not.
 */
- (BOOL)isEmojiReactionEnabled;

/**
 * @brief Send emoji reaction.
 * @param type - The type of the emoji reaction.
 * @return If the function succeeds, it will return @c MobileRTCSDKError_Succuss, otherwise not.
 * @warning MobileRTCEmojiReactionSkinTone doesn't work for MobileRTCEmojiReactionType_Heart type. To set MobileRTCEmojiReactionSkinTone, use -[MobileRTCMeetingSettings setReactionSkinTone] in MobileRTCMeetingSettings.h file.
 */
- (MobileRTCSDKError)sendEmojiReaction:(MobileRTCEmojiReactionType)type;

/**
 * @brief Send the emoji feedback.
 * @param type  Specify the emoji feedback type to be sent.
 * @return If the function succeeds, it will return MobileRTCMeetError_Success, otherwise not.
 */
- (MobileRTCSDKError)sendEmojiFeedback:(MobileRTCEmojiFeedbackType)type;

/**
 * @brief Cancel the emoji feedback.
 * @return If the function succeeds, it will return MobileRTCMeetError_Success, otherwise not.
 */
- (MobileRTCSDKError)cancelEmojiFeedback;
@end

NS_ASSUME_NONNULL_END
