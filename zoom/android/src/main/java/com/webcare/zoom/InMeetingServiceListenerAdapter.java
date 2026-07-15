package com.webcare.zoom;

import us.zoom.sdk.InMeetingServiceListener;

/**
 * No-op implementation of the ~90-method InMeetingServiceListener interface
 * (Zoom SDK 7.0.5 ships no adapter class). Subclass and override only the
 * callbacks you need. Generated from the SDK interface via javap.
 */
public class InMeetingServiceListenerAdapter implements InMeetingServiceListener {

    @Override
    public void onMeetingNeedPasswordOrDisplayName(boolean p0, boolean p1, us.zoom.sdk.InMeetingEventHandler p2) {}

    @Override
    public void onMeetingNeedConfirmPreview(us.zoom.sdk.InMeetingPreviewHandler p0) {}

    @Override
    public void onWebinarNeedRegister(java.lang.String p0) {}

    @Override
    public void onJoinMeetingNeedUserInfo(us.zoom.sdk.IMeetingInputUserInfoHandler p0) {}

    @Override
    public void onJoinWebinarNeedUserNameAndEmail(us.zoom.sdk.InMeetingEventHandler p0) {}

    @Override
    public void onWebinarNeedInputScreenName(us.zoom.sdk.InMeetingEventHandler p0) {}

    @Override
    public void onMeetingNeedCloseOtherMeeting(us.zoom.sdk.InMeetingEventHandler p0) {}

    @Override
    public void onMeetingFail(int p0, int p1) {}

    @Override
    public void onMeetingLeaveComplete(long p0) {}

    @Override
    public void onMeetingUserJoin(java.util.List<java.lang.Long> p0) {}

    @Override
    public void onMeetingUserLeave(java.util.List<java.lang.Long> p0) {}

    @Override
    public void onMeetingUserUpdated(long p0) {}

    @Override
    public void onInMeetingUserAvatarPathUpdated(long p0) {}

    @Override
    public void onMeetingHostChanged(long p0) {}

    @Override
    public void onMeetingCoHostChange(long p0, boolean p1) {}

    @Override
    public void onActiveVideoUserChanged(long p0) {}

    @Override
    public void onActiveSpeakerVideoUserChanged(long p0) {}

    @Override
    public void onHostVideoOrderUpdated(java.util.List<java.lang.Long> p0) {}

    @Override
    public void onFollowHostVideoOrderChanged(boolean p0) {}

    @Override
    public void onSpotlightVideoChanged(java.util.List<java.lang.Long> p0) {}

    @Override
    public void onUserVideoStatusChanged(long p0, us.zoom.sdk.InMeetingServiceListener.VideoStatus p1) {}

    @Override
    public void onSinkMeetingVideoQualityChanged(us.zoom.sdk.VideoQuality p0, long p1) {}

    @Override
    public void onMicrophoneStatusError(us.zoom.sdk.InMeetingAudioController.MobileRTCMicrophoneError p0) {}

    @Override
    public void onUserAudioStatusChanged(long p0, us.zoom.sdk.InMeetingServiceListener.AudioStatus p1) {}

    @Override
    public void onHostAskUnMute(long p0) {}

    @Override
    public void onHostAskStartVideo(long p0) {}

    @Override
    public void onUserAudioTypeChanged(long p0) {}

    @Override
    public void onMyAudioSourceTypeChanged(int p0) {}

    @Override
    public void onLowOrRaiseHandStatusChanged(long p0, boolean p1) {}

    @Override
    public void onChatMessageReceived(us.zoom.sdk.InMeetingChatMessage p0) {}

    @Override
    public void onChatMsgDeleteNotification(java.lang.String p0, us.zoom.sdk.ChatMessageDeleteType p1) {}

    @Override
    public void onChatMessageEditNotification(us.zoom.sdk.InMeetingChatMessage p0) {}

    @Override
    public void onShareMeetingChatStatusChanged(boolean p0) {}

    @Override
    public void onSilentModeChanged(boolean p0) {}

    @Override
    public void onFreeMeetingReminder(boolean p0, boolean p1, boolean p2) {}

    @Override
    public void onMeetingActiveVideo(long p0) {}

    @Override
    public void onSinkAttendeeChatPrivilegeChanged(int p0) {}

    @Override
    public void onSinkAllowAttendeeChatNotification(int p0) {}

    @Override
    public void onSinkPanelistChatPrivilegeChanged(us.zoom.sdk.InMeetingChatController.MobileRTCWebinarPanelistChatPrivilege p0) {}

    @Override
    public void onUserNamesChanged(java.util.List<java.lang.Long> p0) {}

    @Override
    public void onFreeMeetingNeedToUpgrade(us.zoom.sdk.FreeMeetingNeedUpgradeType p0, java.lang.String p1) {}

