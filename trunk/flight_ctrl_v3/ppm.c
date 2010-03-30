#include <avr/io.h>
#include <math.h>
#include <avr/interrupt.h>

#include "config.h"
#include "pindef.h"
#include "macros.h"

#include "ppm.h"

#include "calc.h"
#include "timer.h"
#include "ser.h"

static volatile int32_t ppm_width[8];
static volatile int32_t ppm_offset[8];
static volatile uint8_t ppm_chan;
static volatile uint8_t ppm_highest_chan;
static volatile uint16_t ppm_last_capt;
static volatile uint8_t ppm_ovf_cnt;
static volatile uint8_t ppm_new_data;
static volatile uint8_t ppm_tx_good;
static volatile uint8_t ppm_read_busy;
static volatile uint8_t ppm_has_cal;

ISR(TIMER1_CAPT_vect)
{
	uint8_t ovf_cnt = ppm_ovf_cnt;
	ppm_ovf_cnt = 0;
	uint32_t t_icr = ICR1;

	// calculate total time using overflows and time difference
	int32_t t = ((t_icr | 0x10000) - ppm_last_capt) & 0xFFFF;
	if(t_icr < ppm_last_capt)
	{
	        ovf_cnt--;
	}
	t += 0x10000 * ovf_cnt;

	ppm_last_capt = t_icr;

	// check sync pulse
	if(t > ticks_500us * 6)
	{
		ppm_highest_chan = ppm_chan;
		ppm_chan = 0;
		if(ppm_tx_good == 0)
		{
			ppm_tx_good = 1;
		}
	}
	else // if pulse is shorter than 3ms, then it's a servo pulse
	{
		if(ppm_chan != ppm_read_busy - 1)
		{
			ppm_width[ppm_chan] = t; // store time
		}
		ppm_chan++; // next channel
		if(ppm_chan >= 4 && ppm_tx_good != 0) // last channel, data is now good, reset to first pin
		{
			ppm_tx_good = 2;
			if(ppm_chan == ppm_highest_chan)
			{
				ppm_new_data = 1;
			}
		}
	}
}

ISR(TIMER1_OVF_vect)
{
	ppm_ovf_cnt++;
	if(ppm_ovf_cnt > 10)
	{
		ppm_ovf_cnt = 10;
		ppm_tx_good = 0;
	}
}

void ppm_init()
{
	for(uint8_t i = 0; i < 8; i++)
	{
		ppm_width[i] = ticks_500us * 3;
		ppm_offset[i] = ticks_500us * 3;
	}

	ppm_tx_good = 0;
	ppm_new_data = 0;
	ppm_chan = 0;
	ppm_ovf_cnt = 0;
	ppm_last_capt = 0;
	ppm_highest_chan = ppm_highest_chan_default;
	ppm_has_cal = 0;

	cbi(ppm_port, ppm_pin);
	cbi(ppm_ddr, ppm_pin);

	timer1_init();

	TCCR1B |= _BV(ICNC1) | _BV(ICES1);
	TIMSK1 |= _BV(ICIE1) | _BV(TOIE1);
}

// if new ppm cycle
volatile inline uint8_t ppm_is_new_data(uint8_t c)
{
	ppm_new_data &= c;
	return ppm_new_data;
}

// returns whether or not the TX is on
volatile inline uint8_t ppm_tx_is_good(uint8_t c)
{
	ppm_tx_good &= c;
	return ppm_tx_good;
}

// report how many channels the TX is outputting
volatile inline uint8_t ppm_highest_chan_read()
{
	return ppm_highest_chan;
}

// read channel value in timer ticks
volatile inline int32_t ppm_chan_read(uint8_t i)
{
	if (ppm_tx_good == 0)
	{
		return 0;
	}

	ppm_read_busy = i + 1;
	int16_t r = ppm_width[i] - ppm_offset[i];
	ppm_read_busy = 0;
	return r < ppm_threshold && r > -1 * ppm_threshold ? 0 : r;
}

volatile inline int32_t ppm_chan_read_raw(uint8_t i)
{
	return ppm_width[i];
}

volatile inline uint32_t ppm_center(uint8_t i)
{
	return ppm_offset[i];
}

// take the average center values of each channel to determin the value for stick center
void ppm_calibrate(uint8_t t)
{
	// reset data
	for(uint8_t i = 0; i < 8; i++)
	{
		ppm_offset[i] = 0;
	}
	
	uint64_t sum[8] = {0,0,0,0,0,0,0,0};
	for(uint8_t i = 0; i < t; i++)
	{
		// sum and average for each channel using t samples
		ppm_new_data = 0;
		while(ppm_new_data == 0);
		for(uint8_t j = 0; j < 8; j++)
		{
			sum[j] += ppm_chan_read(j);
		}
	}
	
	// perform averaging
	for(uint8_t j = 0; j < 8; j++)
	{
		ppm_offset[j] = lround((double)sum[j] / (double)t);
	}
	
	// set flag
	ppm_has_cal = 1;
}