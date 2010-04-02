#ifndef default_values_h
#define default_values_h

#include "config.h"

#define default_mot_bot ticks_500us * 0.3
#define default_mot_scale MATH_MULTI * 1.0

#define default_throttle_hover ticks_500us * 2.5

#define default_rate_kp MATH_MULTI * 0.025
#define default_rate_ki MATH_MULTI * 0
#define default_rate_kd MATH_MULTI * 0

#define default_yaw_kp MATH_MULTI * 0.6
#define default_yaw_ki MATH_MULTI * 0
#define default_yaw_kd MATH_MULTI * 0

#define default_roll_pitch_ppm_scale 7 // 9

#define default_roll_pitch_gyro_scale 500
#define default_yaw_gyro_scale 500 // 270
#define default_throttle_ppm_scale MATH_MULTI * 1

#define default_filter_w MATH_MULTI * 0.2

#define default_gyro_miscalibrate_threshold 50

#endif