/**
 * @file MobileRTCCallCountryCode.h
 * @brief Country code definitions for phone calls.
 */

#import <Foundation/Foundation.h>

/**
 * @class MobileRTCCallCountryCode
 * @brief Provides information of countries that support calling.
 */
@interface MobileRTCCallCountryCode : NSObject
/**
 * @brief Get the ID of the country where a user can dial in.The country ID. (e.g. US, CA, etc.).
 */
@property (nonatomic, copy) NSString * _Nullable countryId;
/**
 * @brief Get the country name.
 */
@property (nonatomic, copy) NSString * _Nullable countryName;
/**
 * @brief Get the country code.
 */
@property (nonatomic, copy) NSString * _Nullable countryCode;
/**
 * @brief Get the country number.
 */
@property (nonatomic, copy) NSString * _Nullable countryNumber;
/**
 * @brief Whether free.
 */
@property (nonatomic, assign) BOOL tollFree;

@end
