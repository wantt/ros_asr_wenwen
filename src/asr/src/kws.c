// wantongtang@foxmail.com.

#include <assert.h>
#include <fstream>
#include <iostream>
#include <pthread.h>
#include <string>
#include <unistd.h>
#include <vector>
#include <string.h>
#include "speech_sdk.h"
#include "kws.h"
//#include "serial.h"

extern struct kws_s kws;

static const char
    * kMultiKeywords[] = {"前进", "后退", "左转", "右转", "停止"};

static const std::string kOfflineModelName = "multi_keywords_test";
static const std::string kOfflineModel = "offline_model";
static const std::string kAppKey = "2844F2D8DF07F35DB998BDDA9D130708";

//struct kws_s *kws;




int kws_start(struct kws_s *kws2) {
//kws=kws2;
    //if (kws) {
    if (1) {
        int ret;
        ret = pthread_create(&kws.tid, NULL, kws_routine, &kws);
        if (ret < 0) return -1;
        kws.running = 1;
        kws.out_switch = 0;
        return 0;
    }

    return -1;
}

int kws_release(struct kws_s *kws) {
    if (kws) {
        kws->running = 0;
        pthread_join(kws->tid, NULL);

        //TODO
  // SDK clean up
	  std::cout << "start sdk cleanup" << std::endl;
	  mobvoi_sdk_cleanup();
  	std::cout << "end sdk cleanup" << std::endl;
	  delete kws->speech_handlers;
	  std::cout << "end dummy sender" << std::endl;
	  pthread_mutex_destroy(&(kws->mutex));
	  pthread_cond_destroy(&(kws->cond));
	  pthread_join(kws->tid, NULL);

    }
    return 0;
}

