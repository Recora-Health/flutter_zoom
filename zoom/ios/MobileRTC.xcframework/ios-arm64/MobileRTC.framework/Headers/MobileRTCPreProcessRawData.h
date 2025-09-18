//
//  MobileRTCPreProcessRawData.h
//  MobileRTC
//
//  Created by Zoom Communications on 2020/2/26.
//  Copyright © Zoom Communications, Inc. All rights reserved.
//

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
 * @brief Y data pointer of video's YUV data .
 */
- (char *)getYBuffer:(int)lineNum;

/**
 * @brief U data pointer of video's YUV data .
 */
- (char *)getUBuffer:(int)lineNum;

/**
 * @brief V data pointer of video's YUV data .
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

