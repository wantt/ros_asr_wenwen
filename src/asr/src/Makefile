# wantongtang@foxmail.com 20190410
CC=g++
main:record.o ALSADevices.o kws.o
	g++   -std=c++11   ALSADevices.o kws.o  main.cpp  -lasound  -o main -I../../include -L../../lib/x84_64/ -lmobvoisdk -lpthread  -lcrypt -lm -lrt 


#main:record.o ALSADevices.o kws.o
#	g++   -std=c++11   ALSADevices.o kws.o  serial.o main.cpp  -lasound  -o main -I../../include -L../../lib/x84_64/ -lmobvoisdk -lpthread -lwiringPi  -lcrypt -lm -lrt 
ALSADevices.o:
	g++ -c ALSADevices.cpp -I../../include  -std=c++11
record.o:
	g++ -c record.c -I../../include  -std=c++11
#kws.o: serial.o 
#	g++ -c kws.c   -I../../include  -std=c++11

kws.o: 
	g++ -c kws.c   -I../../include  -std=c++11

#serial.o:
#	g++ -c serial.c -I../../include  -std=c++11 
clean:
	rm -rf *.o main	
