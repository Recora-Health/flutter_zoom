/**
 * @file MobileRTCSMSService.h
 * @brief SMS service for phone number verification and messaging.
 */

#import <Foundation/Foundation.h>
#import <MobileRTC/MobileRTCMeetingDelegate.h>

/**
 * @class MobileRTCRealNameCountryInfo
 * @brief For real name auth usage.
 * @warning Country code will used in retrieve and verify handler.
 */
@interface MobileRTCRealNameCountryInfo : NSObject
@property (nonatomic, copy) NSString * _Nullable countryId;
@property (nonatomic, copy) NSString * _Nullable countryName;
@property (nonatomic, copy) NSString * _Nullable countryCode;
@end

/**
 * @class MobileRTCRetrieveSMSHandler
 * @brief For send SMS usage.
 * @warning If retrieve return NO, please get new retrieve handler 60s later. 'getResendSMSVerificationCodeHandler' in 'MobileRTCSMSService'.
 */
@interface MobileRTCRetrieveSMSHandler : NSObject
/**
 * @brief CountryCode, counry code in country code list.
 * @param phoneNum your phone number.
 * @return If the function succeeds, the return value is YES. Otherwise not.
 * @warning If retrieve return NO, please get new retrieve handler 60s later. 'getResendSMSVerificationCodeHandler' in 'MobileRTCSMSService'.
 */
- (BOOL)retrieve:(NSString * _Nullable)countryCode andPhoneNumber:(NSString * _Nullable)phoneNum;

/**
 * @brief CancelAndLeaveMeeting sms.
 * @return If the function succeeds, the return value is YES. Otherwise not.
 * @warning Cancel and leavemb meeting.
 */
- (BOOL)cancelAndLeaveMeeting;
@end

/**
 * @class MobileRTCVerifySMSHandler
 * @brief For verify SMS usage.
 * @warning If verify return NO, please get new retrieve handler 60s later.  'getReVerifySMSVerificationCodeHandler' in 'MobileRTCSMSService'.
 */
@interface MobileRTCVerifySMSHandler : NSObject
/**
 * @brief CountryCode, counry code in country code list.
 * @param phoneNum your phone number.
 * @param verifyCode your received verify code.
 * @return If the function succeeds, the return value is YES. Otherwise not.
 * @warning If verify return NO, please get new verify handler 60s later. 'getReVerifySMSVerificationCodeHandler' in 'MobileRTCSMSService'.
 */
- (BOOL)verify:(NSString * _Nullable)countryCode phoneNumber:(NSString * _Nullable)phoneNum andVerifyCode:(NSString * _Nullable)verifyCode;

/**
 * @brief CancelAndLeaveMeeting sms.
 * @return If the function succeeds, the return value is YES. Otherwise not.
 * @warning Cancel and leavemb meeting.
 */
- (BOOL)cancelAndLeaveMeeting;
@end


/**
 * @class MobileRTCSMSService
 * @brief For SMS service usage like following flow.
 * @warning 1.need enable sms service by 'enableZoomAuthRealNameMeetingUIShown'.
 * @warning 2.try to join meeting or start meeting. if Real Name verify not pass, will call the callback 'onNeedRealNameAuth: privacyURL: retrieveHandle:'.
 * @warning 3.try to send sms with retrieveHandle, or you can use the retrieve handle cancel and leave the meeting, 'cancelAndLeaveMeeting'.
 * @warning 4.if success in step 3, pop up the dialog for input the verify code, in the same time, you will receive a sms and a callback 'onRetrieveSMSVerificationCodeResultNotification: verifyHandle:'.
 * @warning If failed, please try to get retrieve handle 60s later, and go to step 3.
 * @warning 5.you can verify sms by verifyHandle. or you can cancel and leave meeting. 'cancelAndLeaveMeeting'.
 * @warning 6.you will receive callback 'onVerifySMSVerificationCodeResultNotification:' for the verify result.
 */
@interface MobileRTCSMSService : NSObject
@property (weak, nonatomic) id<MobileRTCSMSServiceDelegate> _Nullable delegate;

/**
 * @brief Enable, pass YES for using the auth real name service. the call back function will called when need.(Judged by sdk logic).
 * @warning Enable/disable auth real name service.
 */
- (void)enableZoomAuthRealNameMeetingUIShown:(bool)enable;

/**
 * @brief For get new retrieve handle.
 * @return If the function succeeds, the return value is MobileRTCRetrieveSMSHandler. Otherwise not.
 * @warning Need get new handle 60s later.
 */
- (MobileRTCRetrieveSMSHandler * _Nullable)getResendSMSVerificationCodeHandler;

/**
 * @brief For get new verify handle.
 * @return If the function succeeds, the return value is MobileRTCVerifySMSHandler. Otherwise not.
 * @warning Need get new handle 60s later.
 */
- (MobileRTCVerifySMSHandler * _Nullable)getReVerifySMSVerificationCodeHandler;

/**
 * @brief GetSupportPhoneNumberCountryList.
 * @return If the function succeeds, will get the support country list.
 * @warning Get country code iist after call join meeting or start meeting interface.
 */
- (NSArray <MobileRTCRealNameCountryInfo *> * _Nullable)getSupportPhoneNumberCountryList;

/**
 * @brief Set default cellphone for signed account.
 * @param countryCode the user account's country code.
 * @param phoneNum default phoen number.
 * @return YES for set success.
 */
- (BOOL)setDefaultCellPhoneInfo:(NSString * _Nullable)countryCode phoneNum:(NSString * _Nullable)phoneNum;

@end
