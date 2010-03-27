#ifndef ppm_h
#define ppm_h

void ppm_init();
volatile unsigned char ppm_is_new_data(unsigned char);
volatile signed short ppm_chan_read(unsigned char);
volatile unsigned short ppm_center(unsigned char);
void ppm_calibrate(unsigned char);
volatile unsigned char ppm_highest_chan_read();
volatile unsigned char ppm_tx_is_good(unsigned char);

#endif