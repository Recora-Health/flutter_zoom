/**
 * @file MobileRTCMeetingService+Polling.h
 * @brief Meeting+Polling service functionality and management.
 */

#import <MobileRTC/MobileRTC.h>


/**
 * @class MobileRTCPollingItem
 * @brief Polling item interface.
 */
@interface MobileRTCPollingItem : NSObject
/**
 * @brief Polling ID.
 * @return If the function succeeds, the return value is the polling ID. Otherwise, the return value is nil.
 */
- (NSString *_Nullable)getPollingID;
/**
 * @brief Polling name.
 * @return If the function succeeds, the return value is the polling name. Otherwise, the return value is nil.
 */
- (NSString *_Nullable)getPollingName;
/**
 * @brief Polling type.
 * @return If the function succeeds, the return value is the polling type. Otherwise, the return value is MobileRTCPollingType_Unknown.
 */
- (MobileRTCPollingType)getPollingType;
/**
 * @brief Polling status.
 * @return If the function succeeds, the return value is the polling status. Otherwise, the return value is MobileRTCPollingStatus_Unknown.
 */
- (MobileRTCPollingStatus)getPollingStatus;
/**
 * @brief Polling question count.
 * @return If the function succeeds, the return value is the polling question count. Otherwise, the return value is 0.
 */
- (NSInteger)getPollingQuestionCount;
/**
 * @brief Count of total voted users.
 * @return If the function succeeds, the return value is the total voted user count. Otherwise, the return value is 0.
 */
- (NSInteger)getTotalVotedUserCount;
/**
 * @brief Determine if is library polling.
 * @return YES means is library polling, otherwise not.
 * @note This function is only available for the library polling.
 */
- (BOOL)isLibraryPolling;
@end

/**
 * @class MobileRTCPollingAnswerItem
 * @brief Polling answer item interface.
 */
@interface MobileRTCPollingAnswerItem : NSObject
/**
 * @brief Polling ID of answer item.
 * @return If the function succeeds, the return value is the polling ID. Otherwise, the return value is nil.
 */
- (NSString *_Nullable)getPollingID;
/**
 * @brief Polling question ID.
 * @return If the function succeeds, the return value is the polling question ID. Otherwise, the return value is nil.
 */
- (NSString *_Nullable)getPollingQuestionID;
/**
 * @brief Polling sub-question ID.
 * @return If the function succeeds, the return value is the polling sub-question ID. Otherwise, the return value is nil.
 */
- (NSString *_Nullable)getPollingSubQuestionID;
/**
 * @brief Polling answer ID.
 * @return If the function succeeds, the return value is the polling answer ID. Otherwise, the return value is nil.
 */
- (NSString *_Nullable)getPollingAnswerID;
/**
 * @brief Polling answer name.
 * @return If the function succeeds, the return value is the polling answer name. Otherwise, the return value is nil.
 */
- (NSString *_Nullable)getPollingAnswerName;
/**
 * @brief Polling answered content.
 * @return If the function succeeds, the return value is the polling answered content. Otherwise, the return value is nil.
 */
- (NSString *_Nullable)getPollingAnsweredContent;
/**
 * @brief Determine if is checked.
 * @return YES means is checked, otherwise not.
 * @note This property has no meaning for the corrent answer.
 */
- (BOOL)isChecked;
@end

/**
 * @class MobileRTCPollingQuestionItem
 * @brief Polling question item interface.
 */
@interface MobileRTCPollingQuestionItem : NSObject
/**
 * @brief Polling ID of question item.
 * @return If the function succeeds, the return value is the polling ID. Otherwise, the return value is nil.
 */
- (NSString *_Nullable)getPollingID;
/**
 * @brief Polling question ID.
 * @return If the function succeeds, the return value is the polling question ID. Otherwise, the return value is nil.
 */
- (NSString *_Nullable)getPollingQuestionID;
/**
 * @brief Polling question name.
 * @return If the function succeeds, the return value is the polling question name. Otherwise, the return value is nil.
 */
- (NSString *_Nullable)getPollingQuestionName;
/**
 * @brief Polling question type.
 * @return If the function succeeds, the return value is the polling question type. Otherwise, the return value is MobileRTCPollingQuestionType_Unknown.
 */
- (MobileRTCPollingQuestionType)getPollingQuestionType;
/**
 * @brief The count of answered questions.
 * @return If the function succeeds, the return value is the count of answered questions. Otherwise, the return value is 0.
 */
- (NSInteger)getAnsweredCount;
/**
 * @brief Determine if is required.
 * @return YES means is required, otherwise not.
 */
