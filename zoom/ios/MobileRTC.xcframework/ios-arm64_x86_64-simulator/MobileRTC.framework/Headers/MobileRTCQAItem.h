/**
 * @file MobileRTCQAItem.h
 * @brief Q&A item data structure for meeting Q&A functionality.
 */

#import <Foundation/Foundation.h>

/**
 * @class MobileRTCQAAnswerItem
 * @brief The Q&A answer interface.
 */
@interface MobileRTCQAAnswerItem : NSObject
- (NSDate *_Nullable)getTime;
- (NSString *_Nullable)getText;
- (NSString *_Nullable)getSenderName;
- (NSString *_Nullable)getQuestionId;
- (NSString *_Nullable)getAnswerID;

- (BOOL)isPrivate;
- (BOOL)isLiveAnswer;
- (BOOL)isSenderMyself;

@end

/**
 * @class MobileRTCQAItem
 * @brief The Q&A question interface.
 */
@interface MobileRTCQAItem : NSObject
- (NSString *_Nullable)getQuestionId;
- (NSDate *_Nullable)getTime;


- (NSString *_Nullable)getText;
- (NSString *_Nullable)getSenderName;


- (BOOL)isAnonymous;
- (BOOL)isMarkedAsAnswered;
- (BOOL)isMarkedAsDismissed;


- (NSUInteger)getUpvoteNumber;

- (BOOL)getHasLiveAnswers;
- (BOOL)getHasTextAnswers;


- (BOOL)isMySelfUpvoted;
- (BOOL)amILiveAnswering;
- (BOOL)isLiveAnswering;
- (NSString *_Nullable)getLiveAnswerName;

- (BOOL)isSenderMyself;

- (nullable NSArray <MobileRTCQAAnswerItem *>*)getAnswerlist;
@end


