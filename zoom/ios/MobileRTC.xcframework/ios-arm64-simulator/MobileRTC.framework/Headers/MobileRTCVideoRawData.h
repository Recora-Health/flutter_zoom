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
 * @brief The Y buffer pointer to a video's YUV data.
 */
@property (nonatomic, assign, nullable) char *yBuffer;

/**
 * @brief The U buffer pointer to a video's YUV data.
 */
@property (nonatomic, assign) char * _Nullable uBuffer;

/**
 * @brief The V buffer pointer to a video's YUV data.
 */
@property (nonatomic, assign) char * _Nullable vBuffer;

/**
 * @brief The video data size.
 */
@property (nonatomic, assign) CGSize size;

/**
 * @brief A pointer to a video's alpha data.
 */
@property (nonatomic, assign) char * _Nullable alphaBuffer;

/**
 * @brief The length of the alpha buffer data.
 */
@property (nonatomic, assign) unsigned int alphaBufferLen;

/**
 * @brief The raw data format of the video data.
 */
@property (nonatomic, assign) MobileRTCFrameDataFormat format;

/**
 * @brief The video data rotation.
 */
@property (nonatomic, assign) MobileRTCVideoRawDataRotation rotation;

/**
 * @brief The timestamp of the video data.
 */
@property(nonatomic, strong, nullable)  NSDate *timeStamp;

/**
 * @brief Determines if adding a reference is allowed.
 * @return YES if allowed. Otherwise, NO.
 */
- (BOOL)canAddRef;

/**
 * @brief Increases the reference count by 1.
 * @return YES if successfully added. Otherwise, NO.
 */
- (BOOL)addRef;

/**
 * @brief Decreases the reference count by 1.
 * @return If the function succeeds, it returns the reference count of this object.
 */
- (NSInteger)releaseRef;

@end

