#ifndef ppm_h
#define ppm_h

#include <stdint.h>

void ppm_init();
volatile uint8_t ppm_is_new_data(uint8_t);
volatile int16_t ppm_chan_read(uint8_t);
volatile uint16_t ppm_center(uint8_t);
void ppm_calibrate(uint8_t);
volatile uint8_t ppm_highest_chan_read();
volatile uint8_t ppm_tx_is_good(uint8_t);

#endif