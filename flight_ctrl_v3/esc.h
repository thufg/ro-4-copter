#ifndef esc_h
#define esc_h

#include <stdint.h>

void esc_init();
void esc_start_next();
volatile uint8_t esc_is_done();
void esc_is_done_clear();
void esc_safe(uint8_t);
void esc_set_speed(uint8_t, uint16_t);
void esc_set_speed_with_mode(uint8_t, uint16_t, uint8_t);
void esc_set_width(uint8_t, uint16_t);
volatile uint32_t esc_get_total();
void esc_set_extra_chan(uint8_t);

#endif