int kws_init(struct kws_s *kws){
    if (!kws) return -1;
		// TODO
		
//  static const std::string kOfflineModelName = "multi_keywords_test";
		kws->in_the_session = true;
  	//kws->type = MOBVOI_RECOGNIZER_ONLINE_ASR ;
  	kws->type = MOBVOI_RECOGNIZER_KEYWORDS ;

	 pthread_mutex_init(&(kws->mutex), NULL);
	 pthread_cond_init(&(kws->cond), NULL);

  mobvoi_sdk_init(kAppKey.c_str());
  mobvoi_recognizer_init_offline(); //wtt
  kws->speech_handlers =
      new mobvoi_recognizer_handler_vtable;
  assert(kws->speech_handlers != NULL);
  memset(kws->speech_handlers, 0, sizeof(mobvoi_recognizer_handler_vtable));
  kws->speech_handlers->on_error = &on_error;
  kws->speech_handlers->on_partial_transcription = &on_partial_transcription;
  kws->speech_handlers->on_final_transcription = &on_final_transcription;
  kws->speech_handlers->on_local_silence_detected = &on_local_silence_detected;
  kws->speech_handlers->on_remote_silence_detected = &on_remote_silence_detected;
  kws->speech_handlers->on_result = &on_result;
  kws->speech_handlers->on_volume = &on_volume;
  mobvoi_recognizer_set_handler(kws->speech_handlers);
	
   mobvoi_recognizer_set_keywords(sizeof(kMultiKeywords) / sizeof(kMultiKeywords[0]), kMultiKeywords, kOfflineModelName.c_str());
  mobvoi_recognizer_set_params(kOfflineModel.c_str(), kOfflineModelName.c_str());

  mobvoi_recognizer_build_keywords(kOfflineModel.c_str());

  mobvoi_recognizer_start(kws->type);
    return 0;
}
	void on_remote_silence_detected() {
  	std::cout << "--------> dummy on_remote_silence_detected" << std::endl;
	}
	void on_partial_transcription(const char* result) {
	int count;

		if (strstr(result,"前进") ||strstr(result,"请进")){
//                        serial_write("11");
//			count=11;
			kws.command='1';
			std::cout <<"关键词检测到1\n\n"<<result  <<std::endl;
		//	std::cout <<"11"<<std::endl;
                }
		if (strstr(result,"后退") ){
       //                 serial_write("n22");
			kws.command='2';
			std::cout <<"关键词检测到1\n\n"<<result  <<std::endl;
                }
	
			if (strstr(result,"左转")){
        //                serial_write("33");
			kws.command='3';
			std::cout <<"关键词检测到1\n\n"<<result  <<std::endl;
                }
			if (strstr(result,"右转")){
          //              serial_write("44");
			kws.command='4';
			std::cout <<"关键词检测到1\n\n"<<result  <<std::endl;
                }
			if (strstr(result,"停止")){
            //            serial_write("55");
			kws.command='5';
			std::cout <<"关键词检测到1\n\n"<<result  <<std::endl;
                }
		
//			if(kws_detected(result)){
			if(0){
			std::cout <<"关键词检测到\n\n"<<result  <<std::endl;
		  	if (kws.type == MOBVOI_RECOGNIZER_ONLINE_ASR) {
  		  	pthread_mutex_lock(&(kws.mutex));
	  		  kws.in_the_session = false;
  	  		pthread_cond_signal(&(kws.cond));
		    	pthread_mutex_unlock(&(kws.mutex));
                        }


		}
	}

	void on_final_transcription(const char* result) {
	int count = 100;
		if (strstr(result,"前进")){
//			serial_write("11");
			kws.command='1';
//			count=11;
				for(int i=0; i < count; i++)
			std::cout <<"前进\n\n" <<std::endl;
		}
		if (strstr(result,"后退")){
//			serial_write("22");
			kws.command='2';
				for(int i=0; i < count; i++)
			std::cout <<"后退\n\n" <<std::endl;
		}
		if (strstr(result,"左转")){
//			serial_write("33");
			kws.command='3';
				for(int i=0; i < count; i++)
			std::cout <<"左转\n\n" <<std::endl;
		}
		if (strstr(result,"右转")){
//			serial_write("44");
			kws.command='4';
				for(int i=0; i < count; i++)
			std::cout <<"右转\n\n" <<std::endl;
		}
		if (strstr(result,"停止")){
//			serial_write("55");
			kws.command='5';
				for(int i=0; i < count; i++)
			std::cout <<"停止\n\n" <<std::endl;
		}
		if (strstr(result,"打开图像模式")){
				for(int i=0; i < count; i++)
			std::cout <<"打开图像模式\n\n" <<std::endl;
		}
		if (strstr(result,"画面亮一点")){
				for(int i=0; i < count; i++)
			std::cout <<"画面亮一点\n\n" <<std::endl;
		}
		if (strstr(result,"画面暗一点")){
				for(int i=0; i < count; i++)
			std::cout <<"画面暗一点\n\n" <<std::endl;
		}
			if (strstr(result,"打开菜单")){
				for(int i=0; i < count; i++)
			std::cout <<"打开菜单\n\n" <<std::endl;
		}
			if (strstr(result,"上一页")){
				for(int i=0; i < count; i++)
			std::cout <<"上一页\n\n" <<std::endl;
		}
	

			if (strstr(result,"下一页")){
				for(int i=0; i < count; i++)
			std::cout <<"下一页\n\n" <<std::endl;
		}

			if (strstr(result,"返回")){
				for(int i=0; i < count; i++)
			std::cout <<"返回\n\n" <<std::endl;
		}
			if (strstr(result,"退出")){
				for(int i=0; i < count; i++)
			std::cout <<"退出\n\n" <<std::endl;
		}

			if (strstr(result,"打开屏显")||strstr(result,"打开评选")){
				for(int i=0; i < count; i++)
			std::cout <<"打开屏显\n\n" <<std::endl;
		}

			if (strstr(result,"打开白板")||strstr(result,"打开白斑")){
				for(int i=0; i < count; i++)
			std::cout <<"打开白板\n\n" <<std::endl;
		}
			if (strstr(result,"开机")){
				for(int i=0; i < count; i++)
			std::cout <<"开机\n\n" <<std::endl;
		}
			if (strstr(result,"关机")){
				for(int i=0; i < count; i++)
			std::cout <<"关机\n\n" <<std::endl;
		}

			if (strstr(result,"截图")){
			std::cout <<"截图\n\n" <<std::endl;
				for(int i=0; i < count; i++)
			std::cout <<"截图\n\n" <<std::endl;
		}

			if (strstr(result,"打开画笔")||strstr(result,"打开画壁")){
				for(int i=0; i < count; i++)
			std::cout <<"打开画笔\n\n" <<std::endl;
		}
			if (strstr(result,"打开橡皮擦")){
				for(int i=0; i < count; i++)
			std::cout <<"打开橡皮擦\n\n" <<std::endl;
		}
			if (strstr(result,"清屏")||strstr(result,"清平")){
				for(int i=0; i < count; i++)
			std::cout <<"清屏\n\n" <<std::endl;
		}
			if (strstr(result,"打开浏览器")){
				for(int i=0; i < count; i++)
			std::cout <<"打开浏览器\n\n" <<std::endl;
		}
			if (strstr(result,"打开会议计时")||strstr(result,"打开会议纪实")){
				for(int i=0; i < count; i++)
			std::cout <<"打开会议计时\n\n" <<std::endl;
		}

			if (strstr(result,"打开信号源")){
				for(int i=0; i < count; i++)
			std::cout <<"打开信号源\n\n" <<std::endl;
		}
			if (strstr(result,"打开视频一")){
			std::cout <<"打开视频1\n\n" <<std::endl;
				for(int i=0; i < count; i++)
			std::cout <<"打开视频1\n\n" <<std::endl;
		}
			if (strstr(result,"打开视频二")){
				for(int i=0; i < count; i++)
			std::cout <<"打开视频2\n\n" <<std::endl;
		}
			if (strstr(result,"打开分量")||strstr(result,"打开风量")||strstr(result,"打开分凉")){
				for(int i=0; i < count; i++)
			std::cout <<"打开分量\n\n" <<std::endl;
		}

			if (strstr(result,"切到安卓")){
				for(int i=0; i < count; i++)
			std::cout <<"切到安卓\n\n" <<std::endl;
		}

			if (strstr(result,"打开多媒体")){
				for(int i=0; i < count; i++)
			std::cout <<"打开多媒体\n\n" <<std::endl;
		}
			if (strstr(result,"打开声音模式")){
				for(int i=0; i <count; i++)
			std::cout <<"打开声音模式\n\n" <<std::endl;
		}


			if (strstr(result,"打开模拟电视")){
				for(int i=0; i < count; i++)
				std::cout <<"打开模拟电视\n\n" <<std::endl;
			}
	
			if (strstr(result,"打开内置电脑")||strstr(result,"打开励志电脑")||strstr(result,"打开那些电脑")){
				for(int i=0; i < count; i++)
				std::cout <<"打开内置电脑\n\n" <<std::endl;
			}
				if (strstr(result,"打开HDMI一")){
				for(int i =0;i <count; i++)
				std::cout <<"打开HDMI1\n\n" <<std::endl;
			}
				if (strstr(result,"打开HDMI二")){
				for(int i =0;i <count; i++)
				std::cout <<"打开HDMI2\n\n" <<std::endl;
			}
				if (strstr(result,"打开HDMI三")){
				for(int i =0;i <count; i++)
				std::cout <<"打开HDMI3\n\n" <<std::endl;
			}
	
				if (strstr(result,"打开电脑一")){
				for(int i =0;i <count; i++)
				std::cout <<"打开电脑1\n\n" <<std::endl;
			}
					if (strstr(result,"打开电脑二")){
				for(int i =0;i <count; i++)
				std::cout <<"打开电脑2\n\n" <<std::endl;
			}
	
				if (strstr(result,"打开电脑三")){
				for(int i =0;i <count; i++)
				std::cout <<"打开电脑3\n\n" <<std::endl;
			}
	
				if (strstr(result,"单独听")||strstr(result,"单独亭")||strstr(result,"单读厅")){
				for(int i =0;i <count; i++)
				std::cout <<"单独听\n\n" <<std::endl;
			}
	



				if (strstr(result,"声音大一点")){
				for(int i =0;i <count; i++)
				std::cout <<"声音大一点\n\n" <<std::endl;
			}
	
		if (strstr(result,"声音小一点")){
				for(int i =0;i <count; i++)
				std::cout <<"声音小一点\n\n" <<std::endl;
			}
	

  	if (kws.type == MOBVOI_RECOGNIZER_ONLINE_ASR) {
    	pthread_mutex_lock(&(kws.mutex));
	    kws.in_the_session = false;
  	  pthread_cond_signal(&(kws.cond));
    	pthread_mutex_unlock(&(kws.mutex));
  }
}

