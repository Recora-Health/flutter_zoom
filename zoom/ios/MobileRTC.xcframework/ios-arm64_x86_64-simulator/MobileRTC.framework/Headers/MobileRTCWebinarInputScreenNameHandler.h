/**
 * @file MobileRTCWebinarInputScreenNameHandler.h
 * @brief Handler for webinar screen name input.
 */

/**
 * @class MobileRTCWebinarInputScreenNameHandler
 * @brief Handler for entering screen name when joining a webinar.
 */
@interface MobileRTCWebinarInputScreenNameHandler : NSObject
/**
 * @brief Input  screen name to join the webinar.
 * @param name The display name for the webinar.
 * @return If the function succeeds, it return MobileRTCSDKError_Success. Otherwise fails.
 */
- (MobileRTCSDKError)inputName:(NSString *_Nonnull)name;

/**
 * @brief Cancel to join webinar.
 * @return If the function succeeds, it will return MobileRTCSDKError_Success. Otherwise the function fails.
 */
- (MobileRTCSDKError)cancel;

@end

