/**
 * @file MobileRTCMeetingSettings.h
 * @brief Configuration settings for meeting behavior and preferences.
 */

#import <Foundation/Foundation.h>

/**
 * @class MobileRTCMeetingSettings
 * @brief Set to modify the configurations of the meeting.
 */
@interface MobileRTCMeetingSettings : NSObject
/**
 * @brief Show/Hide meeting title in the meeting bar.
 * @warning The function only in Zoom UI mode.
 */
@property (assign, nonatomic) BOOL meetingTitleHidden;

/**
 * @brief Show/Hide meeting password in the meeting bar.
 * @warning The function only in Zoom UI mode.
 */
@property (assign, nonatomic) BOOL meetingPasswordHidden;

/**
 * @brief Show/Hide the END/LEAVE MEETING button in the meeting bar.
 * @warning The function only in Zoom UI mode.
 */
@property (assign, nonatomic) BOOL meetingLeaveHidden;

/**
 * @brief Show/Hide AUDIO button in the meeting bar.
 * @warning The function only in Zoom UI mode.
 */
@property (assign, nonatomic) BOOL meetingAudioHidden;

/**
 * @brief Show/Hide VIDEO button in the meeting bar.
 * @warning The function only in Zoom UI mode.
 */
@property (assign, nonatomic) BOOL meetingVideoHidden;

/**
 * @brief Show/Hide INVITE button in the meeting bar.
 * @warning The function only in Zoom UI mode.
 */
@property (assign, nonatomic) BOOL meetingInviteHidden;

/**
 * @brief Show/Hide INVITE link in the meeting info view.
 * @warning The function only in Zoom UI mode.
 */
@property (assign, nonatomic) BOOL meetingInviteUrlHidden;

/**
 * @brief Show/Hide Chat in the meeting bar.
 * @warning The function only in Zoom UI mode.
 */
@property (assign, nonatomic) BOOL meetingChatHidden;

/**
 * @brief Show/Hide PARTICIPANT button in the meeting bar.
 * @warning The function only in Zoom UI mode.
 */
@property (assign, nonatomic) BOOL meetingParticipantHidden;

/**
 * @brief Show/Hide SHARE button in the meeting bar.
 * @warning The function only in Zoom UI mode.
 */
@property (assign, nonatomic) BOOL meetingShareHidden;

/**
 * @brief Show/Hide MORE button in the meeting bar.
 * @warning The function only in Zoom UI mode.
 */
@property (assign, nonatomic) BOOL meetingMoreHidden;

/**
 * @brief Show/Hide the BAR ON THE TOP of view in the meeting.
 * @warning The function only in Zoom UI mode.
 */
@property (assign, nonatomic) BOOL topBarHidden;

/**
 * @brief Show/Hide BAR at the bottom of the view in the meeting.
 * @warning The BAR at the bottom of the view is available on iPhone.
 * @warning The function only in Zoom UI mode.
 */
@property (assign, nonatomic) BOOL bottomBarHidden;

/**
 * @brief Show/Hide disconnect audio button.
 * @warning The function only in Zoom UI mode.
 */
@property (assign, nonatomic) BOOL disconnectAudioHidden;

/**
 * @brief Show/Hide record button.
 * @warning The function only in Zoom UI mode.
 */
@property (assign, nonatomic) BOOL recordButtonHidden;

/**
 * @brief Change thumbnail video layout while viewing a share in the meeting.
 * @warning If you set it to YES, the video of attendees will be placed at right of the Landscape(the device screen is oriented horizontally) or the bottom of Portrait(the device screen is oriented vertically) apart from the shared content, which means the video won't cover the content; if you set to NO, it will show only the video of active speaker and the video will be placed in the bottom right of the screen.
 * @warning The function only in Zoom UI mode.
 */
@property (assign, nonatomic) BOOL thumbnailInShare;

