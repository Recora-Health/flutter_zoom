/**
 * @file MobileRTCMeetingService+RawArchiving.h
 * @brief Meeting+RawArchiving service functionality and management.
 */

#import <MobileRTC/MobileRTC.h>

/**
 * @brief Interface for managing raw archiving privilege in Zoom SDK.
 */
@interface MobileRTCMeetingService (RawArchiving)

/**
 * @brief Start raw archiving and get raw data receive previlege.
 * @return YES if start raw archiving succeeds. Otherwise failed.
 */
- (BOOL)startRawArchiving;

/**
 * @brief Stop raw archiving and revoke rawdata receive previlege.
 * @return YES if stop raw archiving succeeds. Otherwise failed.
 */
- (BOOL)stopRawArchiving;

@end

