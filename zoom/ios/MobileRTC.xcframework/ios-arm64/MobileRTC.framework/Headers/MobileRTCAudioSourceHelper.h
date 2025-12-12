/**
 * @file MobileRTCAudioSourceHelper.h
 * @brief Helper utilities for audiosource functionality.
 */

#import <Foundation/Foundation.h>


/**
 * @class MobileRTCAudioSourceHelper
 * @brief Configure external audio source as virtual microphone input.
 */
@interface MobileRTCAudioSourceHelper : NSObject

/**
 * @brief Set the delegate of virtual audio source.
 * @param audioSourceDelegate The delegate to receive callback.
 * @return If the function succeeds, it will return MobileRTCRawDataSuccess.
 */
- (MobileRTCRawDataError)setExternalAudioSource:(id <MobileRTCAudioSourceDelegate> _Nullable)audioSourceDelegate;

@end