/**
 * @brief Show/Hide LEAVE MEETING item for the host in the pop up view after click the end/leave meeting button in the meeting bar.
 * @warning The function only in Zoom UI mode.
 */
@property (assign, nonatomic) BOOL hostLeaveHidden;

/**
 * @brief Show/Hide the hint message in the meeting, hint message is on the top bar.
 * @warning The function only in Zoom UI mode.
 */
@property (assign, nonatomic) BOOL hintHidden;

/**
 * @brief Show/Hide the tips message in the meeting, tips message is on the bottom of the screen.
 * @warning The function only in Zoom UI mode.
 */
@property (assign, nonatomic) BOOL tipsHidden;

/**
 * @brief Show/Hide the waiting HUD while starting/joining a meeting.
 * @warning The function only in Zoom UI mode.
 */
@property (assign, nonatomic) BOOL waitingHUDHidden;

/**
 * @brief Show/Hide "Call in Room System" item in Invite h.323/SIP Room System.
 * @warning The function only in Zoom UI mode.
 */
@property (assign, nonatomic) BOOL callinRoomSystemHidden;

/**
 * @brief Show/Hide "Call out Room System" item in Invite h.323/SIP Room System.
 * @warning The function only in Zoom UI mode.
 */
@property (assign, nonatomic) BOOL calloutRoomSystemHidden;

/**
 * @brief Show/Hide "Enter Host Key to Claim Host" item in Menu More.
 * @warning The function only in Zoom UI mode.
 */
@property (assign, nonatomic) BOOL claimHostWithHostKeyHidden;

/**
 * @brief Show/Hide CLOSE CAPTION in a meeting.
 * @warning The function only in Zoom UI mode.
 */
@property (assign, nonatomic) BOOL closeCaptionHidden;

/**
 * @brief Show/Hide Q&A button in webinar meeting.
 * @warning The function only in Zoom UI mode.
 */
@property (assign, nonatomic) BOOL qaButtonHidden;

/**
 * @brief Show/Hide "Promote to Panelist" in webinar meeting.
 * @warning Only host/co-host can see the option in webinar meeting‘s participants.
 * @warning The function only in Zoom UI mode.
 */
@property (assign, nonatomic) BOOL promoteToPanelistHidden;

/**
 * @brief Show/Hide "Change to Attendee" in webinar meeting.
 * @warning Only host/co-host can see the option in webinar meeting‘s participants.
 * @warning The function only in Zoom UI mode.
 */
@property (assign, nonatomic) BOOL changeToAttendeeHidden;

/**
 * @brief Enable/Disable Proximity Sensors Monitoring in a meeting. 
 * @warning The function only in Zoom UI mode.
 */
@property (assign, nonatomic) BOOL proximityMonitoringDisable;

/**
 * @brief Enable or disable hiding the recover meeting dialog in Zoom UI mode.
 * @warning The function only in Zoom UI mode.
 */
@property (assign, nonatomic) BOOL hideRecoverMeetingDialog;

/**
 * @brief Hide feedback button on cloud whiteboard.
 * @deprecated Use hideFeedbackButtonOnCloudWhiteboard: in MeetingService instead.
 */
@property (assign, nonatomic) BOOL hideFeedbackButtonOnCloudWhiteboard DEPRECATED_MSG_ATTRIBUTE("Use hideFeedbackButtonOnCloudWhiteboard: in MeetingService instead");

/**
 * @brief Hide share button on cloud whiteboard.
 * @deprecated Use hideShareButtonOnCloudWhiteboard: in MeetingService instead.
 */
@property (assign, nonatomic) BOOL hideShareButtonOnCloudWhiteboard DEPRECATED_MSG_ATTRIBUTE("Use hideShareButtonOnCloudWhiteboard: in MeetingService instead");

/**
 * @brief About button’s visibility on the cloud whiteboard. Default is displaying.
 * @deprecated Use hideAboutButtonOnCloudWhiteboard: in MeetingService instead.
 */
