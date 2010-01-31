#ifndef sensor_h
#define sensor_h

/*
typedef struct sens_hist_
{
	unsigned int res[sens_hist_len_max];
	unsigned char cnt;
	unsigned char last_cnt;
	unsigned int latest;
	double avg;
	double offset;
	double noise;
} sens_hist;
//*/

void sens_init();
void sens_calibrate(unsigned char);
void adc_wait_stop();
unsigned char adc_rounds_cnt(unsigned char);
unsigned short sens_read(unsigned char);
unsigned short sens_offset(unsigned char);

#endif