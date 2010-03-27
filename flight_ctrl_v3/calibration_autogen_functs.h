#ifndef calibration_autogen_functs_h
#define calibration_autogen_functs_h
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
	x->unlock_ppm_chan = 5;
	x->delta_time_const = MATH_MULTI;
	x->comp_filter_w = MATH_MULTI / 2;
	x->button_hold_down = 500;
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
			x->unlock_ppm_chan = (unsigned char)data;
			break;
		case 49:
			x->delta_time_const = (signed long)data;
			break;
		case 50:
			x->comp_filter_w = (signed long)data;
			break;
		case 51:
			x->button_hold_down = (unsigned long)data;
			break;
		default:
			break;
	}
}

#endif
