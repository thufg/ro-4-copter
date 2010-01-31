#ifndef calibration_struct_h
#define calibration_struct_h

typedef struct Calibration_{
	signed long f_mot_bot;
	signed long b_mot_bot;
	signed long l_mot_bot;
	signed long r_mot_bot;
	signed long f_mot_scale;
	signed long b_mot_scale;
	signed long l_mot_scale;
	signed long r_mot_scale;
	signed long roll_gyro_center;
	signed long pitch_gyro_center;
	signed long yaw_gyro_center;
	signed long yaw_gyro_scale;
	signed long roll_accel_bot;
	signed long roll_accel_top;
	signed long pitch_accel_bot;
	signed long pitch_accel_top;
	signed long roll_ppm_center;
	signed long pitch_ppm_center;
	signed long yaw_ppm_center;
	signed long throttle_ppm_center;
	signed long roll_ppm_scale;
	signed long pitch_ppm_scale;
	signed long yaw_ppm_scale;
	signed long throttle_ppm_scale;
	signed long roll_level_kp;
	signed long roll_level_ki;
	signed long roll_level_kd;
	signed long pitch_level_kp;
	signed long pitch_level_ki;
	signed long pitch_level_kd;
	signed long roll_rate_kp;
	signed long roll_rate_ki;
	signed long roll_rate_kd;
	signed long pitch_rate_kp;
	signed long pitch_rate_ki;
	signed long pitch_rate_kd;
	signed long yaw_kp;
	signed long yaw_ki;
	signed long yaw_kd;
	signed long comp_filter_w;
} Calibration;

// Var count: 40

/*
void calibration_default(Calibration * x)
{
	x->f_mot_bot = ticks_500us * 2;
	x->b_mot_bot = ticks_500us * 2;
	x->l_mot_bot = ticks_500us * 2;
	x->r_mot_bot = ticks_500us * 2;
	x->f_mot_scale = MATH_MULTI;
	x->b_mot_scale = MATH_MULTI;
	x->l_mot_scale = MATH_MULTI;
	x->r_mot_scale = MATH_MULTI;
	x->roll_gyro_center = 512;
	x->pitch_gyro_center = 512;
	x->yaw_gyro_center = 512;
	x->yaw_gyro_scale = MATH_MULTI;
	x->roll_accel_bot = 0;
	x->roll_accel_top = 0;
	x->pitch_accel_bot = 1024;
	x->pitch_accel_top = 1024;
	x->roll_ppm_center = ticks_500us * 3;
	x->pitch_ppm_center = ticks_500us * 3;
	x->yaw_ppm_center = ticks_500us * 3;
	x->throttle_ppm_center = ticks_500us * 3;
	x->roll_ppm_scale = MATH_MULTI;
	x->pitch_ppm_scale = MATH_MULTI;
	x->yaw_ppm_scale = MATH_MULTI;
	x->throttle_ppm_scale = MATH_MULTI;
	x->roll_level_kp = MATH_MULTI;
	x->roll_level_ki = 0;
	x->roll_level_kd = 0;
	x->pitch_level_kp = MATH_MULTI;
	x->pitch_level_ki = 0;
	x->pitch_level_kd = 0;
	x->roll_rate_kp = MATH_MULTI;
	x->roll_rate_ki = 0;
	x->roll_rate_kd = 0;
	x->pitch_rate_kp = MATH_MULTI;
	x->pitch_rate_ki = 0;
	x->pitch_rate_kd = 0;
	x->yaw_kp = MATH_MULTI;
	x->yaw_ki = 0;
	x->yaw_kd = 0;
	x->comp_filter_w = MATH_MULTI / 2;
}
*/

#endif