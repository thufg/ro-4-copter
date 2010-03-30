#ifndef default_values_h
#define default_values_h

#include "config.h"

#define default_mot_bot ticks_500us * 0.2
#define default_mot_scale MATH_MULTI * 1.0

#define default_throttle_hover ticks_500us * 2.5

#define default_rate_kp MATH_MULTI * 0.0215
#define default_rate_ki MATH_MULTI * 0
#define default_rate_kd MATH_MULTI * 0

#define default_level_kp MATH_MULTI * 1
#define default_level_ki MATH_MULTI * 0
#define default_level_kd MATH_MULTI * 0

#define default_yaw_kp MATH_MULTI * 0.6
#define default_yaw_ki MATH_MULTI * 0
#define default_yaw_kd MATH_MULTI * 0

#define default_roll_pitch_ppm_scale 9
#define default_roll_pitch_gyro_scale 2432
#define default_yaw_gyro_scale 270 // = ticks_500us / 180 / degree_per_sec_per_adc_unit
#define default_throttle_ppm_scale MATH_MULTI * 0.9

#define default_trig_multi_const 4
#define default_delta_time_const 23 // 23 = 0.001152575 / (1024 / F_CPU)
#define default_comp_filter_w MATH_MULTI * 0.12

#endif