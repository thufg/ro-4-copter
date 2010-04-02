#ifndef ser_h
#define ser_h

#include <stdio.h>
#include <stdint.h>

#include "config.h"

// circular buffer data structure
typedef struct _ser_buff
{
	uint8_t * d; // data buffer
	uint16_t h; // head pointer
	uint16_t t; // tail pointer
	uint16_t s; // size
	uint8_t f; // flag
}
ser_buff_s;

void ser0_init(uint16_t, uint8_t, uint8_t);
#ifdef __AVR_ATmega644P__
void ser1_init(uint16_t, uint8_t, uint8_t);
#endif
void ser_tx(uint8_t, uint8_t);
void ser_tx_0(char, FILE *);
#ifdef __AVR_ATmega644P__
void ser_tx_1(char, FILE *);
#endif
uint8_t ser_tx_is_busy(uint8_t);
uint8_t ser_rx(uint8_t, uint8_t *);
void ser_num(uint8_t, int32_t);

#endif