/**
 * @file MobileRTCAICQueryHelper.h
 * @brief AI Companion query helper for intelligent meeting features.
 */

#import <Foundation/Foundation.h>

/**
 * @brief Enumeration of the types of feedback for AI Companion query responses.
 */
typedef NS_ENUM(NSUInteger, MobileRTCAICompanionQueryFeedbackType) {
    /** For initialization. */
    MobileRTCAICompanionQueryFeedbackType_None = 0,
    /** Indicates the feedback is positive, the query response was good. */
    MobileRTCAICompanionQueryFeedbackType_Good,
    /** Indicates the feedback is negative, the query response was bad. */
    MobileRTCAICompanionQueryFeedbackType_Bad
};

/**
 * @brief Enumeration of the error types for AI Companion query requests.
 */
typedef NS_ENUM(NSUInteger, MobileRTCAICompanionQueryRequestError) {
    /** The request was successful, no error. */
    MobileRTCAICompanionQueryRequestError_OK = 0,
    /** Invalid parameter provided in the query request. */
    MobileRTCAICompanionQueryRequestError_InvalidParam,
    /** The request failed to be sent. */
    MobileRTCAICompanionQueryRequestError_SendFailed,
    /** The web service is unavailable. */
    MobileRTCAICompanionQueryRequestError_WebUnAvailable,
    /** Permission verification failed for the query request. */
    MobileRTCAICompanionQueryRequestError_PermissionVerifyFailed,
    /** The query request exceeded the rate limit. */
    MobileRTCAICompanionQueryRequestError_QueryRateLimitError,
    /** The query request timed out. */
    MobileRTCAICompanionQueryRequestError_Timeout,
    /** An unknown error occurred. */
    MobileRTCAICompanionQueryRequestError_Unknown = 100
};

/**
 * @brief Enumeration of configuration options for who in the meeting can interact with AI Companion by asking questions about the meeting. For more information, please visit <https://support.zoom.com/hc/en/article?id=zm_kb&sysparm_article=KB0057749>.
 */
typedef NS_ENUM(NSUInteger, MobileRTCAICompanionQuerySettingOptions) {
    /** For initialization. */
    MobileRTCAICompanionQuerySettingOptions_None = 0,
    /** Allows all participants and attendee to ask questions about all discussions since AI Companion was active. */
    MobileRTCAICompanionQuerySettingOptions_WhenQueryStarted,
    /** Allows all participants to ask questions about the discussion since they joined the current meeting. */
    MobileRTCAICompanionQuerySettingOptions_WhenParticipantsJoin,
    /** Allow only the host, alternative host, and users with host privileges assigned before the meeting starts to ask questions about all discussions since AI Companion is active. */
    MobileRTCAICompanionQuerySettingOptions_OnlyHost,
    /** Allows only participants and invitees from your organization to ask questions about all discussions since AI Companion was active. */
    MobileRTCAICompanionQuerySettingOptions_ParticipantsAndInviteesInOurOrganization,
    /** Allows only participants from your organization to ask questions about the discussion since they joined the current meeting. */
    MobileRTCAICompanionQuerySettingOptions_WhenParticipantsAndOrganizationJoin,
    /** Hosts and all panelists can ask question, and answers are based on the meeting's start until now. */
    MobileRTCAICompanionQuerySettingOptions_HostAndPanelists = 10,
    /** Hosts and all panelists in our organization can ask question, and answers are based on the meeting's start until now. */
    MobileRTCAICompanionQuerySettingOptions_HostAndPanelistsInOurOrganization
};

/**
 * @class MobileRTCAICompanionQueryItem
 * @brief Represents a query item including question, answer, and error information for AI Companion.
 */
@interface MobileRTCAICompanionQueryItem : NSObject
/**
 * @brief Get the query question content.
 */
@property(nonatomic, copy, readonly, nullable) NSString* qustionContent;
/**
 * @brief Get the query question ID.
 */
@property(nonatomic, copy, readonly, nullable) NSString* queryID;

/**
 * @brief Get the query answer content.
 */
@property(nonatomic, copy, readonly, nullable) NSString* answerContent;

/**
 * @brief Get the error code.
 */
@property(nonatomic, assign, readonly) MobileRTCAICompanionQueryRequestError errorCode;

/**
 * @brief Get the error message.
 */
@property(nonatomic, copy, readonly, nullable) NSString* errorMsg;

/**
 * @brief Get the timestamp.
 */
@property(nonatomic, strong, readonly, nullable) NSDate *timestamp;

/**
 * @brief Send feedback of query answer.
 * @param feedbackType The feedback type.
 * @return If the function succeeds, it will return MobileRTCSDKError_Success. Otherwise the function fails.
 */