- (BOOL)isRequired;
/**
 * @brief Get the list of polling question's subquestion.
 * @return If the function succeeds, the return value is NSArray<MobileRTCPollingQuestionItem*>. Otherwise, the return value is nil.
 */
- (NSArray <MobileRTCPollingQuestionItem *> * _Nullable)getPollingSubQuestionItemList;
/**
 * @brief Get the list of polling question or subquestion's answer. 
 * @return If the function succeeds, the return value is NSArray<MobileRTCPollingAnswerItem*>. Otherwise, the return value is nil.
 */
- (NSArray <MobileRTCPollingAnswerItem *> * _Nullable)getPollingAnswerItemList;
@end

/**
 * @class MobileRTCPollingAnswerResultItem
 * @brief Polling answer result item interface.
 */
@interface MobileRTCPollingAnswerResultItem : NSObject
/**
 * @brief Polling ID of answer result item.
 * @return If the function succeeds, the return value is the polling ID.
 */
- (NSString *_Nullable)getPollingID;
/**
 * @brief Polling queston ID.
 * @return If the function succeeds, the return value is the polling question ID.
 */
- (NSString *_Nullable)getPollingQuestionID;
/**
 * @brief Polling sub-queston ID.
 * @return If the function succeeds, the return value is the polling sub-question ID.
 */
- (NSString *_Nullable)getPollingSubQuestionID;
/**
 * @brief Polling answer ID.
 * @return If the function succeeds, the return value is the polling answer ID.
 */
- (NSString *_Nullable)getPollingAnswerID;
/**
 * @brief Polling answer name.
 * @return If the function succeeds, the return value is the polling answer name.
 */
- (NSString *_Nullable)getPollingAnswerName;
/**
 * @brief Query how many participants selected this answer.
 * @return If the function succeeds, the return value is the selected count.
 */
- (NSInteger)getSelectedCount;
@end


/**
 * @brief Polling  feature of meeting service.
 */
@interface MobileRTCMeetingService (Polling)

#pragma mark - for all users -
/**
 * @brief Determine whether the current meeting can do the polling.
 * @return YES indicates you can do polling.
 */
- (BOOL)canDoPolling;

/**
 * @brief Get the active poll's ID.
 * @return The shared result or started poll's ID.
 */
- (NSString *_Nullable)getActivePollingID;

/**
 * @brief Get the list of polling question's subquestion.
 * @param pollingID pollingID Specify the question's polling ID.
 * @return If the function succeeds, the return value is NSArray<MobileRTCPollingQuestionItem*>. Otherwise, the return value is nil.
 */
- (NSArray <MobileRTCPollingQuestionItem *> * _Nullable)getPollingQuestionItemList:(NSString *_Nullable)pollingID;

/**
 * @brief Determine if the right answer item list can be allowed to get.
 * @param pollingID Specify the right answer's polling ID.
 * @return Yes means can get th right.
 */
- (BOOL)canGetRightAnswerItemList:(NSString *_Nullable)pollingID;

/**
 * @brief Get the list of polling question or subquestion's right answer.
 * @param pollingID Specify the right answer's polling ID.
 * @return If the function succeeds, the return value is NSArray<MobileRTCPollingAnswerItem*>. Otherwise, the return value is nil.
 */
- (NSArray <MobileRTCPollingAnswerItem *> * _Nullable)getPollingRightAnswerItemList:(NSString *_Nullable)pollingID;

/**
 * @brief Determine if the answer result list can be show.
 * @param pollingID Specify the right answer's polling ID.
 * @return Yes means can show the answer list.
 */
- (BOOL)canShowAnswerResultList:(NSString *_Nullable)pollingID;

/**
 * @brief Get the list of polling answer result item.
 * @param pollingID Specify the right answer's polling ID.
 * @return If the function succeeds, the return value is NSArray<MobileRTCPollingAnswerResultItem*>. Otherwise, the return value is nil.
 */
- (NSArray <MobileRTCPollingAnswerResultItem *> * _Nullable)getPollingAnswerResultItemList:(NSString *_Nullable)pollingID;

/**
 * @brief Get the polling item object of specified polling ID.
 * @param pollingID Specify the polling ID for which you want to get the information.
 * @return If the function succeeds, the return value is MobileRTCPollingItem. Otherwise, the return value is nil.
 */
- (MobileRTCPollingItem * _Nullable)getPollingItemByID:(NSString *_Nullable)pollingID;

