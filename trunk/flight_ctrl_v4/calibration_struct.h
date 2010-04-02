#ifndef calibration_struct_h
#define calibration_struct_h

// Var count: 37

typedef struct Calibration_{
	int32_t f_mot_bot;
	int32_t b_mot_bot;
	int32_t l_mot_bot;
	int32_t r_mot_bot;
	int32_t f_mot_scale;
	int32_t b_mot_scale;
	int32_t l_mot_scale;
	int32_t r_mot_scale;
	int32_t roll_gyro_center;
	int32_t pitch_gyro_center;
	int32_t yaw_gyro_center;
	int32_t roll_ppm_center;
	int32_t pitch_ppm_center;
	int32_t yaw_ppm_center;
	int32_t throttle_ppm_center;
	int32_t roll_gyro_scale;
	int32_t pitch_gyro_scale;
	int32_t yaw_gyro_scale;
	int32_t throttle_ppm_scale;
	int32_t throttle_hover;
	int32_t roll_rate_kp;
	int32_t roll_rate_ki;
	int32_t roll_rate_kd;
	int32_t pitch_rate_kp;
	int32_t pitch_rate_ki;
	int32_t pitch_rate_kd;
	int32_t yaw_kp;
	int32_t yaw_ki;
	int32_t yaw_kd;
	uint8_t yaw_ppm_chan;
	uint8_t throttle_ppm_chan;
	uint8_t pitch_ppm_chan;
	uint8_t roll_ppm_chan;
	uint8_t unlock_ppm_chan;
	uint8_t gyro_miscalibrate_threshold;
	int32_t filter_w;
	uint32_t button_hold_down;
} Calibration;

#endif