@property (assign, nonatomic) BOOL hideAboutButtonOnCloudWhiteboard DEPRECATED_MSG_ATTRIBUTE("Use hideAboutButtonOnCloudWhiteboard: in MeetingService instead");

/**
 * @brief Query if the user joins meeting with audio device. 
 * @return YES means the audio device is automatically connected, otherwise not. 
 */
- (BOOL)autoConnectInternetAudio;

/**
 * @brief Set to auto-connect the audio when user joins meeting. 
 * @param connected The option value.
 */
- (void)setAutoConnectInternetAudio:(BOOL)connected;

/**
 * @brief Query if user's audio is muted when he joins the meeting. 
 * @return YES means muted, otherwise not.
 */
- (BOOL)muteAudioWhenJoinMeeting;

/**
 * @brief Set to mute user's audio when he joins the meeting. 
 * @param muted YES means to mute the audio, otherwise not.
 */
- (void)setMuteAudioWhenJoinMeeting:(BOOL)muted;

/**
 * @brief Query if user's video is muted when he joins the meeting. 
 * @return YES means muted, otherwise not.
 */
- (BOOL)muteVideoWhenJoinMeeting;

/**
 * @brief Set to mute user's video when he joins the meeting. 
 * @param muted YES means to mute the video, otherwise not.
 */
- (void)setMuteVideoWhenJoinMeeting:(BOOL)muted;

/**
 * @brief Query Touch up my appearance enable or not.
 * @return Muted YES means enable, otherwise not.
 */
- (BOOL)faceBeautyEnabled;

/**
 * @brief Set Touch up my appearance enable or not.
 * @param enable YES means successful, otherwise not.
 */
- (void)setFaceBeautyEnabled:(BOOL)enable;

/**
 * @brief Determine if mirror effect is enabled.
 * @return YES means enabled, otherwise not.
 */
- (BOOL)isMirrorEffectEnabled;

/**
 * @brief Set to enable/disable mirror effect.
 * @param enable YES means enabled, No disabled.
 */
- (void)enableMirrorEffect:(BOOL)enable;

/**
 * @brief Query if driving mode is disabled.
 * @return YES means muted, otherwise not.
 * @warning The function only in Zoom UI mode.
 */
- (BOOL)driveModeDisabled;

/**
 * @brief Set to disable the Driving mode in the meeting.
 * @param disabled YES means disabled, otherwise not.
 * @warning The function only in Zoom UI mode.
 */
- (void)disableDriveMode:(BOOL)disabled;

/**
 * @brief Query if Gallery View is disabled.
 * @return YES means muted, otherwise not.
 * @warning The function only in Zoom UI mode.
 */
- (BOOL)galleryViewDisabled;

/**
 * @brief Set to disable the Gallery View in the meeting.
 * @param disabled YES means disabled, otherwise not.
 * @warning The function only in Zoom UI mode.
 */
- (void)disableGalleryView:(BOOL)disabled;

/**
 * @brief Enable or disable the new Zoom Whiteboard feature (different from Classic Whiteboard). This feature enabled by default.
 * @param disabled YES means disabled, otherwise not.
 * @warning The function only in Zoom UI mode.
 * @deprecated Use disableCloudWhiteboard: in MeetingService instead.
 */
- (void)disableCloudWhiteboard:(BOOL)disabled DEPRECATED_MSG_ATTRIBUTE("Use disableCloudWhiteboard: in MeetingService instead");

/**
 * @brief Query if it is disabled to call in.
 * @return YES means disabled, otherwise not.
 * @warning The function only in Zoom UI mode.
 */
- (BOOL)callInDisabled;

/**
 * @brief Set to disable the incoming calls.
 * @param disabled The option value.
 * @warning The function only in Zoom UI mode.
 */
- (void)disableCallIn:(BOOL)disabled;

