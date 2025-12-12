/**
 * @file MobileRTCVideoRawData.h
 * @brief Raw video data handling for custom video processing.
 */

#import <Foundation/Foundation.h>

/**
 * @class MobileRTCVideoRawData
 * @brief Represents raw data received from subscribed video stream.
 */
@interface MobileRTCVideoRawData : NSObject

/**
 * @brief The y-data pointer to a video's YUV data.
 */
@property (nonatomic, assign, nullable) char *yBuffer;

/**
 * @brief The u-data data pointer to a video's YUV data.
 */
@property (nonatomic, assign) char * _Nullable uBuffer;

/**
 * @brief The v-data data pointer to a video's YUV data.
 */
@property (nonatomic, assign) char * _Nullable vBuffer;

/**
 * @brief The video data's size.
 */
@property (nonatomic, assign) CGSize size;

/**
 * @brief The data pointer to a video's alpha data.
 */
@property (nonatomic, assign) char * _Nullable alphaBuffer;

/**
 * @brief The alpha buffer data length.
 */
@property (nonatomic, assign) unsigned int alphaBufferLen;

/**
 * @brief The video data's raw data format.
 */
@property (nonatomic, assign) MobileRTCFrameDataFormat format;

/**
 * @brief The video data's rotation.
 */
@property (nonatomic, assign) MobileRTCVideoRawDataRotation rotation;

/**
 * @brief TimeStamp of video data.
 */
@property(nonatomic, strong, nullable)  NSDate *timeStamp;

/**
 * @brief Whether adding a reference is allowed.
 * @return YES if allow. Otherwise, false.
 */
- (BOOL)canAddRef;

/**
 * @brief Add to reference count.
 * @return YES if successfully added. Otherwise, this returns false.
 */
- (BOOL)addRef;

/**
 * @brief Subtract from reference count.
 * @return If the function succeeds, it will return reference count of this object.
 */
- (NSInteger)releaseRef;

@end

