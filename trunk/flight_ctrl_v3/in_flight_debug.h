#ifndef in_flight_debug_h
#define in_flight_debug_h

#include <stdint.h>
#include "calibration.h"

void debug_initialize();
volatile uint8_t debug_check_msg(Calibration *);
void debug_report_vars(Calibration *);

#endif