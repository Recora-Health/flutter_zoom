/**
 * @file MobileRTCRoomDevice.h
 * @brief Room device management and configuration.
 */

#import <Foundation/Foundation.h>

/**
 * @brief Enumeration of room device types.
 */
typedef enum {
    /** H.323 device. */
    MobileRTCDeviceType_H323  = 1,
    /** SIP device. */
    MobileRTCDeviceType_SIP,
    /** Both H.323 and SIP device. */
    MobileRTCDeviceType_Both,
}MobileRTCDeviceType;

/**
 * @brief Enumeration of H.323/SIP encryption types.
 */
typedef enum {
    /** Meeting room system is not encrypted. */
    MobileRTCDeviceEncryptType_None   = 0,
    /** Meeting room system is encrypted. */
    MobileRTCDeviceEncryptType_Encrypt,
    /** Meeting room system is encrypted automatically. */
    MobileRTCDeviceEncryptType_Auto,
}MobileRTCDeviceEncryptType;

/**
 * @class MobileRTCRoomDevice
 * @brief Represents H.323 device information used in Zoom meetings.
 */
@interface MobileRTCRoomDevice : NSObject

/**
 * @brief Get or set the name of the H.323 device.
 */
@property (nonatomic, copy) NSString * _Nullable deviceName;
/**
 * @brief Get or set the IP address of the H.323 device.
 */
@property (nonatomic, copy) NSString * _Nullable ipAddress;
/**
 * @brief Get or set the E.164 number of the H.323 device.
 */
@property (nonatomic, copy) NSString * _Nullable e164num;
/**
 * @brief Get or set the type of the H.323 device.
 */
@property (nonatomic, assign) MobileRTCDeviceType deviceType;
/**
 * @brief Get or set the encryption type used by the H.323 device.
 */
@property (nonatomic, assign) MobileRTCDeviceEncryptType encryptType;

@end
