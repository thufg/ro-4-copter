#ifndef sensor_h
#define sensor_h

#include <stdint.h>

/*
typedef struct sens_hist_
{
	uint16_t res[sens_hist_len_max];
	uint8_t cnt;
	uint8_t last_cnt;
	uint16_t latest;
	double avg;
	double offset;
	double noise;
} sens_hist;
//*/

void sens_init();
void sens_calibrate(uint8_t);
void adc_wait_stop();
volatile uint8_t adc_rounds_cnt(uint8_t);
volatile int32_t sens_read(uint8_t);
volatile int32_t sens_offset(uint8_t);

#endif