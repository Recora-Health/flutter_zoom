/**
 * @file MobileRTCShareAudioSender.h
 * @brief Audio sharing sender for screen share with audio.
 */

#import <Foundation/Foundation.h>
#import <MobileRTC/MobileRTCConstants.h>


/**
 * @class MobileRTCShareAudioSender
 * @brief Send share audio raw data.
 */
@interface MobileRTCShareAudioSender : NSObject

/**
 * @brief Send share audio raw data.
 * @param data The audio data’s address.
 * @param length The audio data’s length, in even numbers.
 * @param rate The audio data’s sampling rate.
 * @param channel The channel type, default is MobileRTCAudioChannel_Mono.
 * @return The send action result.
 * @warning Support sample Rate.
 * @note Memo 8000/11025/16000/32000/44100/48000/50000/50400/96000/192000, Stereo: 8000/16000/32000/44100/48000/50000/50400/96000/192000, Channels: mono and stereo, resolution: little-endian, 16bit.
 */
- (MobileRTCRawDataError)sendShareAudio:(char *)data dataLength:(NSUInteger)length sampleRate:(NSUInteger)rate audioChannel:(MobileRTCAudioChannel)channel;

@end