- (MobileRTCSDKError)feedback:(MobileRTCAICompanionQueryFeedbackType)feedbackType;
@end

/**
 * @class MobileRTCEnableQueryHandler
 * @brief Handler to enable the meeting query feature.
 */
@interface MobileRTCEnableQueryHandler : NSObject
/**
 * @brief Enable meeting query.
 * @return If the function succeeds, it will return MobileRTCSDKError_Success. Otherwise the function fails.
 */
- (MobileRTCSDKError)enableQuery;

/**
 * @brief Determine if this handler for request enable query.
 * @return YES means this handler is for request enable query. Otherwise it returns NO means this handler is for enable query directly.
 */
- (BOOL)isForRequest;

@end

/**
 * @class MobileRTCStartQueryHandler
 * @brief Handler to start the meeting query feature.
 */
@interface MobileRTCStartQueryHandler : NSObject
/**
 * @brief Start meeting query.
 * @return If the function succeeds, it will return MobileRTCSDKError_Success. Otherwise the function fails.
 */
- (MobileRTCSDKError)startMeetingQuery;

/**
 * @brief Determine if this handler for request enable query.
 * @return YES means this handler is for request enable query. Otherwise it returns NO and is not available.
 */
- (BOOL)isForRequest;

@end

/**
 * @class MobileRTCApproveEnableQueryHandler
 * @brief Handler to approve or continue enabling query request.
 */
@interface MobileRTCApproveEnableQueryHandler : NSObject
/**
 * @brief Get the requester's user ID.
 */
@property (nonatomic, assign) NSUInteger senderUserID;

/**
 * @brief Continue approve action.
 * @return If the function succeeds, it returns MobileRTCSDKError_Success. Otherwise the function fails.
 */
- (MobileRTCSDKError)continueApprove;
@end

/**
 * @class MobileRTCApproveStartQueryHandler
 * @brief Handler to start the meeting query feature.
 */
@interface MobileRTCApproveStartQueryHandler : NSObject
/**
 * @brief Get the requester's user ID.
 */
@property (nonatomic, assign, readonly) NSUInteger senderUserID;
/**
 * @brief Approve the request.
 * @return If the function succeeds, it returns MobileRTCSDKError_Success. Otherwise the function fails.
 */
- (MobileRTCSDKError)approve;

/**
 * @brief Decline the request.
 * @return If the function succeeds, it returns MobileRTCSDKError_Success. Otherwise the function fails.
 */
- (MobileRTCSDKError)decline;

@end

/**
 * @class MobileRTCSendQueryHandler
 * @brief Handler for sending queries during the meeting.
 */
@interface MobileRTCSendQueryHandler : NSObject

/**
 * @brief Get  default query questions.
 * @return If the function succeeds, it returns the array of questions. Otherwise the function fails and returns nothing.
 */
- (NSArray<NSString *> *_Nullable)getDefaultQueryQuestions;

/**
 * @brief Send query question.
 * @return If the function succeeds, it returns MobileRTCSDKError_Success. Otherwise the function fails.
 */
- (MobileRTCSDKError)sendQueryQuestion:(NSString * _Nullable)question;

/**
 * @brief Stop meeting query.
 * @return If the function succeeds, it returns MobileRTCSDKError_Success. Otherwise the function fails.
 */
- (MobileRTCSDKError)stopMeetingQuery;

/**
 * @brief Deterine if can send query.
 * @return YES means can, otherwise not.
 */
- (BOOL)canSendQuery;

/**
 * @brief Request send query privilege.
 * @return If the function succeeds, it returns MobileRTCSDKError_Success Otherwise the function fails.
 */
- (MobileRTCSDKError)requestSendQueryPrivilege;

@end

/**
 * @class MobileRTCApproveSendQueryHandler
 * @brief Handler to approve or decline the send query request.
 */
@interface MobileRTCApproveSendQueryHandler : NSObject
/**
 * @brief Get the requester's user ID.
 */
@property (nonatomic, assign) NSUInteger senderUserID;

/**
 * @brief Approve the request.
 * @return If the function succeeds, it returns MobileRTCSDKError_Success. Otherwise the function fails.
 */
- (MobileRTCSDKError)approve;

/**
 * @brief Decline the request.
 * @param declineAll YES means decline all request.
 * @return If the function succeeds, it returns MobileRTCSDKError_Success. Otherwise the function fails.
 */
- (MobileRTCSDKError)decline:(BOOL)declineAll;
@end

/**
 * @class MobileRTCEnableQueryActionHandler
 * @brief Handler for actions related to enabling meeting query.
 */
