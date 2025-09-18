//
//  MobileRTCAudioRawData.h
//  MobileRTC
//
//  Created by Zoom Communications on 2019/8/6.
//  Copyright © Zoom Communications, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * @class MobileRTCAudioRawData
 * @brief Represents audio raw data received from the SDK.
 */
@interface MobileRTCAudioRawData : NSObject

/**
 * @brief Data pointer of audio buffer data.
 */
@property (nonatomic, assign) char * _Nullable buffer;

/**
 * @brief Audio buffer data lenth.
 */
@property (nonatomic, assign) NSInteger bufferLen;

/**
 * @brief Audio sampling rate.
 */
@property (nonatomic, assign) NSInteger sampleRate;

/**
 * @brief Number of audio channels.
 */
@property (nonatomic, assign) NSInteger channelNum;

/**
 * @brief TimeStamp of audio data.
 */
@property(nonatomic, strong, nullable)  NSDate *timeStamp;

/**
 * @brief Can add reference count or not.
 */
- (BOOL)canAddRef;

/**
 * @brief Add reference count.
 */
- (BOOL)addRef;

/**
 * @brief Minus reference count.
 */
- (NSInteger)releaseRef;

@end

