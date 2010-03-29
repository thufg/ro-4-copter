#ifndef debug_autogen_functs_h
#define debug_autogen_functs_h
void debug_report_vars(Calibration * x)
{
	fprintf_P(&serstream, PSTR("0, int32_t (%d), f_mot_bot: %d\r\n"), (uint8_t)sizeof(int32_t), x->f_mot_bot);
	fprintf_P(&serstream, PSTR("1, int32_t (%d), b_mot_bot: %d\r\n"), (uint8_t)sizeof(int32_t), x->b_mot_bot);
	fprintf_P(&serstream, PSTR("2, int32_t (%d), l_mot_bot: %d\r\n"), (uint8_t)sizeof(int32_t), x->l_mot_bot);
	fprintf_P(&serstream, PSTR("3, int32_t (%d), r_mot_bot: %d\r\n"), (uint8_t)sizeof(int32_t), x->r_mot_bot);
	fprintf_P(&serstream, PSTR("4, int32_t (%d), f_mot_scale: %d\r\n"), (uint8_t)sizeof(int32_t), x->f_mot_scale);
	fprintf_P(&serstream, PSTR("5, int32_t (%d), b_mot_scale: %d\r\n"), (uint8_t)sizeof(int32_t), x->b_mot_scale);
	fprintf_P(&serstream, PSTR("6, int32_t (%d), l_mot_scale: %d\r\n"), (uint8_t)sizeof(int32_t), x->l_mot_scale);
	fprintf_P(&serstream, PSTR("7, int32_t (%d), r_mot_scale: %d\r\n"), (uint8_t)sizeof(int32_t), x->r_mot_scale);
	fprintf_P(&serstream, PSTR("8, uint8_t (%d), motor_mode: %d\r\n"), (uint8_t)sizeof(uint8_t), x->motor_mode);
	fprintf_P(&serstream, PSTR("9, int32_t (%d), yaw_gyro_scale: %d\r\n"), (uint8_t)sizeof(int32_t), x->yaw_gyro_scale);
	fprintf_P(&serstream, PSTR("10, int32_t (%d), roll_accel_bot: %d\r\n"), (uint8_t)sizeof(int32_t), x->roll_accel_bot);
	fprintf_P(&serstream, PSTR("11, int32_t (%d), roll_accel_center: %d\r\n"), (uint8_t)sizeof(int32_t), x->roll_accel_center);
	fprintf_P(&serstream, PSTR("12, int32_t (%d), roll_accel_top: %d\r\n"), (uint8_t)sizeof(int32_t), x->roll_accel_top);
	fprintf_P(&serstream, PSTR("13, int32_t (%d), pitch_accel_bot: %d\r\n"), (uint8_t)sizeof(int32_t), x->pitch_accel_bot);
	fprintf_P(&serstream, PSTR("14, int32_t (%d), pitch_accel_center: %d\r\n"), (uint8_t)sizeof(int32_t), x->pitch_accel_center);
	fprintf_P(&serstream, PSTR("15, int32_t (%d), pitch_accel_top: %d\r\n"), (uint8_t)sizeof(int32_t), x->pitch_accel_top);
	fprintf_P(&serstream, PSTR("16, int32_t (%d), vert_accel_bot: %d\r\n"), (uint8_t)sizeof(int32_t), x->vert_accel_bot);
	fprintf_P(&serstream, PSTR("17, int32_t (%d), vert_accel_top: %d\r\n"), (uint8_t)sizeof(int32_t), x->vert_accel_top);
	fprintf_P(&serstream, PSTR("18, int32_t (%d), roll_gyro_center: %d\r\n"), (uint8_t)sizeof(int32_t), x->roll_gyro_center);
	fprintf_P(&serstream, PSTR("19, int32_t (%d), pitch_gyro_center: %d\r\n"), (uint8_t)sizeof(int32_t), x->pitch_gyro_center);
	fprintf_P(&serstream, PSTR("20, int32_t (%d), yaw_gyro_center: %d\r\n"), (uint8_t)sizeof(int32_t), x->yaw_gyro_center);
	fprintf_P(&serstream, PSTR("21, int32_t (%d), pitch_angle_offset: %d\r\n"), (uint8_t)sizeof(int32_t), x->pitch_angle_offset);
	fprintf_P(&serstream, PSTR("22, int32_t (%d), roll_angle_offset: %d\r\n"), (uint8_t)sizeof(int32_t), x->roll_angle_offset);
	fprintf_P(&serstream, PSTR("23, int32_t (%d), pitch_gyro_to_rate: %d\r\n"), (uint8_t)sizeof(int32_t), x->pitch_gyro_to_rate);
	fprintf_P(&serstream, PSTR("24, int32_t (%d), roll_gyro_to_rate: %d\r\n"), (uint8_t)sizeof(int32_t), x->roll_gyro_to_rate);
	fprintf_P(&serstream, PSTR("25, int32_t (%d), roll_ppm_center: %d\r\n"), (uint8_t)sizeof(int32_t), x->roll_ppm_center);
	fprintf_P(&serstream, PSTR("26, int32_t (%d), pitch_ppm_center: %d\r\n"), (uint8_t)sizeof(int32_t), x->pitch_ppm_center);
	fprintf_P(&serstream, PSTR("27, int32_t (%d), yaw_ppm_center: %d\r\n"), (uint8_t)sizeof(int32_t), x->yaw_ppm_center);
	fprintf_P(&serstream, PSTR("28, int32_t (%d), throttle_ppm_center: %d\r\n"), (uint8_t)sizeof(int32_t), x->throttle_ppm_center);
	fprintf_P(&serstream, PSTR("29, int32_t (%d), roll_ppm_scale: %d\r\n"), (uint8_t)sizeof(int32_t), x->roll_ppm_scale);
	fprintf_P(&serstream, PSTR("30, int32_t (%d), pitch_ppm_scale: %d\r\n"), (uint8_t)sizeof(int32_t), x->pitch_ppm_scale);
	fprintf_P(&serstream, PSTR("31, int32_t (%d), yaw_ppm_scale: %d\r\n"), (uint8_t)sizeof(int32_t), x->yaw_ppm_scale);
	fprintf_P(&serstream, PSTR("32, int32_t (%d), throttle_ppm_scale: %d\r\n"), (uint8_t)sizeof(int32_t), x->throttle_ppm_scale);
	fprintf_P(&serstream, PSTR("33, int32_t (%d), throttle_hover: %d\r\n"), (uint8_t)sizeof(int32_t), x->throttle_hover);
	fprintf_P(&serstream, PSTR("34, int32_t (%d), roll_level_kp: %d\r\n"), (uint8_t)sizeof(int32_t), x->roll_level_kp);
	fprintf_P(&serstream, PSTR("35, int32_t (%d), roll_level_ki: %d\r\n"), (uint8_t)sizeof(int32_t), x->roll_level_ki);
	fprintf_P(&serstream, PSTR("36, int32_t (%d), roll_level_kd: %d\r\n"), (uint8_t)sizeof(int32_t), x->roll_level_kd);
	fprintf_P(&serstream, PSTR("37, int32_t (%d), pitch_level_kp: %d\r\n"), (uint8_t)sizeof(int32_t), x->pitch_level_kp);
	fprintf_P(&serstream, PSTR("38, int32_t (%d), pitch_level_ki: %d\r\n"), (uint8_t)sizeof(int32_t), x->pitch_level_ki);
	fprintf_P(&serstream, PSTR("39, int32_t (%d), pitch_level_kd: %d\r\n"), (uint8_t)sizeof(int32_t), x->pitch_level_kd);
	fprintf_P(&serstream, PSTR("40, int32_t (%d), roll_rate_kp: %d\r\n"), (uint8_t)sizeof(int32_t), x->roll_rate_kp);
	fprintf_P(&serstream, PSTR("41, int32_t (%d), roll_rate_ki: %d\r\n"), (uint8_t)sizeof(int32_t), x->roll_rate_ki);
	fprintf_P(&serstream, PSTR("42, int32_t (%d), roll_rate_kd: %d\r\n"), (uint8_t)sizeof(int32_t), x->roll_rate_kd);
	fprintf_P(&serstream, PSTR("43, int32_t (%d), pitch_rate_kp: %d\r\n"), (uint8_t)sizeof(int32_t), x->pitch_rate_kp);
	fprintf_P(&serstream, PSTR("44, int32_t (%d), pitch_rate_ki: %d\r\n"), (uint8_t)sizeof(int32_t), x->pitch_rate_ki);
	fprintf_P(&serstream, PSTR("45, int32_t (%d), pitch_rate_kd: %d\r\n"), (uint8_t)sizeof(int32_t), x->pitch_rate_kd);
	fprintf_P(&serstream, PSTR("46, int32_t (%d), yaw_kp: %d\r\n"), (uint8_t)sizeof(int32_t), x->yaw_kp);
	fprintf_P(&serstream, PSTR("47, int32_t (%d), yaw_ki: %d\r\n"), (uint8_t)sizeof(int32_t), x->yaw_ki);
	fprintf_P(&serstream, PSTR("48, int32_t (%d), yaw_kd: %d\r\n"), (uint8_t)sizeof(int32_t), x->yaw_kd);
	fprintf_P(&serstream, PSTR("49, uint8_t (%d), yaw_ppm_chan: %d\r\n"), (uint8_t)sizeof(uint8_t), x->yaw_ppm_chan);
	fprintf_P(&serstream, PSTR("50, uint8_t (%d), throttle_ppm_chan: %d\r\n"), (uint8_t)sizeof(uint8_t), x->throttle_ppm_chan);
	fprintf_P(&serstream, PSTR("51, uint8_t (%d), pitch_ppm_chan: %d\r\n"), (uint8_t)sizeof(uint8_t), x->pitch_ppm_chan);
	fprintf_P(&serstream, PSTR("52, uint8_t (%d), roll_ppm_chan: %d\r\n"), (uint8_t)sizeof(uint8_t), x->roll_ppm_chan);
	fprintf_P(&serstream, PSTR("53, uint8_t (%d), unlock_ppm_chan: %d\r\n"), (uint8_t)sizeof(uint8_t), x->unlock_ppm_chan);
	fprintf_P(&serstream, PSTR("54, int32_t (%d), delta_time_const: %d\r\n"), (uint8_t)sizeof(int32_t), x->delta_time_const);
	fprintf_P(&serstream, PSTR("55, int32_t (%d), comp_filter_w: %d\r\n"), (uint8_t)sizeof(int32_t), x->comp_filter_w);
	fprintf_P(&serstream, PSTR("56, uint32_t (%d), button_hold_down: %d\r\n"), (uint8_t)sizeof(uint32_t), x->button_hold_down);
}

#endif