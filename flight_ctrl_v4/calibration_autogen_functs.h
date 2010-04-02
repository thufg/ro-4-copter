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
	x->roll_gyro_center = 357;
	x->pitch_gyro_center = 370;
	x->yaw_gyro_center = 288;
	x->roll_ppm_center = ticks_500us * 3;
	x->pitch_ppm_center = ticks_500us * 3;
	x->yaw_ppm_center = ticks_500us * 3;
	x->throttle_ppm_center = ticks_500us * 3;
	x->roll_gyro_scale = default_roll_pitch_gyro_scale;
	x->pitch_gyro_scale = default_roll_pitch_gyro_scale;
	x->yaw_gyro_scale = default_yaw_gyro_scale;
	x->throttle_ppm_scale = default_throttle_ppm_scale;
	x->throttle_hover = default_throttle_hover;
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
	x->filter_w = default_filter_w;
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
			x->roll_gyro_center = (int32_t)data;
			break;
		case 9:
			x->pitch_gyro_center = (int32_t)data;
			break;
		case 10:
			x->yaw_gyro_center = (int32_t)data;
			break;
		case 11:
			x->roll_ppm_center = (int32_t)data;
			break;
		case 12:
			x->pitch_ppm_center = (int32_t)data;
			break;
		case 13:
			x->yaw_ppm_center = (int32_t)data;
			break;
		case 14:
			x->throttle_ppm_center = (int32_t)data;
			break;
		case 15:
			x->roll_gyro_scale = (int32_t)data;
			break;
		case 16:
			x->pitch_gyro_scale = (int32_t)data;
			break;
		case 17:
			x->yaw_gyro_scale = (int32_t)data;
			break;
		case 18:
			x->throttle_ppm_scale = (int32_t)data;
			break;
		case 19:
			x->throttle_hover = (int32_t)data;
			break;
		case 20:
			x->roll_rate_kp = (int32_t)data;
			break;
		case 21:
			x->roll_rate_ki = (int32_t)data;
			break;
		case 22:
			x->roll_rate_kd = (int32_t)data;
			break;
		case 23:
			x->pitch_rate_kp = (int32_t)data;
			break;
		case 24:
			x->pitch_rate_ki = (int32_t)data;
			break;
		case 25:
			x->pitch_rate_kd = (int32_t)data;
			break;
		case 26:
			x->yaw_kp = (int32_t)data;
			break;
		case 27:
			x->yaw_ki = (int32_t)data;
			break;
		case 28:
			x->yaw_kd = (int32_t)data;
			break;
		case 29:
			x->yaw_ppm_chan = (uint8_t)data;
			break;
		case 30:
			x->throttle_ppm_chan = (uint8_t)data;
			break;
		case 31:
			x->pitch_ppm_chan = (uint8_t)data;
			break;
		case 32:
			x->roll_ppm_chan = (uint8_t)data;
			break;
		case 33:
			x->unlock_ppm_chan = (uint8_t)data;
			break;
		case 34:
			x->gyro_miscalibrate_threshold = (uint8_t)data;
			break;
		case 35:
			x->filter_w = (int32_t)data;
			break;
		case 36:
			x->button_hold_down = (uint32_t)data;
			break;
		default:
			break;
	}
}

#endif