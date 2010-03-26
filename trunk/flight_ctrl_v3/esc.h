#ifndef esc_h
#define esc_h

void esc_init();
void esc_start_next();
unsigned char esc_is_done();
void esc_is_done_clear();
void esc_safe(unsigned char);
void esc_set_speed(unsigned char, unsigned short);
void esc_set_speed_with_mode(unsigned char, unsigned short, unsigned char);
void esc_set_width(unsigned char, unsigned short);
unsigned long esc_get_total();
void esc_set_extra_chan(unsigned char);

#endif