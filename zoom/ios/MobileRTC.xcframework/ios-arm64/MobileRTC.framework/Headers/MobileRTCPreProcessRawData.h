/**
 * @file MobileRTCPreProcessRawData.h
 * @brief Raw data preprocessing utilities.
 */

#import <Foundation/Foundation.h>

/**
 * @class MobileRTCPreProcessRawData
 * @brief The YUV video frame data.
 */
@interface MobileRTCPreProcessRawData : NSObject

/**
 * @brief The size of video data.
 */
@property (nonatomic, assign) CGSize size;

/**
 * @brief Y data pointer of video's YUV data stride.
 */
@property (nonatomic, assign) int yStride;

/**
 * @brief U data pointer of video's YUV data stride.
 */
@property (nonatomic, assign) int uStride;

/**
 * @brief V data pointer of video's YUV data stride.
 */
@property (nonatomic, assign) int vStride;

/**
 * @brief Y data pointer of video's YUV data.
 * @return If the function succeeds, it will return the Y buffer of this data.
 */
- (char *)getYBuffer:(int)lineNum;

/**
 * @brief U data pointer of video's YUV data.
 * @return If the function succeeds, it will return the U buffer of this data.
 */
- (char *)getUBuffer:(int)lineNum;

/**
 * @brief V data pointer of video's YUV data.
 * @return If the function succeeds, it will return the V buffer of this data.
 */
- (char *)getVBuffer:(int)lineNum;

/**
 * @brief The raw data format of video data.
 */
@property (nonatomic, assign) MobileRTCFrameDataFormat format;

/**
 * @brief The direction of video data.
 */
@property (nonatomic, assign) MobileRTCVideoRawDataRotation rotation;

@end

