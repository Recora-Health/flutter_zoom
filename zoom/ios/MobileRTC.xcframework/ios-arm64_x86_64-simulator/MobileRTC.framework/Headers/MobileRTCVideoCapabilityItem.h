//
//  MobileRTCVideoCapabilityItem.h
//  MobileRTC
//
//  Created by Zoom Communications on 2020/3/9.
//  Copyright © Zoom Communications, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * @class MobileRTCVideoCapabilityItem
 */
@interface MobileRTCVideoCapabilityItem : NSObject

/**
 * @brief The video frame width.
 */
@property (nonatomic, assign) int width;
/**
 * @brief The video frame height.
 */
@property (nonatomic, assign) int height;
/**
 * @brief The video frame rate.
 */
@property (nonatomic, assign) int videoFrame;

@end
