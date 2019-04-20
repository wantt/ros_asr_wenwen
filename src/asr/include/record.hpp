#ifndef _RECORD_H
#define _RECORD_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <pthread.h>

struct record {

		pthread_t tid;
		int running;

};

int record_start(struct record_s *record);
void *record_routine(void *a);



#ifdef __cplusplus
}
#endif

#endif
