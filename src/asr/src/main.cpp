#include "record.hpp"

#include "ALSADevices.hpp"
#include "constants.h"
#include <iostream>
#include "kws.h"

#include <pthread.h>

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Int8.h"
#include <sstream>

struct kws_s kws;

int main(int argc,char **argv){
	int ret;
	int err;
	ros::init(argc, argv, "asr");
    	ros::NodeHandle n;
    	ros::Rate loop_rate(1);
    	//ros::Subscriber chatterCallbackSub = n.subscriber("chatter", 1000, chatterCallback);
	ros::Publisher Pub = n.advertise<std_msgs::String>("/voiceWords", 1000);
	
	//static char *result=NULL;
//	struct kws_s kws1;
	int *a = 0;
	int count;

	pthread_t tid;
	//ret = kws_start(&kws1);
	ret = kws_start(&kws);
	err=pthread_create(&tid,NULL,record_routine,&a);
	
	//std_msgs::String msg;
	//msg=result;
	
	//pthread_join(tid,NULL);  //主线程等待对等线程终止
	std_msgs::String msg;
//	msg.data="xx";
	while(ros::ok){
//	msg.data=kws1.command;
	if(kws.command=='1'){
		
		msg.data = "11";

	}
	else if(kws.command=='2'){
		
		msg.data = "22";
	}
	else if(kws.command=='3'){
		
		msg.data = "33";
	}
	else if(kws.command=='4'){
	
		msg.data = "44";
	}
	else if(kws.command=='5'){
	
		msg.data = "55";
	}
		Pub.publish(msg);
		kws.command='0';
		msg.data="00";	
		ros::spinOnce();
	        loop_rate.sleep();
	}
	
return 0;

}
