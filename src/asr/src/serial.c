#include "serial.h"
int serial_write(const char * msg){

	int fd;
	if(wiringPiSetupSys() < 0){printf("init sys fail\n"); return 1;}
	if((fd = serialOpen(COMPORT,115200)) < 0 ){  printf("open serial fail\n"); return 1;}
	serialPuts(fd,msg);
	serialClose(fd);

	return  0;
}
