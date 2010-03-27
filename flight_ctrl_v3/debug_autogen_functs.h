#ifndef debug_autogen_functs_h
#define debug_autogen_functs_h
void debug_report_vars(Calibration * x)
{
	fprintf_P(&serstream, PSTR("0, signed long (%d), f_mot_bot: %d\r\n"), (unsigned char)sizeof(signed long), x->f_mot_bot);
	fprintf_P(&serstream, PSTR("1, signed long (%d), b_mot_bot: %d\r\n"), (unsigned char)sizeof(signed long), x->b_mot_bot);
	fprintf_P(&serstream, PSTR("2, signed long (%d), l_mot_bot: %d\r\n"), (unsigned char)sizeof(signed long), x->l_mot_bot);
	fprintf_P(&serstream, PSTR("3, signed long (%d), r_mot_bot: %d\r\n"), (unsigned char)sizeof(signed long), x->r_mot_bot);
	fprintf_P(&serstream, PSTR("4, signed long (%d), f_mot_scale: %d\r\n"), (unsigned char)sizeof(signed long), x->f_mot_scale);
	fprintf_P(&serstream, PSTR("5, signed long (%d), b_mot_scale: %d\r\n"), (unsigned char)sizeof(signed long), x->b_mot_scale);
	fprintf_P(&serstream, PSTR("6, signed long (%d), l_mot_scale: %d\r\n"), (unsigned char)sizeof(signed long), x->l_mot_scale);
	fprintf_P(&serstream, PSTR("7, signed long (%d), r_mot_scale: %d\r\n"), (unsigned char)sizeof(signed long), x->r_mot_scale);
	fprintf_P(&serstream, PSTR("8, unsigned char (%d), motor_mode: %d\r\n"), (unsigned char)sizeof(unsigned char), x->motor_mode);
	fprintf_P(&serstream, PSTR("9, signed long (%d), yaw_gyro_scale: %d\r\n"), (unsigned char)sizeof(signed long), x->yaw_gyro_scale);
	fprintf_P(&serstream, PSTR("10, signed long (%d), roll_accel_bot: %d\r\n"), (unsigned char)sizeof(signed long), x->roll_accel_bot);
	fprintf_P(&serstream, PSTR("11, signed long (%d), roll_accel_top: %d\r\n"), (unsigned char)sizeof(signed long), x->roll_accel_top);
	fprintf_P(&serstream, PSTR("12, signed long (%d), pitch_accel_bot: %d\r\n"), (unsigned char)sizeof(signed long), x->pitch_accel_bot);
	fprintf_P(&serstream, PSTR("13, signed long (%d), pitch_accel_top: %d\r\n"), (unsigned char)sizeof(signed long), x->pitch_accel_top);
	fprintf_P(&serstream, PSTR("14, signed long (%d), vert_accel_bot: %d\r\n"), (unsigned char)sizeof(signed long), x->vert_accel_bot);
	fprintf_P(&serstream, PSTR("15, signed long (%d), vert_accel_top: %d\r\n"), (unsigned char)sizeof(signed long), x->vert_accel_top);
	fprintf_P(&serstream, PSTR("16, signed long (%d), pitch_angle_offset: %d\r\n"), (unsigned char)sizeof(signed long), x->pitch_angle_offset);
	fprintf_P(&serstream, PSTR("17, signed long (%d), roll_angle_offset: %d\r\n"), (unsigned char)sizeof(signed long), x->roll_angle_offset);
	fprintf_P(&serstream, PSTR("18, signed long (%d), pitch_gyro_to_rate: %d\r\n"), (unsigned char)sizeof(signed long), x->pitch_gyro_to_rate);
	fprintf_P(&serstream, PSTR("19, signed long (%d), roll_gyro_to_rate: %d\r\n"), (unsigned char)sizeof(signed long), x->roll_gyro_to_rate);
	fprintf_P(&serstream, PSTR("20, signed long (%d), roll_ppm_center: %d\r\n"), (unsigned char)sizeof(signed long), x->roll_ppm_center);
	fprintf_P(&serstream, PSTR("21, signed long (%d), pitch_ppm_center: %d\r\n"), (unsigned char)sizeof(signed long), x->pitch_ppm_center);
	fprintf_P(&serstream, PSTR("22, signed long (%d), yaw_ppm_center: %d\r\n"), (unsigned char)sizeof(signed long), x->yaw_ppm_center);
	fprintf_P(&serstream, PSTR("23, signed long (%d), throttle_ppm_center: %d\r\n"), (unsigned char)sizeof(signed long), x->throttle_ppm_center);
	fprintf_P(&serstream, PSTR("24, signed long (%d), roll_ppm_scale: %d\r\n"), (unsigned char)sizeof(signed long), x->roll_ppm_scale);
	fprintf_P(&serstream, PSTR("25, signed long (%d), pitch_ppm_scale: %d\r\n"), (unsigned char)sizeof(signed long), x->pitch_ppm_scale);
	fprintf_P(&serstream, PSTR("26, signed long (%d), yaw_ppm_scale: %d\r\n"), (unsigned char)sizeof(signed long), x->yaw_ppm_scale);
	fprintf_P(&serstream, PSTR("27, signed long (%d), throttle_ppm_scale: %d\r\n"), (unsigned char)sizeof(signed long), x->throttle_ppm_scale);
	fprintf_P(&serstream, PSTR("28, signed long (%d), throttle_hover: %d\r\n"), (unsigned char)sizeof(signed long), x->throttle_hover);
	fprintf_P(&serstream, PSTR("29, signed long (%d), roll_level_kp: %d\r\n"), (unsigned char)sizeof(signed long), x->roll_level_kp);
	fprintf_P(&serstream, PSTR("30, signed long (%d), roll_level_ki: %d\r\n"), (unsigned char)sizeof(signed long), x->roll_level_ki);
	fprintf_P(&serstream, PSTR("31, signed long (%d), roll_level_kd: %d\r\n"), (unsigned char)sizeof(signed long), x->roll_level_kd);
	fprintf_P(&serstream, PSTR("32, signed long (%d), pitch_level_kp: %d\r\n"), (unsigned char)sizeof(signed long), x->pitch_level_kp);
	fprintf_P(&serstream, PSTR("33, signed long (%d), pitch_level_ki: %d\r\n"), (unsigned char)sizeof(signed long), x->pitch_level_ki);
	fprintf_P(&serstream, PSTR("34, signed long (%d), pitch_level_kd: %d\r\n"), (unsigned char)sizeof(signed long), x->pitch_level_kd);
	fprintf_P(&serstream, PSTR("35, signed long (%d), roll_rate_kp: %d\r\n"), (unsigned char)sizeof(signed long), x->roll_rate_kp);
	fprintf_P(&serstream, PSTR("36, signed long (%d), roll_rate_ki: %d\r\n"), (unsigned char)sizeof(signed long), x->roll_rate_ki);
	fprintf_P(&serstream, PSTR("37, signed long (%d), roll_rate_kd: %d\r\n"), (unsigned char)sizeof(signed long), x->roll_rate_kd);
	fprintf_P(&serstream, PSTR("38, signed long (%d), pitch_rate_kp: %d\r\n"), (unsigned char)sizeof(signed long), x->pitch_rate_kp);
	fprintf_P(&serstream, PSTR("39, signed long (%d), pitch_rate_ki: %d\r\n"), (unsigned char)sizeof(signed long), x->pitch_rate_ki);
	fprintf_P(&serstream, PSTR("40, signed long (%d), pitch_rate_kd: %d\r\n"), (unsigned char)sizeof(signed long), x->pitch_rate_kd);
	fprintf_P(&serstream, PSTR("41, signed long (%d), yaw_kp: %d\r\n"), (unsigned char)sizeof(signed long), x->yaw_kp);
	fprintf_P(&serstream, PSTR("42, signed long (%d), yaw_ki: %d\r\n"), (unsigned char)sizeof(signed long), x->yaw_ki);
	fprintf_P(&serstream, PSTR("43, signed long (%d), yaw_kd: %d\r\n"), (unsigned char)sizeof(signed long), x->yaw_kd);
	fprintf_P(&serstream, PSTR("44, unsigned char (%d), yaw_ppm_chan: %d\r\n"), (unsigned char)sizeof(unsigned char), x->yaw_ppm_chan);
	fprintf_P(&serstream, PSTR("45, unsigned char (%d), throttle_ppm_chan: %d\r\n"), (unsigned char)sizeof(unsigned char), x->throttle_ppm_chan);
	fprintf_P(&serstream, PSTR("46, unsigned char (%d), pitch_ppm_chan: %d\r\n"), (unsigned char)sizeof(unsigned char), x->pitch_ppm_chan);
	fprintf_P(&serstream, PSTR("47, unsigned char (%d), roll_ppm_chan: %d\r\n"), (unsigned char)sizeof(unsigned char), x->roll_ppm_chan);
	fprintf_P(&serstream, PSTR("48, unsigned char (%d), unlock_ppm_chan: %d\r\n"), (unsigned char)sizeof(unsigned char), x->unlock_ppm_chan);
	fprintf_P(&serstream, PSTR("49, signed long (%d), delta_time_const: %d\r\n"), (unsigned char)sizeof(signed long), x->delta_time_const);
	fprintf_P(&serstream, PSTR("50, signed long (%d), comp_filter_w: %d\r\n"), (unsigned char)sizeof(signed long), x->comp_filter_w);
	fprintf_P(&serstream, PSTR("51, unsigned long (%d), button_hold_down: %d\r\n"), (unsigned char)sizeof(unsigned long), x->button_hold_down);
}

#endif
