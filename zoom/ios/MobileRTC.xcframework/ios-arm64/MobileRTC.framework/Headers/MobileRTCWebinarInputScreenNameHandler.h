//
//  MobileRTCWebinarInputScreenNameHandler.h
//  MobileRTC
//
//  Created by Zoom on 2024/3/2.
//  Copyright © Zoom Communications, Inc. All rights reserved.
//

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
 */
- (MobileRTCSDKError)cancel;

@end

