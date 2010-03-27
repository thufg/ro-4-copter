#ifndef timer_h_inc
#define timer_h_inc

#include <stdint.h>

void timer0_init();
void timer1_init();
volatile int32_t timer0_elapsed();
volatile int32_t timer1_elapsed();

#endif