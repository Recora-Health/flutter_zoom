//
//  MobileRTCLiveTranscriptionLanguage.h
//  MobileRTC
//
//  Created by Zoom on 2022/5/30.
//  Copyright © Zoom Communications, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * @class MobileRTCLiveTranscriptionLanguage
 * @brief Represent interpretation language information.
 */
@interface MobileRTCLiveTranscriptionLanguage : NSObject

/**
 * @brief Language id of transcription language.
 */
@property(nonatomic, assign, readonly) NSInteger languageID;

/**
 * @brief Localized language name of transcription language.
 */
@property(nonatomic, copy, readonly) NSString * _Nullable languageName;

@end

NS_ASSUME_NONNULL_END
