#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "rs232.h"

#define BUF_SIZE 100

int i=0;
int cport_nr=24; /* /dev/ttyUSB0 */
int bdrate=115200; /* 9600 baud */

char mode[]={'8','N','1',0}; // 8 data bits, no parity, 1 stop bit
char str_send[2][BUF_SIZE]; // send data buffer
unsigned char str_recv[BUF_SIZE]; // recv data buffer

int Setup();

void Write(const char *data);

const char* Read();

