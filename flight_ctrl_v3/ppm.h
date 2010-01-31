#ifndef ppm_h
#define ppm_h

void ppm_init();
unsigned char ppm_is_new_data(unsigned char);
signed short ppm_chan_read(unsigned char);
unsigned short ppm_center(unsigned char);
void ppm_calibrate(unsigned char);
unsigned char ppm_highest_chan_read();
unsigned char ppm_tx_is_good(unsigned char);

#endif