@interface MobileRTCEnableQueryActionHandler : NSObject
/**
 * @brief Get the title of the tip.
 * @return The title of the tip
 */
- (NSString *_Nullable)tipTitle;

/**
 * @brief Get the tip string.
 * @return The tip string.
 */
- (NSString *_Nullable)tipString;

/**
 * @brief Confirm enable query.
 * @return If the function succeeds, it returns MobileRTCSDKError_Success. Otherwise the function fails.
 */
- (MobileRTCSDKError)confirm;

/**
 * @brief Cancel enable query.
 * @return If the function succeeds, it returns MobileRTCSDKError_Success. Otherwise the function fails.
 */
- (MobileRTCSDKError)cancel;
@end


/**
 * @protocol MobileRTCAICompanionQueryHelperDelegate
 * @brief Delegate protocol for receiving AI Companion meeting query related events.
 */
@protocol MobileRTCAICompanionQueryHelperDelegate <NSObject>
@optional
/**
 * @brief Notification that meeting does not support meeting query.
 */
- (void)onQueryStateNotSupported;

/**
 * @brief Notification that the meeting supports query but query feature is disabled.
 * @param handler The handler to enable the query.
 */
- (void)onQueryStateEnabledButNotStarted:(MobileRTCStartQueryHandler *_Nullable)handler;

/**
 * @brief Notification that the meting supports query but query feature is disabled.
 * @param handler The handler to enable the query.
 */
- (void)onQueryStateSupportedButDisabled:(MobileRTCEnableQueryHandler *_Nullable)handler;

/**
 * @brief Notification that the query is started.
 * @param handler The handler to send the query.
 */
- (void)onQueryStateStarted:(MobileRTCSendQueryHandler *_Nullable)handler;

/**
 * @brief Notification that the query setting is changed.
 * @param setting The selected query setting.
 */
- (void)onQuerySettingChanged:(MobileRTCAICompanionQuerySettingOptions)setting;

/**
 * @brief Notification that the request send query failed.
 * @param bTimeout YES means that the request timeout. No means the user declines the request.
 */
- (void)onFailedToStartQuery:(BOOL)bTimeout;

/**
 * @brief Notification of receiving request to enable query.
 * @param handler The handler to handle the request.
 */
- (void)onReceiveRequestToEnableQuery:(MobileRTCApproveEnableQueryHandler *_Nullable)handler;

/**
 * @brief Notification of receiving request to start query.
 * @param handler The handler to handle the request.
 */
- (void)onReceiveRequestToStartQuery:(MobileRTCApproveStartQueryHandler *_Nullable)handler;

/**
 * @brief Notification of receiving query answer.
 * @param queryItem The obect of MobileRTCAICompanionQueryItem.
 */
- (void)onReceiveQueryAnswer:(MobileRTCAICompanionQueryItem *_Nullable)queryItem;

/**
 * @brief Notification of receiving query enable action callback.
 * @param handler The handler to enable the query.
 */
- (void)onQueryEnableActionCallback:(MobileRTCEnableQueryActionHandler *_Nullable)handler;

/**
 * @brief Notification of got or loss send query question privilege.
 * @param canSendQuery YES means can send. Otherwise not.
 */
- (void)onSendQueryPrivilegeChanged:(BOOL)canSendQuery;

/**
 * @brief Notification that failed to request send query.
 * @param bTimeout YES means is timeout. No measn the user declines the request.
 */
- (void)onFailedToRequestSendQuery:(BOOL)bTimeout;

/**
 * @brief Notification of receiving request to send query.
 * @param handler The handler to handle the request.
 */
- (void)onReceiveRequestToSendQuery:(MobileRTCApproveSendQueryHandler *_Nullable)handler;

@end

/**
 * @class MobileRTCAICompanionQueryHelper
 * @brief Helper class to manage AI Companion meeting query features and related legal notices.
 */
@interface MobileRTCAICompanionQueryHelper : NSObject

@property(nonatomic, weak) id<MobileRTCAICompanionQueryHelperDelegate> delegate;

/**
 * @brief Get the selected query setting.
 * @return If the function succeeds, it returns the selected query setting. Otherwise the function fails.
 */
- (MobileRTCAICompanionQuerySettingOptions)getSelectedQuerySetting;

/**
 * @brief Determine whether the current user can change the query setting.
 * @return YES means that it can change the setting. Otherwise it can't change the setting.
 */
- (BOOL)canChangeQuerySetting;

/**
 * @brief Change query setting.
 * @return If the function succeeds, it returns MobileRTCSDKError_Success. Otherwise nthe function fails.
 */
- (MobileRTCSDKError)changeQuerySettings:(MobileRTCAICompanionQuerySettingOptions)setting;

@end
