/**
 * @file MobileRTCRawLiveStreamInfo.h
 * @brief Raw live streaming information and configuration.
 */

#import <Foundation/Foundation.h>

/**
 * @class MobileRTCRawLiveStreamInfo
 * @brief Raw live stream information, such as the broadcast name and URL.
 */
@interface MobileRTCRawLiveStreamInfo : NSObject
/**
 * @brief User ID.
 */
@property(nonatomic, assign, readonly) NSUInteger userId;
/**
 * @brief Broadcast URL (hosted by you or the URL to your Zoom App Marketplace page).
 */
@property(nonatomic, copy, readonly) NSString * _Nullable broadcastUrl;

/**
 * @brief Broadcast Name.
 */
@property(nonatomic, copy, readonly) NSString * _Nullable broadcastName;

@end

