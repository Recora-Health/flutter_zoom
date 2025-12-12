/**
 * @file MobileRTCAudioRawDataHelper.h
 * @brief Helper utilities for audio raw data processing and management.
 */

#import <Foundation/Foundation.h>

/**
 * @class MobileRTCAudioRawDataHelper
 * @brief Helper to subscribe or unsubscribe audio raw data.
 */
@interface MobileRTCAudioRawDataHelper : NSObject
/**
 * @brief Call the function to initialize MobileRTCAudioRawDataHelper.
 * @param delegate Specify the delegate to receive the callback.
 * @return The MobileRTCAudioRawDataHelper object.
 */
- (instancetype _Nonnull)initWithDelegate:(id<MobileRTCAudioRawDataDelegate>_Nonnull) delegate;

/**
 * @brief Call the function to start audio rawdata.
 * @return If the function succeeds, it will return MobileRTCRawData_Success. Otherwise the function fails.
 */
-(MobileRTCRawDataError)subscribe;

/**
 * @brief Call the function to stop audio rawdata.
 * @return If the function succeeds, it will return MobileRTCRawData_Success. Otherwise the function fails.
 */
- (MobileRTCRawDataError)unSubscribe;

@end
