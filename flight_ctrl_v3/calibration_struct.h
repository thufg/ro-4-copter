#ifndef calibration_struct_h
#define calibration_struct_h

// Var count: 52

typedef struct Calibration_{
	signed long f_mot_bot;
	signed long b_mot_bot;
	signed long l_mot_bot;
	signed long r_mot_bot;
	signed long f_mot_scale;
	signed long b_mot_scale;
	signed long l_mot_scale;
	signed long r_mot_scale;
	unsigned char motor_mode;
	signed long yaw_gyro_scale;
	signed long roll_accel_bot;
	signed long roll_accel_top;
	signed long pitch_accel_bot;
	signed long pitch_accel_top;
	signed long vert_accel_bot;
	signed long vert_accel_top;
	signed long pitch_angle_offset;
	signed long roll_angle_offset;
	signed long pitch_gyro_to_rate;
	signed long roll_gyro_to_rate;
	signed long roll_ppm_center;
	signed long pitch_ppm_center;
	signed long yaw_ppm_center;
	signed long throttle_ppm_center;
	signed long roll_ppm_scale;
	signed long pitch_ppm_scale;
	signed long yaw_ppm_scale;
	signed long throttle_ppm_scale;
	signed long throttle_hover;
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
	unsigned char yaw_ppm_chan;
	unsigned char throttle_ppm_chan;
	unsigned char pitch_ppm_chan;
	unsigned char roll_ppm_chan;
	unsigned char unlock_ppm_chan;
	signed long delta_time_const;
	signed long comp_filter_w;
	unsigned long button_hold_down;
} Calibration;

#endif