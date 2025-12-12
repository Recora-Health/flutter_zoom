/**
 * @file MobileRTCInMeetingDeviceInfo.h
 * @brief Device information and capabilities during meetings.
 */

#import <Foundation/Foundation.h>
/**
 * @class MobileRTCInMeetingDeviceInfo
 * @brief Information of meeting device info.
 */
@interface MobileRTCInMeetingDeviceInfo : NSObject
/**
 * @brief Index.
 * @deprecated Please use meetingId instead.
 */
@property(nonatomic, assign, readonly) NSInteger index DEPRECATED_MSG_ATTRIBUTE("Please use meetingId instead");
/**
 * @brief Device name.
 */
@property(nonatomic, copy, readonly) NSString * _Nullable deviceName;
/**
 * @brief Meeting topic.
 */
@property(nonatomic, copy, readonly) NSString * _Nullable meetingTopic;
/**
 * @brief Meeting number.
 */
@property(nonatomic, assign, readonly) NSUInteger meetingNumber;
/**
 * @brief Meeting id.
 */
@property(nonatomic, copy, readonly) NSString * _Nullable meetingId;
/**
 * @brief This meeting support joining in companion mode.
 */
@property(nonatomic, assign) BOOL isSupportCompanionMode;

@end