/**
 * @brief Get the polling question's image path.
 * @param pollingID Specify the answer's polling ID.
 * @param questionID Specify the answer's question ID.
 * @return If the function succeeds, the return value is the question's image path, Otherwise the function fails, and the return value is nil.
 */
- (NSString *_Nullable)getPollingQuestionImagePath:(NSString *_Nullable)pollingID questionID:(NSString *_Nullable)questionID;

/**
 * @brief Get the polling question's minimum length.
 * @param pollingID Specify the poll's polling ID.
 * @param questionID Specify the question's question ID.
 * @return The integer value of question's minimum length.
 */
- (NSInteger)getQuestionCharactersMinLen:(NSString*_Nullable)pollingID questionID:(NSString*_Nullable)questionID;

/**
 * @brief Get the polling question's maximum length.
 * @param pollingID Specify the poll's polling ID.
 * @param questionID Specify the question's question ID.
 * @return The integer value of question's maximum length.
 */
- (NSInteger)getQuestionCharactersMaxLen:(NSString*_Nullable)pollingID questionID:(NSString*_Nullable)questionID;

/**
 * @brief Determine if the question is case sensitive.
 * @param pollingID Specify the question's polling ID.
 * @param questionID Specify the question's question ID.
 * @return This function can only be used by fill blank questions.
 */
- (BOOL)isQuestionCaseSensitive:(NSString *_Nullable)pollingID questionID:(NSString *_Nullable)questionID;

#pragma mark - for host -

/**
 * @brief Determine if the host can add polling.
 * @return The result of it.
 * @warning Only the origin host can add polling.
 */
- (BOOL)canAddPolling;

/**
 * @brief Create polling in a web browser.
 * @return If the function succeeds, the return value is MobileRTCSDKError_Success. Otherwise the function fails. 
 */
- (MobileRTCSDKError)addPolling;

/**
 * @brief Determine if the host can edit polling.
 * @param pollingID Specify the edit poll's polling ID.
 * @return Can edit or not.
 * @warning Only the origin host can edit polling.
 */
- (BOOL)canEditPolling:(NSString *_Nullable)pollingID;

/**
 * @brief Open edit polling in a web browser.
 * @param pollingID Specify the edit poll's polling ID.
 * @return If the function succeeds, the return value is MobileRTCSDKError_Success. Otherwise the function fails. 
 */
- (MobileRTCSDKError)editPolling:(NSString *_Nullable)pollingID;

/**
 * @brief Determine if the host can delete polling.
 * @param pollingID Specify the edit poll's polling ID.
 * @return Can delete the polling or not.
 * @warning Only the origin host can delete polling.
 */
- (BOOL)canDeletePolling:(NSString *_Nullable)pollingID;

/**
 * @brief Delete the polling.
 * @param pollingID Specify the edit poll's polling ID.
 * @return If the function succeeds, the return value is MobileRTCSDKError_Success. Otherwise the function fails. 
 */
- (MobileRTCSDKError)deletePolling:(NSString *_Nullable)pollingID;

/**
 * @brief Determine if the host can duplicate polling.
 * @param pollingID Specify the duplicate poll's polling ID.
 * @return Can duplicate the polling or not.
 * @warning Only the origin host can duplicate polling.
 */
- (BOOL)canDuplicatePolling:(NSString *_Nullable)pollingID;

/**
 * @brief Duplicate the polling.
 * @param pollingID Specify the edit poll's polling ID.
 * @return If the function succeeds, the return value is MobileRTCSDKError_Success. Otherwise the function fails. 
 */
- (MobileRTCSDKError)duplicatePolling:(NSString *_Nullable)pollingID;

/**
 * @brief Determine if the user can view polling results in the browser.
 * @param pollingID Specify the duplicate poll's polling ID.
 * @return Can view the polling result or not.
 */
- (BOOL)canViewPollingResultFromBrowser:(NSString *_Nullable)pollingID;

/**
 * @brief Open a polling result in the web browser.
 * @param pollingID Specify the edit poll's polling ID.
 * @return If the function succeeds, the return value is MobileRTCSDKError_Success. Otherwise the function fails. 
 */
- (MobileRTCSDKError)viewPollingResultFromBrowser:(NSString *_Nullable)pollingID;

/**
 * @brief Get the list of poll item.
 * @return If the function succeeds, the return value is a pointer to the NSArray<MobileRTCPollingItem *>. Otherwise, the return value is nil.
 */
- (NSArray <MobileRTCPollingItem *> * _Nullable)getPollingItemList;

