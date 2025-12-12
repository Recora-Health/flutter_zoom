/**
 * @file MobileRTCMeetingService+Docs.h
 * @brief Meeting+Docs service functionality and management.
 */

#import <MobileRTC/MobileRTC.h>

/**
 * @class MobileRTCDocSharingSourceInfo
 * @brief Share source info of Zoom docs.
 */
@interface MobileRTCDocSharingSourceInfo: NSObject
/**
 * @brief Get the User ID of the Doc Sharing Source info.
 * @return If the function succeeds, the return value is the User ID. Otherwise the function fails, and the return value is ZERO (0).
 */
- (NSUInteger)getUserID;

/**
 * @brief Get the ID of the Doc Sharing Source Source Info.
 * @return If the function succeeds, the return value is the sharing Source ID. Otherwise the function fails, and the return value is ZERO (0).
 */
- (NSUInteger)getShareSourceID;

/**
 * @brief Get the Status of the Doc Sharing Source Info.
 * @return Return value is the sharing Source Info Status.
 */
- (MobileRTCDocsStatus)getStatus;

/**
 * @brief Get the Title of the Doc Sharing Source Info.
 * @return If the function succeeds, the return value is the totle of Sharing Source Info. Otherwise the function fails, and the return value is nil.
 */
- (NSString *_Nullable)getDocTitle;

@end


/**
 * @brief Meeting service for docs.
 */
@interface MobileRTCMeetingService (Docs)

/**
 * @brief Determine whether the current meeting supports the Docs or not.
 * @return YES means the current meeting supports the Docs, false means the Docs is not supported.
 */
- (BOOL)isSupportDocs;

/**
 * @brief Determine whether the current user can start share Doc or not.
 * @return The reason that no one can start share the Doc.
 */
- (MobileRTCCannotShareReasonType)canStartShareDoc;

/**
 * @brief Show Doc  or  DocDashboardView need to set  parent view controller. If Doc is activing( @c MobileRTCDocsStatus_Start),that can show activing Doc.
 * @param parentVC which use to present ViewController.
 * @warning The function only for Custom UI. This method is a prerequisite for using doc. Suggest to call this function in "onDocsStatusChanged:" for doc status.
 * @return If the function succeeds, the return value is MobileRTCSDKError_Success.
 */
- (MobileRTCSDKError)showDocByParentViewCtroller:(UIViewController* _Nonnull)parentVC;

/**
 * @brief Show Doc  or  DocDashboardView need to set  parent view controller. If Doc is activing( @c MobileRTCDocsStatus_Start),that can show activing Doc.
 * @param parentVC which use to present ViewController.
 * @param shareSourceID which the selected doc share source ID;
 * @warning The function only for Custom UI. This method is a prerequisite for using doc. Suggest to call this function in "onDocsStatusChanged:" for doc status.
 * @return If the function succeeds, the return value is MobileRTCSDKError_Success.
 */
- (MobileRTCSDKError)showActiveDoc:(NSUInteger)shareSourceID byParentViewCtroller:(UIViewController* _Nonnull)parentVC;

/**
 * @brief Show the dashboard web view window.
 * @return If the function succeeds, the return value is MobileRTCSDKError_Success.
 * @warning The function only for Custom UI.
 */
- (MobileRTCSDKError)showDocDashboardView;

/**
 * @brief Dismiss Doc  Dashboard.
 * @warning The function only for Custom UI.
 */
- (void)dismissDocOrDashboardView;

/**
 * @brief Determine whether the current user can set Docs option or not.
 * @return YES means the current user can set Docs option, false means the user can not set Docs option.
 */
- (BOOL)canSetDocsOption;

/**
 * @brief Set the setting option for Docs who can share.
 * @param option the setting for  who can share.
 * @return If the function succeeds, the return value is SDKErr_Success.
 */
-(MobileRTCSDKError)setDocsShareOption:(MobileRTCDocsShareOption)option;

/**
 * @brief Get the setting option for Docs who can share.
 * @return Option.
 */
-(MobileRTCDocsShareOption)getDocsShareOption;

/**
 * @brief Set the setting option for Docs who can initiate new Docs.
 * @param option Setting option for  who can initiate new Docs.
 * @return If the function succeeds, the return value is SDKErr_Success.
 */
-(MobileRTCSDKError)setDocsCreateOption:(MobileRTCDocsCreateOption)option;

/**
 * @brief Get the setting option for  who can initiate new Docs.
 * @return Option.
 */
-(MobileRTCDocsCreateOption)getDocsCreateOption;

/**
 * @brief Query if other user is sharing docs.
 * @return YES  means sharing successfully, No not.
 */
-(BOOL)isOtherSharingDocs;

/**
 * @brief Query if the current user is sharing docs successfully.
 * @return YES  means sharing successfully, No not.
 */
-(BOOL)isSharingDocsOut;

/**
 * @brief Get the list of sharing source info.
 * @param userID The ID of the user who is sharing.
 * @return If the function succeeds, the return value is a pointer to the NSArray<MobileRTCDocSharingSourceInfo*>. Otherwise, the return value is nil.
 */
- (NSArray<MobileRTCDocSharingSourceInfo *>* _Nullable)getDocSharingSourceInfoList:(NSUInteger)userID;


@end