    @Override
    public void onFreeMeetingUpgradeToGiftFreeTrialStart() {}

    @Override
    public void onFreeMeetingUpgradeToGiftFreeTrialStop() {}

    @Override
    public void onFreeMeetingUpgradeToProMeeting() {}

    @Override
    public void onClosedCaptionReceived(java.lang.String p0, long p1) {}

    @Override
    public void onRecordingStatus(us.zoom.sdk.InMeetingServiceListener.RecordingStatus p0) {}

    @Override
    public void onLocalRecordingStatus(long p0, us.zoom.sdk.InMeetingServiceListener.RecordingStatus p1) {}

    @Override
    public void onInvalidReclaimHostkey() {}

    @Override
    public void onPermissionRequested(java.lang.String[] p0) {}

    @Override
    public void onAllHandsLowered() {}

    @Override
    public void onLocalVideoOrderUpdated(java.util.List<java.lang.Long> p0) {}

    @Override
    public void onLocalRecordingPrivilegeRequested(us.zoom.sdk.IRequestLocalRecordingPrivilegeHandler p0) {}

    @Override
    public void onSuspendParticipantsActivities() {}

    @Override
    public void onAllowParticipantsStartVideoNotification(boolean p0) {}

    @Override
    public void onAllowParticipantsRenameNotification(boolean p0) {}

    @Override
    public void onAllowParticipantsUnmuteSelfNotification(boolean p0) {}

    @Override
    public void onAllowParticipantsShareWhiteBoardNotification(boolean p0) {}

    @Override
    public void onMeetingLockStatus(boolean p0) {}

    @Override
    public void onRequestLocalRecordingPrivilegeChanged(us.zoom.sdk.LocalRecordingRequestPrivilegeStatus p0) {}

    @Override
    public void onAICompanionActiveChangeNotice(boolean p0) {}

    @Override
    public void onParticipantProfilePictureStatusChange(boolean p0) {}

    @Override
    public void onCloudRecordingStorageFull(long p0) {}

    @Override
    public void onUVCCameraStatusChange(java.lang.String p0, us.zoom.sdk.InMeetingServiceListener.UVCCameraStatus p1) {}

    @Override
    public void onFocusModeStateChanged(boolean p0) {}

    @Override
    public void onFocusModeShareTypeChanged(us.zoom.sdk.MobileRTCFocusModeShareType p0) {}

    @Override
    public void onVideoAlphaChannelStatusChanged(boolean p0) {}

    @Override
    public void onAllowParticipantsRequestCloudRecording(boolean p0) {}

    @Override
    public void onSinkJoin3rdPartyTelephonyAudio(java.lang.String p0) {}

    @Override
    public void onUserConfirmToStartArchive(us.zoom.sdk.IMeetingArchiveConfirmHandler p0) {}

    @Override
    public void onCameraControlRequestReceived(long p0, us.zoom.sdk.CameraControlRequestType p1, us.zoom.sdk.ICameraControlRequestHandler p2) {}

    @Override
    public void onCameraControlRequestResult(long p0, boolean p1) {}

    @Override
    public void onCameraControlRequestResult(long p0, us.zoom.sdk.CameraControlRequestResult p1) {}

    @Override
    public void onFileSendStart(us.zoom.sdk.ZoomSDKFileSender p0) {}

    @Override
    public void onFileReceived(us.zoom.sdk.ZoomSDKFileReceiver p0) {}

    @Override
    public void onFileTransferProgress(us.zoom.sdk.ZoomSDKFileTransferInfo p0) {}

    @Override
    public void onMuteOnEntryStatusChange(boolean p0) {}

    @Override
    public void onMeetingTopicChanged(java.lang.String p0) {}

    @Override
    public void onMeetingFullToWatchLiveStream(java.lang.String p0) {}

    @Override
    public void onBotAuthorizerRelationChanged(long p0) {}

    @Override
    public void onVirtualNameTagStatusChanged(boolean p0, long p1) {}

    @Override
    public void onVirtualNameTagRosterInfoUpdated(long p0) {}

    @Override
    public void onCreateCompanionRelation(long p0, long p1) {}

    @Override
    public void onRemoveCompanionRelation(long p0) {}

    @Override
    public void onUserConfirmRecoverMeeting(us.zoom.sdk.IRecoverMeetingHandle p0) {}

    @Override
    public void onGrantCoOwnerPrivilegeChanged(boolean p0) {}

    @Override
    public void onUserNetworkStatusChanged(us.zoom.sdk.EnumComponentType p0, us.zoom.sdk.MobileRTCNetworkQuality p1, long p2, boolean p3) {}

    @Override
    public void onAppSignalPanelUpdated(us.zoom.sdk.InMeetingAppSignalPanelHandler p0) {}

}
