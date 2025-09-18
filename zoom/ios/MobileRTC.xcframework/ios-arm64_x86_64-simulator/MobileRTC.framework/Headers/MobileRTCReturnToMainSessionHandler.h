//
//  MobileRTCReturnToMainSessionHandler.h
//  MobileRTC
//
//  Created by Zoom Communications on 2021/5/31.
//  Copyright © Zoom Communications, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * @class MobileRTCReturnToMainSessionHandler
 * @brief Handler for returning to main session from breakout meeting.
 */
@interface MobileRTCReturnToMainSessionHandler : NSObject

/**
 * @brief Go back to main session for the main session invitation.
 * @return Whether return succeed or not.
 */
- (BOOL)returnToMainSession;

/**
 * @brief Ingore the main session invitation.
 */
- (void)ignore;

@end

NS_ASSUME_NONNULL_END
