#ifndef _KWS_H
#define _KWS_H
#ifdef __cplusplus
extern "C"
{
#endif
#include <pthread.h>
#include "speech_sdk.h"
struct kws_s {
    pthread_t tid;
    int running;
		int out_switch;
		pthread_mutex_t mutex;
		pthread_cond_t cond;
		mobvoi_recognizer_handler_vtable* speech_handlers;
		bool wakeup =0;
//		static const std::string kAppKey;
		volatile bool in_the_session;
		volatile mobvoi_recognizer_type type;
		char command;

};
//struct kws_s kws;
int  kws_start(struct kws_s *kws);

void *kws_routine(void *user);

int kws_release(struct kws_s *kws);
int kws_init(struct kws_s *kws);
void on_remote_silence_detected();
void on_partial_transcription(const char* result);
void on_final_transcription(const char* result);
void on_result(const char* result);
void on_error(int error_code);
void on_local_silence_detected();
void on_volume(float spl);
void wakeup_kws(struct kws_s *kws);
#ifdef __cplusplus
}
#endif
#endif // _KWS_H