/**
 * @brief Query if it is disabled to call out.
 * @return YES means disabled, otherwise not.
 * @warning The function only in Zoom UI mode.
 */
- (BOOL)callOutDisabled;

/**
 * @brief Set to disable the outgoing calls. 
 * @param disabled The option value.
 * @warning The function only in Zoom UI mode.
 */
- (void)disableCallOut:(BOOL)disabled;

/**
 * @brief Query if it is disabled to Minimize Meeting.
 * @return YES means disabled, otherwise not.
 * @warning The function only in Zoom UI mode.
 */
- (BOOL)minimizeMeetingDisabled;

/**
 * @brief Set to disable the Minimize Meeting.
 * @param disabled The option value.
 * @warning The function only in Zoom UI mode.
 */
- (void)disableMinimizeMeeting:(BOOL)disabled;

/**
 * @brief Query if it is disabled free meeting upgrade tips.
 * @return YES means disabled, otherwise not.
 */
- (BOOL)freeMeetingUpgradeTipsDisabled;

/**
 * @brief Set to disable free meeting upgrade tips.
 * @param disabled The option value.
 */
- (void)disableFreeMeetingUpgradeTips:(BOOL)disabled;

/**
 * @brief Query Meeting setting of speaker off when present meeting.
 * @return YES means speaker off, otherwise not.
 * @warning The function only in Zoom UI mode.
 */
- (BOOL)speakerOffWhenInMeeting;

/**
 * @brief Set speaker off.  Default value is No, Need set to NO when not used.
 * @param speakerOff means speaker off, otherwise not.
 * @warning The function only in Zoom UI mode.
 */
- (void)setSpeakerOffWhenInMeeting:(BOOL)speakerOff;

/**
 * @brief Query show meeting elapse time.
 * @return YES means show meeting elapse time, otherwise not.
 * @warning The function only in Zoom UI mode.
 */
- (BOOL)showMyMeetingElapseTime;

/**
 * @brief Enable show meeting elapse time.
 * @param enable YES means show meeting elapse time, otherwise not.
 * @warning The function only in Zoom UI mode.
 */
- (void)enableShowMyMeetingElapseTime:(BOOL)enable;

/**
 * @brief Query mic original input enable or not.
 * @return YES means mic original input enable, otherwise not.
 */
- (BOOL)micOriginalInputEnabled;

/**
 * @brief Enable mic original input.
 * @param enable YES means enable mic original input, otherwise not.
 */
- (void)enableMicOriginalInput:(BOOL)enable;

/**
 * @brief Query reactions on MeetingUI is hidden or not.
 * @return YES means reactions on MeetingUI is hidden, otherwise not.
 * @warning YES means reactions on MeetingUI is hidden, otherwise not.
 */
- (BOOL)reactionsOnMeetingUIHidden;

/**
 * @brief Set the visibility of reaction on meeting UI. Default is displaying.
 * @param hidden YES means hide reaction emotion.
 * @warning The function only in Zoom UI mode.
 */
- (void)hideReactionsOnMeetingUI:(BOOL)hidden;

/**
 * @brief Query if it is disabled to show video preview when join meeting.
 * @return YES means disabled, otherwise not.
 * @warning The function only in Zoom UI mode.
 */
- (BOOL)showVideoPreviewWhenJoinMeetingDisabled;

/**
 * @brief Set to disable show video preview when join meeting.
 * @param disabled The option value.
 * @warning The function only in Zoom UI mode.
 */
- (void)disableShowVideoPreviewWhenJoinMeeting:(BOOL)disabled;

/**
 * @brief Query if it is disabled for virtual background.
 * @return YES means disabled, otherwise not.
 */
- (BOOL)virtualBackgroundDisabled;

/**
 * @brief Set to disable virtual background.
 * @param disabled The option value.
 */
- (void)disableVirtualBackground:(BOOL)disabled;

