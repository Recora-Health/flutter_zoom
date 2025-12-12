/**
 * @file MobileRTCShareSourceHelper.h
 * @brief Helper for managing screen sharing sources.
 */

#import <Foundation/Foundation.h>


/**
 * @class MobileRTCShareSourceHelper
 * @brief Manage external source for share video and share audio in meeting.
 */
@interface MobileRTCShareSourceHelper : NSObject

/**
 * @brief Start sharing external source.
 * @param shareDelegate The external source object pointer. Please See MobileRTCShareSourceDelegate.
 * @param audioDelegate .The external audio source object pointer.  Please See MobileRTCShareAudioSourceDelegate.
 * @return Return If the function succeeds, the return value is @c MobileRTCRawData_Success.
 * @warning If audioDelegate is non-null, it indicates sharinge user-defined audio at the same time.
 */
- (MobileRTCRawDataError)setExternalShareSource:(id<MobileRTCShareSourceDelegate> _Nullable)shareDelegate andAudioSource:(id <MobileRTCShareAudioSourceDelegate> _Nullable)audioDelegate;

@end

