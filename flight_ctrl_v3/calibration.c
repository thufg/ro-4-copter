#include <avr/eeprom.h>

#include "calibration.h"

#include "config.h"

void eeprom_write_byte_if_different(unsigned long addr, unsigned char data)
{
	if (eeprom_read_byte(addr) != data)
	{
		eeprom_write_byte(addr, data);
	}
}

void calibration_save(Calibration * x)
{
	unsigned char * c = x;
	
	for (unsigned long addr = 0; addr < sizeof(Calibration); addr++)
	{
		eeprom_write_byte_if_different(addr, c[addr]);
	}
}

void calibration_load(Calibration * x)
{
	unsigned char * c = x;
	
	for (unsigned long addr = 0; addr < sizeof(Calibration); addr++)
	{
		c[addr] = eeprom_read_byte(addr);
	}
}

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
	x->roll_level_kd = 0;
	x->pitch_rate_kp = MATH_MULTI;
	x->pitch_rate_ki = 0;
	x->pitch_rate_kd = 0;
	x->yaw_kp = MATH_MULTI;
	x->yaw_ki = 0;
	x->yaw_kd = 0;
	x->comp_filter_w = MATH_MULTI / 2;
}