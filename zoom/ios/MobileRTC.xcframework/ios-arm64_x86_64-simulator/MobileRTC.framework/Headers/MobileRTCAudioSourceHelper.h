//
//  MobileRTCAudioSourceHelper.h
//  MobileRTC
//
//  Created by Zoom on 2022/7/25.
//  Copyright © Zoom Communications, Inc. All rights reserved.
//

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
