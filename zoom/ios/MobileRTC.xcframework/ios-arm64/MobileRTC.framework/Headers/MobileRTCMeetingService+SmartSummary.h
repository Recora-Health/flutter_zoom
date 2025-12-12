/**
 * @file MobileRTCMeetingService+SmartSummary.h
 * @brief Meeting+SmartSummary service functionality and management.
 */

#import <MobileRTC/MobileRTC.h>

/**
 * @class MobileRTCSmartSummaryPrivilegeHandler
 * @brief Interface to handle start smart summary request.
 */
@interface MobileRTCSmartSummaryPrivilegeHandler : NSObject
/**
 * @brief Agree the start smart summary request.
 * @return If the function succeeds, the return value is @c MobileRTCSDKError_Success, otherwise the function fails.
 * @deprecated Use MobileRTCAICompanionSmartSummaryHelper instead.
 */
- (MobileRTCSDKError)accept DEPRECATED_MSG_ATTRIBUTE("Use MobileRTCAICompanionSmartSummaryHelper instead");

/**
 * @brief Decline the start smart summary request.
 * @return If the function succeeds, the return value is @c MobileRTCSDKError_Success, otherwise the function fails.
 * @deprecated Use MobileRTCAICompanionSmartSummaryHelper instead.
 */
- (MobileRTCSDKError)decline DEPRECATED_MSG_ATTRIBUTE("Use MobileRTCAICompanionSmartSummaryHelper instead");

/**
 * @brief Ignore the start smart summary request.
 * @deprecated Use MobileRTCAICompanionSmartSummaryHelper instead.
 */
- (void)ignore DEPRECATED_MSG_ATTRIBUTE("Use MobileRTCAICompanionSmartSummaryHelper instead");
@end

/**
 * @brief This class provides interfaces to manage and control the smart summary feature in meetings.
 */
@interface MobileRTCMeetingService (SmartSummary)

/**
 * @brief Determine if current meeting support smart summary feature.
 * @return YES means the current meeting supports the smart summary feature, false means the feature is not supported.
 * @deprecated Use MobileRTCAICompanionSmartSummaryHelper instead.
 */
- (BOOL)isSmartSummarySupported DEPRECATED_MSG_ATTRIBUTE("Use MobileRTCAICompanionSmartSummaryHelper instead");

/**
 * @brief Determine if the smart summary feature is enabled in the meeting.
 * @return YES means smart summary feature is enabled.
 * @deprecated Use MobileRTCAICompanionSmartSummaryHelper instead.
 */
- (BOOL)isSmartSummaryEnabled DEPRECATED_MSG_ATTRIBUTE("Use MobileRTCAICompanionSmartSummaryHelper instead");

/**
 * @brief Whether the current user can request the host to start the smart summary for the current meeting.
 * @return If the function succeeds, the return value is MobileRTCSDKError_Success. Otherwise the function fails.
 * @deprecated Use MobileRTCAICompanionSmartSummaryHelper instead.
 */
- (MobileRTCSDKError)canRequestStartSmartSummary DEPRECATED_MSG_ATTRIBUTE("Use MobileRTCAICompanionSmartSummaryHelper instead");

/**
 * @brief Request the host to start the smart summary for the current meeting.
 * @return If the function succeeds, the return value is @c MobileRTCSDKError_Success. Otherwise the function fails.
 * @deprecated Use MobileRTCAICompanionSmartSummaryHelper instead.
 */
- (MobileRTCSDKError)requestStartSmartSummary DEPRECATED_MSG_ATTRIBUTE("Use MobileRTCAICompanionSmartSummaryHelper instead");

/**
 * @brief Whether the current user is able to start smart summary.
 * @return If the function succeeds, the return value is @c MobileRTCSDKError_Success. Otherwise the function fails.
 * @deprecated Use MobileRTCAICompanionSmartSummaryHelper instead.
 */
- (MobileRTCSDKError)canStartSmartSummary DEPRECATED_MSG_ATTRIBUTE("Use MobileRTCAICompanionSmartSummaryHelper instead");

/**
 * @brief Start smart summary.
 * @return If the function succeeds, the return value is @c MobileRTCSDKError_Success. Otherwise the function fails.
 * @deprecated Use MobileRTCAICompanionSmartSummaryHelper instead".
 */
- (MobileRTCSDKError)startSmartSummary DEPRECATED_MSG_ATTRIBUTE("Use MobileRTCAICompanionSmartSummaryHelper instead");

/**
 * @brief Stop smart summary.
 * @return If the function succeeds, the return value is @c MobileRTCSDKError_Success. Otherwise the function fails.
 * @deprecated Use MobileRTCAICompanionSmartSummaryHelper instead.
 */
- (MobileRTCSDKError)stopSmartSummary DEPRECATED_MSG_ATTRIBUTE("Use MobileRTCAICompanionSmartSummaryHelper instead");

/**
 * @brief Query whether smart summary is started.
 * @return YES means smart summary is started, false means it has not.
 * @deprecated Use MobileRTCAICompanionSmartSummaryHelper instead.
 */
- (BOOL)isSmartSummaryStarted DEPRECATED_MSG_ATTRIBUTE("Use MobileRTCAICompanionSmartSummaryHelper instead");

@end

