#ifndef calibration_autogen_functs_h
#define calibration_autogen_functs_h
void calibration_default(Calibration * x)
{
	x->f_mot_bot = default_mot_bot;
	x->b_mot_bot = default_mot_bot;
	x->l_mot_bot = default_mot_bot;
	x->r_mot_bot = default_mot_bot;
	x->f_mot_scale = default_mot_scale;
	x->b_mot_scale = default_mot_scale;
	x->l_mot_scale = default_mot_scale;
	x->r_mot_scale = default_mot_scale;
	x->motor_mode = 0b00000000;
	x->roll_accel_bot = 294;
	x->roll_accel_center = 544;
	x->roll_accel_top = 796;
	x->pitch_accel_bot = 303;
	x->pitch_accel_center = 551;
	x->pitch_accel_top = 812;
	x->vert_accel_bot = 255;
	x->vert_accel_top = 756;
	x->roll_gyro_center = 357;
	x->pitch_gyro_center = 370;
	x->yaw_gyro_center = 288;
	x->pitch_angle_offset = 0;
	x->roll_angle_offset = 0;
	x->pitch_gyro_to_rate = 6;
	x->roll_gyro_to_rate = 6;
	x->roll_ppm_center = ticks_500us * 3;
	x->pitch_ppm_center = ticks_500us * 3;
	x->yaw_ppm_center = ticks_500us * 3;
	x->throttle_ppm_center = ticks_500us * 3;
	x->roll_ppm_scale = default_roll_pitch_ppm_scale;
	x->pitch_ppm_scale = default_roll_pitch_ppm_scale;
	x->roll_gyro_scale = default_roll_pitch_gyro_scale;
	x->pitch_gyro_scale = default_roll_pitch_gyro_scale;
	x->yaw_gyro_scale = default_yaw_gyro_scale;
	x->throttle_ppm_scale = default_throttle_ppm_scale;
	x->throttle_hover = default_throttle_hover;
	x->roll_level_kp = default_level_kp;
	x->roll_level_ki = default_level_ki;
	x->roll_level_kd = default_level_kd;
	x->pitch_level_kp = default_level_kp;
	x->pitch_level_ki = default_level_ki;
	x->pitch_level_kd = default_level_kd;
	x->roll_rate_kp = default_rate_kp;
	x->roll_rate_ki = default_rate_ki;
	x->roll_rate_kd = default_rate_kd;
	x->pitch_rate_kp = default_rate_kp;
	x->pitch_rate_ki = default_rate_ki;
	x->pitch_rate_kd = default_rate_kd;
	x->yaw_kp = default_yaw_kp;
	x->yaw_ki = default_yaw_ki;
	x->yaw_kd = default_yaw_kd;
	x->yaw_ppm_chan = 0;
	x->throttle_ppm_chan = 1;
	x->pitch_ppm_chan = 2;
	x->roll_ppm_chan = 3;
	x->unlock_ppm_chan = 5;
	x->gyro_miscalibrate_threshold = default_gyro_miscalibrate_threshold;
	x->delta_time_const = default_delta_time_const;
	x->trig_multi_const = default_trig_multi_const;
	x->comp_filter_w = default_comp_filter_w;
	x->button_hold_down = 125;
}


