#include <avr/io.h>
#include <avr/interrupt.h>

#include "config.h"
#include "pindef.h"
#include "macros.h"

#include "timer.h"

#include "calc.h"

static volatile uint32_t last_tcnt1;
static volatile uint32_t last_tcnt0;

void timer0_init()
{
	//TIMSK0 |= _BV(OCIE0B) | _BV(OCIE0A);
	TCCR0B |= _BV(CS00) | _BV(CS02);
}

void timer1_init()
{
	last_tcnt1 = TCNT1;
	sbi(TCCR1B, CS10);
}

volatile int32_t timer1_elapsed()
{
	int32_t temp_tcnt1 = TCNT1;
	int32_t diff = ((temp_tcnt1 | 0x10000) - last_tcnt1) & 0xFFFF;
	last_tcnt1 = temp_tcnt1;
	int32_t r = calc_multi(diff, MATH_MULTIPLIER, F_CPU);
	return r;
}

volatile int32_t timer0_elapsed()
{
	int32_t temp_tcnt0 = TCNT0;
	int32_t diff = ((temp_tcnt0 | 0x100) - last_tcnt0) & 0xFF;
	last_tcnt0 = temp_tcnt0;
	int32_t r = calc_multi(diff, MATH_MULTIPLIER * 1024, F_CPU);
	return r;
}


ISR(TIMER0_COMPB_vect)
{
}

ISR(TIMER0_COMPA_vect)
{
}