void on_result(const char* result) {
//  std::cout << "--------> dummy on_result: " << result << std::endl;
  pthread_mutex_lock(&(kws.mutex));
  kws.in_the_session = false;
  pthread_cond_signal(&(kws.cond));
  pthread_mutex_unlock(&(kws.mutex));
}

void on_error(int error_code) {
 // std::cout << "--------> dummy on_error with error code: " << error_code
 //           << std::endl;
  pthread_mutex_lock(&(kws.mutex));
  kws.in_the_session = false;
  pthread_cond_signal(&(kws.cond));
  pthread_mutex_unlock(&(kws.mutex));
}

void on_local_silence_detected() {
  std::cout << "--------> dummy on_local_silence_detected" << std::endl;
  mobvoi_recognizer_stop();
}

void on_volume(float spl) {
  // The sound press level is here, do whatever you want
  // std::cout << "--------> dummy on_speech_spl_generated: spl = "
  //           << std::fixed << std::setprecision(6) << spl
  //           << std::endl;
}

void wakeup_kws(struct kws_s *kws){
	//*kws.wakeup = 1;
};

void *kws_routine(void *user){

	//struct kws_s *kws = (struct kws_s *)user;
	//kws = (struct kws_s *)user;
//	kws_init(kws);

  // Send the audio data in a separated thread
while(1){
//	if (kws->wakeup){
	if (1){
		kws_init(&kws);
	  pthread_mutex_lock(&(kws.mutex));
  	kws.in_the_session = true;
	  while (kws.in_the_session) {
  	  pthread_cond_wait(&(kws.cond), &(kws.mutex));
	  }
  	pthread_mutex_unlock(&(kws.mutex));
		kws_release(&kws);
		kws.wakeup=0;
//		usleep(1000*1000);
	}

}


}
