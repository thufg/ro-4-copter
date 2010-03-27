#ifndef in_flight_debug_h
#define in_flight_debug_h

#include <stdint.h>

void debug_initialize();
uint8_t debug_check_msg(Calibration *);
void debug_report_vars(Calibration *);

#endif