/**
 * @brief Pre populate webinar registration info.
 * @param email registration email address.
 * @param username registration username.
 */
- (void)prePopulateWebinarRegistrationInfo:(nonnull NSString *)email username:(nonnull NSString *)username;

/**
 * @brief Set the webinar register information dialog to hide or display.
 * @param hide Yes means hide the dialog. Otherwise, do not hide the dialog.
 */
- (void)setHideRegisterWebinarInfoWindow:(BOOL)hide;

/**
 * @brief Get the webinar register information dialog to hide or display.
 * @return Boolean value of the setting value.
 */
- (BOOL)hideRegisterWebinarInfoWindow;

/**
 * @brief Set the webinar username input dialog to hide or display. if hide webinar user name input dialog, should handle.\link MobileRTCMeetingServiceDelegate::onWebinarNeedInputScreenName: \endlink. \link MobileRTCWebinarInputScreenNameHandler:: inputName: \endlink.
 * @param hide true  means hide the dialog. Otherwise, do not hide the dialog.
 */
- (void)setHideWebinarNameInputWindow:(BOOL)hide;

/**
 * @brief Get the webinar username input dialog to hide or display.
 * @return Value of the setting value.
 */
- (BOOL)isHideWebinarNameInputWindow;

/**
 * @brief Set to disable confidential watermark.
 * @param disable The option value.
 * @return YES means confidential watermark is disable, otherwise not.
 * @warning The function only in Zoom UI mode.
 */
- (BOOL)disableConfidentialWatermark:(BOOL)disable;

/**
 * @brief Query if it is disabled for copy meeting url.
 * @return YES means disabled, otherwise not.
 * @warning The function only in Zoom UI mode.
 */
- (BOOL)copyMeetingUrlDisabled;

/**
 * @brief Set to disable copy meeting url in the meeting info view.
 * @param disabled The option value.
 * @warning The function only in Zoom UI mode.
 */
- (void)disableCopyMeetingUrl:(BOOL)disabled;

/**
 * @brief Set emoji reaction skin tone.
 * @param skinTone The reaction skin tone.
 * @return If the function succeeds, it will return MobileRTCMeetError_Success. Otherwise the function fails.
 * @warning The function only in Zoom UI mode.
 */
- (MobileRTCMeetError)setReactionSkinTone:(MobileRTCEmojiReactionSkinTone)skinTone;

/**
 * @brief Get reaction skin tone.
 * @return SkinTone for emoji reaction.
 * @warning The function only in Zoom UI mode.
 */
- (MobileRTCEmojiReactionSkinTone)reactionSkinTone;

/**
 * @brief Disable the action of clear WebView's cache.
 * @param disabled Specify to disable the clear action or not.
 */
- (void)disableClearWebKitCache:(BOOL)disabled;

/**
 * @brief Query if the action of clear WebView's cache be disabled.
 * @return Action of clear WebView's cache is disabled or not.
 */
- (BOOL)isDisabledClearWebKitCache;

/**
 * @brief Query if the option HIDE NON-VIDEO PARTICIPANTS is enabled.
 * @return YES means enabled. NO not.
 */
- (BOOL)isHideNoVideoUsersEnabled;

/**
 * @brief Set whether to enable the option HIDE NON-VIDEO PARTICIPANTS.
 * @param enabled YES means enabled. NO not.
 */
- (void)setHideNoVideoUsersEnabled:(BOOL)enabled;

/**
 * @brief Enable or disable to hide the userself's view. isHidden TRUE indicates to enable to hide the userself's view.
 */
- (void)enableHideSelfView:(BOOL)isHidden;

/**
 * @brief Get the flag to enable/disable to hide userself's view.
 * @return YES means hide self view, otherwise not.
 */
- (BOOL)isHideSelfViewEnabled;

/**
 * @brief Set the visibility of request local recording privilege dialog when attendee request local recording privilege. Default is displaying.
 * @param bHide YES indicates to display the tab. No not.
 */