void calibration_write(Calibration * x, int32_t addr, int32_t data)
{
	switch(addr)
	{
		case 0:
			x->f_mot_bot = (int32_t)data;
			break;
		case 1:
			x->b_mot_bot = (int32_t)data;
			break;
		case 2:
			x->l_mot_bot = (int32_t)data;
			break;
		case 3:
			x->r_mot_bot = (int32_t)data;
			break;
		case 4:
			x->f_mot_scale = (int32_t)data;
			break;
		case 5:
			x->b_mot_scale = (int32_t)data;
			break;
		case 6:
			x->l_mot_scale = (int32_t)data;
			break;
		case 7:
			x->r_mot_scale = (int32_t)data;
			break;
		case 8:
			x->motor_mode = (uint8_t)data;
			break;
		case 9:
			x->roll_accel_bot = (int32_t)data;
			break;
		case 10:
			x->roll_accel_center = (int32_t)data;
			break;
		case 11:
			x->roll_accel_top = (int32_t)data;
			break;
		case 12:
			x->pitch_accel_bot = (int32_t)data;
			break;
		case 13:
			x->pitch_accel_center = (int32_t)data;
			break;
		case 14:
			x->pitch_accel_top = (int32_t)data;
			break;
		case 15:
			x->vert_accel_bot = (int32_t)data;
			break;
		case 16:
			x->vert_accel_top = (int32_t)data;
			break;
		case 17:
			x->roll_gyro_center = (int32_t)data;
			break;
		case 18:
			x->pitch_gyro_center = (int32_t)data;
			break;
		case 19:
			x->yaw_gyro_center = (int32_t)data;
			break;
		case 20:
			x->pitch_angle_offset = (int32_t)data;
			break;
		case 21:
			x->roll_angle_offset = (int32_t)data;
			break;
		case 22:
			x->pitch_gyro_to_rate = (int32_t)data;
			break;
		case 23:
			x->roll_gyro_to_rate = (int32_t)data;
			break;
		case 24:
			x->roll_ppm_center = (int32_t)data;
			break;
		case 25:
			x->pitch_ppm_center = (int32_t)data;
			break;
		case 26:
			x->yaw_ppm_center = (int32_t)data;
			break;
		case 27:
			x->throttle_ppm_center = (int32_t)data;
			break;
		case 28:
			x->roll_ppm_scale = (int32_t)data;
			break;
		case 29:
			x->pitch_ppm_scale = (int32_t)data;
			break;
		case 30:
			x->roll_gyro_scale = (int32_t)data;
			break;
		case 31:
			x->pitch_gyro_scale = (int32_t)data;
			break;
		case 32:
			x->yaw_gyro_scale = (int32_t)data;
			break;
		case 33:
			x->throttle_ppm_scale = (int32_t)data;
			break;
		case 34:
			x->throttle_hover = (int32_t)data;
			break;
		case 35:
			x->roll_level_kp = (int32_t)data;
			break;
		case 36:
			x->roll_level_ki = (int32_t)data;
			break;
		case 37:
			x->roll_level_kd = (int32_t)data;
			break;
		case 38:
			x->pitch_level_kp = (int32_t)data;
			break;
		case 39:
			x->pitch_level_ki = (int32_t)data;
			break;
		case 40:
			x->pitch_level_kd = (int32_t)data;
			break;
		case 41:
			x->roll_rate_kp = (int32_t)data;
			break;
		case 42:
			x->roll_rate_ki = (int32_t)data;
			break;
		case 43:
			x->roll_rate_kd = (int32_t)data;
			break;
		case 44:
			x->pitch_rate_kp = (int32_t)data;
			break;
		case 45:
			x->pitch_rate_ki = (int32_t)data;
			break;
		case 46:
			x->pitch_rate_kd = (int32_t)data;
			break;
		case 47:
			x->yaw_kp = (int32_t)data;
			break;
		case 48:
			x->yaw_ki = (int32_t)data;
			break;
		case 49:
			x->yaw_kd = (int32_t)data;
			break;
		case 50:
			x->yaw_ppm_chan = (uint8_t)data;
			break;
		case 51:
			x->throttle_ppm_chan = (uint8_t)data;
			break;
		case 52:
			x->pitch_ppm_chan = (uint8_t)data;
			break;
		case 53:
			x->roll_ppm_chan = (uint8_t)data;
			break;
		case 54:
			x->unlock_ppm_chan = (uint8_t)data;
			break;
		case 55:
			x->gyro_miscalibrate_threshold = (uint8_t)data;
			break;
		case 56:
			x->delta_time_const = (int32_t)data;
			break;
		case 57:
			x->trig_multi_const = (int32_t)data;
			break;
		case 58:
			x->comp_filter_w = (int32_t)data;
			break;
		case 59:
			x->button_hold_down = (uint32_t)data;
			break;
		default:
			break;
	}
}

#endif