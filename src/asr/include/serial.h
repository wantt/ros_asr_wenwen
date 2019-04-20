#ifndef _SERIAL_H
#define _SERIAL_H

#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdio.h>
#include <unistd.h>

//#define COMPORT "/dev/serial0"
#define COMPORT "/dev/serial0"
int serial_write(const char * msg);

#endif

