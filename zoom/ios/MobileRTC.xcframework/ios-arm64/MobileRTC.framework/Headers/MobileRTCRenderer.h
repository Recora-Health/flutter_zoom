/**
 * @file MobileRTCRenderer.h
 * @brief Video rendering functionality and display management.
 */

#import <Foundation/Foundation.h>
#import <MobileRTC/MobileRTCMeetingDelegate.h>

/**
 * @class MobileRTCRenderer
 */
@interface MobileRTCRenderer : NSObject

/**
 * @brief MobileRTCRenderer's user ID.
 */
@property (nonatomic, assign, readonly) NSUInteger userId;

/**
 * @brief MobileRTCRenderer's video type.
 */
@property (nonatomic, assign, readonly) MobileRTCVideoType videoType;

/**
 * @brief MobileRTCRenderer's video resolution.
 */
@property (nonatomic, assign, readonly) MobileRTCVideoResolution resolution;

/**
 * @brief Initialize MobileRTCRenderer.
 * @param delegate - The delegate to receive callbacks.
 * @return The MobileRTCRenderer object.
 */
- (instancetype _Nonnull)initWithDelegate:(id<MobileRTCVideoRawDataDelegate>_Nonnull) delegate;

/**
 * @brief Call the function to set video resolution.
 * @return If the function succeeds, the return value is MobileRTCRawData_Success. Otherwise, the function fails and returns null.
 */
- (MobileRTCRawDataError)setRawDataResolution:(MobileRTCVideoResolution)resolution;

/**
 * @brief Call the function to subscribe to raw video data.
 * @return If the function succeeds, the return value is @c MobileRTCRawData_Success. Otherwise, the function fails and returns null.
 * @note Before entering the meeting, subscribe to your preview video data with userId = 0.
 * @note If you are already in the meeting, subscribe to your own video data using the real userId or userId = 0.
 */
- (MobileRTCRawDataError)subscribe:(NSUInteger)userId videoType:(MobileRTCVideoType)type;

/**
 * @brief Call the function to unsubscribe from raw video data.
 * @return If the function succeeds, the return value is MobileRTCRawData_Success. Otherwise, the function fails and returns null.
 */
- (MobileRTCRawDataError)unSubscribe;

@end