/**
 * @brief Determine if the host or co-host can start the polling.
 * @param pollingID Specify the poll's polling ID.
 * @return Can start the poll or not.
 */
- (BOOL)canStartPolling:(NSString *_Nullable)pollingID;

/**
 * @brief Start the polling.
 * @param pollingID Specify the edit poll's polling ID.
 * @return If the function succeeds, the return value is MobileRTCSDKError_Success. Otherwise the function fails. 
 */
- (MobileRTCSDKError)startPolling:(NSString *_Nullable)pollingID;

/**
 * @brief Stop the polling.
 * @param pollingID Specify the edit poll's polling ID.
 * @return If the function succeeds, the return value is MobileRTCSDKError_Success. Otherwise the function fails. 
 */
- (MobileRTCSDKError)stopPolling:(NSString *_Nullable)pollingID;

/**
 * @brief Determine if the host or co-host can restart the polling.
 * @param pollingID Specify the poll's polling ID.
 * @return Can restart the poll or not.
 */
- (BOOL)canRestartPolling:(NSString *_Nullable)pollingID;

/**
 * @brief Restart the polling.
 * @param pollingID Specify the edit poll's polling ID.
 * @return If the function succeeds, the return value is MobileRTCSDKError_Success. Otherwise the function fails. 
 */
- (MobileRTCSDKError)restartPolling:(NSString *_Nullable)pollingID;

/**
 * @brief Determine if the host or co-host can share the poll's result.
 * @param pollingID Specify the poll's polling ID.
 * @return Can share the poll result or not.
 */
- (BOOL)canSharePollingResult:(NSString *_Nullable)pollingID;

/**
 * @brief Share the poll's result.
 * @param pollingID Specify the edit poll's polling ID.
 * @return If the function succeeds, the return value is MobileRTCSDKError_Success. Otherwise the function fails. 
 */
- (MobileRTCSDKError)startSharePollingResult:(NSString *_Nullable)pollingID;

/**
 * @brief Stop the poll's result.
 * @param pollingID Specify the edit poll's polling ID.
 * @return If the function succeeds, the return value is MobileRTCSDKError_Success. Otherwise the function fails. 
 */
- (MobileRTCSDKError)stopSharePollingResult:(NSString *_Nullable)pollingID;

/**
 * @brief Set to enable show right answer to participants when share quiz's result.
 * @param enable YES indicates to enable. NO not.
 * @return If the function succeeds, the return value is MobileRTCSDKError_Success. Otherwise the function fails. 
 */
- (MobileRTCSDKError)enableGetRightAnswerList:(BOOL)enable;

/**
 * @brief Determine if the host can download poll's result from browser.
 * @return Can download the poll result or not.
 */
- (BOOL)canDownloadResult;

/**
 * @brief Download all stopped poll's result from browser.
 * @return If the function succeeds, the return value is MobileRTCSDKError_Success. Otherwise the function fails. 
 */
- (MobileRTCSDKError)downLoadResult;

#pragma mark - for attendee -

/**
 * @brief Attendee set answer's check.
 * @param answerItem Specify the answer item where you want to set check.
 * @param check Specify whether you want to select the answer or not.
 * @return If the function succeeds, the return value is @c MobileRTCSDKError_Success. Otherwise the function fails. 
 * @warning This function should only be used by single, matching, rank order, multi, rating scale, or drop down questions.
 */
- (MobileRTCSDKError)setAnswerCheck:(MobileRTCPollingAnswerItem * _Nullable)answerItem check:(BOOL)check;

/**
 * @brief Attendee set answer's content.
 * @param answerItem Specify the answer item  where you want to ansswer.
 * @param answerText Specify you want to reply answer's content.
 * @return If the function succeeds, the return value is @c MobileRTCSDKError_Success. Otherwise the function fails. 
 * @warning This function should only be used by fill blank, short answer, and long answer questions.
 */
- (MobileRTCSDKError)setAnswerContent:(MobileRTCPollingAnswerItem * _Nullable)answerItem answerText:(NSString *_Nullable)answerText;

/**
 * @brief Determine if the attendee can submit the polling.
 * @param pollingID Specify the submit poll's polling ID.
 * @return Can submit the polling or not.
 */
- (BOOL)canSubmitPolling:(NSString *_Nullable)pollingID;

/**
 * @brief Attendee set answer's content.
 * @param pollingID pollingID Specify the submit poll's polling ID.
 * @return If the function succeeds, the return value is MobileRTCSDKError_Success. Otherwise the function fails. 
 */
- (MobileRTCSDKError)submitPolling:(NSString *_Nullable)pollingID;
@end

