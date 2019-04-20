/**
 * In this example we read from a microphone - ALSA capture device - and write to a
 * speaker - ALSA playback device. The key to getting this right is to use the same
 * frames per period for both, if this number is not the same you will get jitter.
 * So, if you are having issues consider increasing or decreasing FRAMES_PER_PERIOD.
 * 
 * 
 * For all the information require to read through the source code, please visit this
 * amazing source: https://www.linuxjournal.com/article/6735?page=0,1.
 * 
 * TO COMPILE: g++ play_plain_audio.cpp ALSADevices.cpp -o out -lasound
 * TO RUN: ./out
 */
#include "ALSADevices.hpp"
#include "constants.h"
#include <iostream>
#include "speech_sdk.h"
#include  "record.hpp"

ALSACaptureDevice microphone("plughw:1,0,0", SAMPLING_RATE, CHANNELS, FRAMES_PER_PERIOD, FORMAT);
ALSAPlaybackDevice speaker("plughw:1,0,0", SAMPLING_RATE, CHANNELS, FRAMES_PER_PERIOD, FORMAT);

void  *record_routine(void *a) {
    microphone.open();
    speaker.open();
    char* buffer = microphone.allocate_buffer();
    unsigned int frames_captured, frames_played;
    do{
	try{
        frames_captured = microphone.capture_into_buffer(buffer, FRAMES_PER_PERIOD);

	mobvoi_send_speech_frame( (char *)buffer, sizeof(short)*frames_captured); 
//        frames_played = speaker.play_from_buffer(buffer, FRAMES_PER_PERIOD);
	}catch(int a){
            microphone.close();
	    speaker.close();
	    return 0;
	
	}
	
	
    }while(1);

    microphone.close();
    speaker.close();
    return 0;
}
/*
int record_start(struct record_s *record_a){
	if (record_a){
		int ret  =0;
//		int ret =  pthread_create(&record_a->tid,NULL,record_routine,NULL);
		if (ret <0) return -1;
		record_a->running =1;
		return  0;
	
	}
	return  -1;


}
*/
