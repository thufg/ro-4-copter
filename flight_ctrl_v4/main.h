// main.h created for project Flight_CTRL_v3 on 01/14/2010 02:58:32

#ifndef main_h
#define main_h

#include <stdint.h>

void user_io_init();
void hold_esc();
void init();
void loop();
int main();
void check_ppm_calibration();
void check_sensor_calibration();

#endif