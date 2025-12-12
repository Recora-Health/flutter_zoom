/**
 * @file MobileRTCMeetingService+VirtualBackground.h
 * @brief Meeting+VirtualBackground service functionality and management.
 */

#import <MobileRTC/MobileRTC.h>

/**
 * @class MobileRTCVirtualBGImageInfo
 * @brief Image item property.
 */
@interface MobileRTCVirtualBGImageInfo : NSObject
/**
 * @brief virtual background image type.
 */
@property(nonatomic, assign) MobileRTCVBType vbType;

/**
 * @brief Current using image item if yes.
 */
@property(nonatomic, assign) BOOL isSelect;

/**
 * @brief Image path of image item, nil for none image item.
 */
@property(nonatomic, retain) NSString* _Nullable imagePath;

/**
 * @brief Current using image item allow to be deleted  if yes.
 */
@property(nonatomic, assign) BOOL isAllowDelete;

@end

/**
 * @brief Meeting service for virtual background.
 */
@interface MobileRTCMeetingService (VirtualBackground)
/**
 * @brief The preview for inspect the virtual background effect.
 */
@property (retain, nonatomic) UIView * _Nullable previewView;

/**
 * @brief Start preview for inspect the virtual background effect.
 * @return YES mean preview is ready.
 */
- (BOOL)startPreviewWithFrame:(CGRect)frame;

/**
 * @brief Stop previewing the virtual background.
 */
- (void)stopPreview;

/**
 * @brief Determine if the virtual background feature is supported by the meeting.
 * @return YES indicates that the meeting supports the virtual background feature.
 */
- (BOOL)isSupportVirtualBG;

/**
 * @brief Determine if the smart virtual background feature can be supported by the machine.
 * @return YES indicates that the machine can supports to use smart virtual background feature.
 * @warning Device should be iPhone 8/ 8 plus X or above or be iPad Pro 9.7 above, OS should be iOS 11 or above.
 */
- (BOOL)isDeviceSupportSmartVirtualBG;

/**
 * @brief Is Support smart virtual background.
 * @return YES mean support, you can use it.
 * @deprecated Use IsDeviceSupportSmartVirtualBG: instead.
 */
- (BOOL)isSupportSmartVirtualBG DEPRECATED_MSG_ATTRIBUTE("Use IsDeviceSupportSmartVirtualBG: instead");


#pragma mark smart virtual background
/**
 * @brief Get the virtual background list.
 * @return Return Narray of the items which include the None item.
 */
- (NSArray <MobileRTCVirtualBGImageInfo *>* _Nullable)getBGImageList;

/**
 * @brief Determine if the adding new virtual background item feature is supported by the meeting.
 * @return YES indicates that the meeting supports adding new virtual background item feature.
 */
- (BOOL)isAllowToAddNewVBItem;

/**
 * @brief Add and use the image for virtual background.
 * @return Add and use virtual background result.
 */
- (MobileRTCMeetError)addBGImage:(UIImage *_Nullable)image;

/**
 * @brief Remove image item form image list. Will use the previous one for virtual background.
 * @return Remove result.
 */
- (MobileRTCMeetError)removeBGImage:(MobileRTCVirtualBGImageInfo *_Nullable)bgImageInfo;

/**
 * @brief Use the specify image item for virtual background.
 * @return The result of use image item.
 */
- (MobileRTCMeetError)useBGImage:(MobileRTCVirtualBGImageInfo *_Nullable)bgImage;

/**
 * @brief Disable the virtrual background, same as use a none image item.
 * @return The result of disable virtual background.
 * @deprecated Use useBGImage: instead.
 */
- (MobileRTCMeetError)useNoneImage DEPRECATED_MSG_ATTRIBUTE("Use useBGImage: instead");

#pragma mark green virtual background
/**
 * @brief Is using green virtual background.
 * @return Return yes if using green virtual background.
 */
- (BOOL)isUsingGreenVB;

/**
 * @brief Enable green virtual background mode.
 * @param enable or disable.
 * @return Result of enable green virtual background.
 * @warning Only iPad support Virtual background GreenScreen, iPhone does not support the feature.
 * @warning Need call "startPreviewWithFrame:" to get the preview View, and shown in your UI hierarchy. Then select the point in preview view. We will using the color of your selected(point of the preview) to calculate the background.
 */
- (MobileRTCMeetError)enableGreenVB:(BOOL)enable;

/**
 * @brief Select the point that regard as background.
 * @param point point in preview view.
 * @return Result of set background point action.
 * @warning Only iPad support Virtual background GreenScreen, iPhone does not support the feature.
 */
- (MobileRTCMeetError)selectGreenVBPoint:(CGPoint)point;

@end

