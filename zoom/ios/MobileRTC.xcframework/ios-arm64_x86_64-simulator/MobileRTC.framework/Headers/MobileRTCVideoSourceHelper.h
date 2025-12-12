/**
 * @file MobileRTCVideoSourceHelper.h
 * @brief Helper for managing video sources and capture.
 */

#import <Foundation/Foundation.h>

/**
 * @class MobileRTCVideoSourceHelper
 */
@interface MobileRTCVideoSourceHelper : NSObject

/**
 * @brief This method is used to preprocess video's YUV420 data before rendering receive.
 * @param delegate please See MobileRTCPreProcessorDelegate.
 * @return If the function succeeds, it will return MobileRTCRawDataError_Success. Otherwise the function fails.
 * @warning Set nil stop preProcessor.
 */
-(MobileRTCRawDataError)setPreProcessor:(id<MobileRTCPreProcessorDelegate>) delegate;

/**
 * @brief This method is used to send your own video rawdata.
 * @param delegate please See MobileRTCVideoSourceDelegate.
 * @return If the function succeeds, it will return MobileRTCRawDataError_Success. Otherwise the function fails.
 * @warning Set nil for Switch to internal video source.
 */
-(MobileRTCRawDataError)setExternalVideoSource:(id<MobileRTCVideoSourceDelegate>)delegate;

@end
