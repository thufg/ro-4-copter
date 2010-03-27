#ifndef in_flight_debug_h
#define in_flight_debug_h

void debug_initialize();
unsigned char debug_check_msg(Calibration *);
void debug_report_vars(Calibration *);

#endif