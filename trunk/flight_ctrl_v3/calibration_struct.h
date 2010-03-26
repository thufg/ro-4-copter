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
	signed long delta_time_const;
	signed long comp_filter_w;
} Calibration;

// Var count: 50

/*
void calibration_default(Calibration * x)
{
	x->f_mot_bot = 0;
	x->b_mot_bot = 0;
	x->l_mot_bot = 0;
	x->r_mot_bot = 0;
	x->f_mot_scale = MATH_MULTI;
	x->b_mot_scale = MATH_MULTI;
	x->l_mot_scale = MATH_MULTI;
	x->r_mot_scale = MATH_MULTI;
	x->motor_mode = 0b00000000;
	x->yaw_gyro_scale = MATH_MULTI;
	x->roll_accel_bot = 0;
	x->roll_accel_top = 1024;
	x->pitch_accel_bot = 0;
	x->pitch_accel_top = 1024;
	x->vert_accel_bot = 0;
	x->vert_accel_top = 1024;
	x->pitch_angle_offset = 0;
	x->roll_angle_offset = 0;
	x->pitch_gyro_to_rate = MATH_MULTI;
	x->roll_gyro_to_rate = MATH_MULTI;
	x->roll_ppm_center = ticks_500us * 3;
	x->pitch_ppm_center = ticks_500us * 3;
	x->yaw_ppm_center = ticks_500us * 3;
	x->throttle_ppm_center = ticks_500us * 3;
	x->roll_ppm_scale = MATH_MULTI;
	x->pitch_ppm_scale = MATH_MULTI;
	x->yaw_ppm_scale = MATH_MULTI;
	x->throttle_ppm_scale = MATH_MULTI;
	x->throttle_hover = ticks_500us * 3;
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
	x->yaw_ppm_chan = 0;
	x->throttle_ppm_chan = 1;
	x->pitch_ppm_chan = 2;
	x->roll_ppm_chan = 3;
	x->delta_time_const = MATH_MULTI;
	x->comp_filter_w = MATH_MULTI / 2;
}


void calibration_write(Calibration * x, signed long addr, signed long data)
{
	switch(addr)
	{
		case 0:
			x->f_mot_bot = (signed long)data;
			break;
		case 1:
			x->b_mot_bot = (signed long)data;
			break;
		case 2:
			x->l_mot_bot = (signed long)data;
			break;
		case 3:
			x->r_mot_bot = (signed long)data;
			break;
		case 4:
			x->f_mot_scale = (signed long)data;
			break;
		case 5:
			x->b_mot_scale = (signed long)data;
			break;
		case 6:
			x->l_mot_scale = (signed long)data;
			break;
		case 7:
			x->r_mot_scale = (signed long)data;
			break;
		case 8:
			x->motor_mode = (unsigned char)data;
			break;
		case 9:
			x->yaw_gyro_scale = (signed long)data;
			break;
		case 10:
			x->roll_accel_bot = (signed long)data;
			break;
		case 11:
			x->roll_accel_top = (signed long)data;
			break;
		case 12:
			x->pitch_accel_bot = (signed long)data;
			break;
		case 13:
			x->pitch_accel_top = (signed long)data;
			break;
		case 14:
			x->vert_accel_bot = (signed long)data;
			break;
		case 15:
			x->vert_accel_top = (signed long)data;
			break;
		case 16:
			x->pitch_angle_offset = (signed long)data;
			break;
		case 17:
			x->roll_angle_offset = (signed long)data;
			break;
		case 18:
			x->pitch_gyro_to_rate = (signed long)data;
			break;
		case 19:
			x->roll_gyro_to_rate = (signed long)data;
			break;
		case 20:
			x->roll_ppm_center = (signed long)data;
			break;
		case 21:
			x->pitch_ppm_center = (signed long)data;
			break;
		case 22:
			x->yaw_ppm_center = (signed long)data;
			break;
		case 23:
			x->throttle_ppm_center = (signed long)data;
			break;
		case 24:
			x->roll_ppm_scale = (signed long)data;
			break;
		case 25:
			x->pitch_ppm_scale = (signed long)data;
			break;
		case 26:
			x->yaw_ppm_scale = (signed long)data;
			break;
		case 27:
			x->throttle_ppm_scale = (signed long)data;
			break;
		case 28:
			x->throttle_hover = (signed long)data;
			break;
		case 29:
			x->roll_level_kp = (signed long)data;
			break;
		case 30:
			x->roll_level_ki = (signed long)data;
			break;
		case 31:
			x->roll_level_kd = (signed long)data;
			break;
		case 32:
			x->pitch_level_kp = (signed long)data;
			break;
		case 33:
			x->pitch_level_ki = (signed long)data;
			break;
		case 34:
			x->pitch_level_kd = (signed long)data;
			break;
		case 35:
			x->roll_rate_kp = (signed long)data;
			break;
		case 36:
			x->roll_rate_ki = (signed long)data;
			break;
		case 37:
			x->roll_rate_kd = (signed long)data;
			break;
		case 38:
			x->pitch_rate_kp = (signed long)data;
			break;
		case 39:
			x->pitch_rate_ki = (signed long)data;
			break;
		case 40:
			x->pitch_rate_kd = (signed long)data;
			break;
		case 41:
			x->yaw_kp = (signed long)data;
			break;
		case 42:
			x->yaw_ki = (signed long)data;
			break;
		case 43:
			x->yaw_kd = (signed long)data;
			break;
		case 44:
			x->yaw_ppm_chan = (unsigned char)data;
			break;
		case 45:
			x->throttle_ppm_chan = (unsigned char)data;
			break;
		case 46:
			x->pitch_ppm_chan = (unsigned char)data;
			break;
		case 47:
			x->roll_ppm_chan = (unsigned char)data;
			break;
		case 48:
			x->delta_time_const = (signed long)data;
			break;
		case 49:
			x->comp_filter_w = (signed long)data;
			break;
		default:
			break;
	}
}


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
	fprintf_P(&serstream, PSTR("48, signed long (%d), delta_time_const: %d\r\n"), (unsigned char)sizeof(signed long), x->delta_time_const);
	fprintf_P(&serstream, PSTR("49, signed long (%d), comp_filter_w: %d\r\n"), (unsigned char)sizeof(signed long), x->comp_filter_w);
}
*/

#endif