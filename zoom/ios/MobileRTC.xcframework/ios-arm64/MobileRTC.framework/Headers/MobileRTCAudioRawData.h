/**
 * @file MobileRTCAudioRawData.h
 * @brief Raw audio data handling for custom audio processing.
 */

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
 * @return If can add ref, it will return YES. Otherwise NO.
 */
- (BOOL)canAddRef;

/**
 * @brief Add reference count.
 * @return If the function succeeds, it will return YES. Otherwise NO.
 */
- (BOOL)addRef;

/**
 * @brief Minus reference count.
 * @return If the function succeeds, it will return reference count of this object.
 */
- (NSInteger)releaseRef;

@end