- (void)hideRequestRecordPrivilegeDialog:(BOOL)bHide;

/**
 * @brief Get the flag of auto enter Picture-in-Picture Mode for video calls.
 * @return YES means auto enter Picture-in-Picture Mode, otherwise not.
 */
- (BOOL)videoCallPictureInPictureEnabled;

/**
 * @brief Set whether to close the current sharing of another user without prompt and directly beginning a new sharing content by the closer. Default value: FALSE(prompt).
 * @param enable YES indicates no prompt. FALSE not.
 */
- (void)enableGrabShareWithoutReminder:(BOOL)enable;

/**
 * @brief Set the meeting input user info dialog to hide or display.
 * @param hide YES means hide the dialog. Otherwise, do not hide the dialog.
 */
- (void)setHideMeetingInputUserInfoWindow:(BOOL)hide;

/**
 * @brief Get the meeting input user info dialog to hide or display.
 * @return The value of the setting value.
 */
- (BOOL)isHideMeetingInputUserInfoWindow;

/**
 * @brief Query if this device supports CenterStage Mode.
 * @return YES means supported, otherwise not.
 * @warning Only iPad of os version above 14.5 can using this feature.
 */
- (BOOL)isCenterStageModeSupported;

/**
 * @brief Enable or disable CenterStage Mode. This is disable by default.
 * @param enable YES means enabled, otherwise not.
 * @return YES means supported, otherwise not.
 */
- (BOOL)enableCenterStageMode:(BOOL)enable;

/**
 * @brief Query if CenterStage Mode is enable by MobileRTC.
 * @return YES indicates enable. Otherwise not.
 */
- (BOOL)isEnabledCenterStageMode;
/**
 * @brief Enable echo cancellation.
 * @param enable true means enabled, false disabled.
 * @return If the function succeeds, the return value is MobileRTCSDKError_Success.
 */
- (MobileRTCSDKError)enableEchoCancellation:(BOOL)enable;

/**
 * @brief Determine if echo cancellation is enabled or not.
 * @return YES means supported, otherwise not.
 */
- (BOOL)isEchoCancellationOn;

/**
 * @brief Determine if the meeting supports echo cancellation.
 * @return YES means supported, otherwise not. Only using this feature when enabled original sound called: "enableMicOriginalInput:".
 */
- (BOOL)isSupportEchoCancellation;


/**
 * @brief Set the confirm start archive dialog to hide or display.
 * @param hide true  means hide the dialog. Otherwise, do not hide the dialog.
 * @warning If hide confirm start archive dialog when join meeting, should handle the 'MobileRTCArchiveConfrimHandle'.
 */
- (void)setHideConfirmStartArchiveDialog:(BOOL)hide;

/**
 * @brief Get the confirm start archive dialog whether hide or display.
 * @return YES means hide, false means display.
 */
- (BOOL)isHideConfirmStartArchiveDialog;

/**
 * @brief Whether to cancel the bandwidth limit, If YES is set, the network bandwidth is no longer limited, and better audio and video quality can be obtained. Bandwidth is not limited by default. If it is a wifi network, the bandwidth is not limited, and this setting is invalid.
 * @param enable a boolean flag to set up the behavoir.
 */
- (void)enable5GHighBandWidth:(BOOL)enable;

/**
 * @brief Enable or disable zoom docs features in custom ui. this can only take effect when \link MobileRTCSDKInitContext::enableCustomizeMeetingUI \endlink is true.This is disabled by default. When you enable this feature,you need to handle the \link MobileRTCMeetingServiceDelegate::onDocsStatusChanged: \endlink, and subscribe the docs share with the \link MobileRTCMeetingService::showDocByParentViewCtroller: \endlink.
 * @param enable true means enable, otherwise disable.
 */
- (void)enableZoomDocs:(BOOL)enable;

@end
