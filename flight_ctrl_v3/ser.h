#ifndef ser_h
#define ser_h

#include <stdio.h>

#include "config.h"

// circular buffer data structure
typedef struct _ser_buff
{
	unsigned char * d; // data buffer
	unsigned int h; // head pointer
	unsigned int t; // tail pointer
	unsigned int s; // size
	unsigned char f; // flag
}
ser_buff_s;

void ser0_init(unsigned short, unsigned char, unsigned char);
#ifdef __AVR_ATmega644P__
void ser1_init(unsigned short, unsigned char, unsigned char);
#endif
void ser_tx(unsigned char, unsigned char);
void ser_tx_0(char, FILE *);
#ifdef __AVR_ATmega644P__
void ser_tx_1(char, FILE *);
#endif
unsigned char ser_tx_is_busy(unsigned char);
unsigned char ser_rx(unsigned char, unsigned char *);

#endif