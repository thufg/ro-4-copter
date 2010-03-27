// main.c created for project Flight_CTRL_v3 on 01/14/2010 02:53:50

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#include "main.h"

#include "pindef.h"
#include "macros.h"
#include "config.h"

#include "ser.h"
#include "test.h"
#include "calibration.h"
#include "calc.h"
#include "ppm.h"
#include "in_flight_debug.h"

FUSES = 
{
	.low = 0xFF,
	.high = (FUSE_SPIEN & FUSE_EESAVE),
	.extended = EFUSE_DEFAULT, // 0xFF
};

static Calibration cal_data;

static FILE serdebugstream = FDEV_SETUP_STREAM(ser_tx_1, NULL, _FDEV_SETUP_WRITE);

void user_io_init()
{
	// LEDs as output
	sbi(LED_port, LED1_pin);
	sbi(LED_port, LED2_pin);
	sbi(LED_ddr, LED1_pin);
	sbi(LED_ddr, LED2_pin);
	
	// button to input with pull-ups
	sbi(button_port, button_pin);
	cbi(button_ddr, button_pin);
	
	// switches to input with pull-ups
	sbi(switch_port, switch_1_pin);
	sbi(switch_port, switch_2_pin);
	sbi(switch_port, switch_3_pin);
	sbi(switch_port, switch_4_pin);
	cbi(switch_ddr, switch_1_pin);
	cbi(switch_ddr, switch_2_pin);
	cbi(switch_ddr, switch_3_pin);
	cbi(switch_ddr, switch_4_pin);
}

void hold_esc()
{
	esc_safe(1);
	
	int flashcnt = 0;
	int presscnt = 0;
	
	for (unsigned char i = 0; i < 6; i++)
	{
		esc_set_width(i, ticks_500us * 2);
	}
	
	ppm_is_new_data(0);
	while (ppm_is_new_data(0xFF) == 0);
	
	while (1)
	{
		debug_check_msg(&cal_data);
		
		if (flashcnt < 12)
		{
			LED2_on();
			LED1_on();
		}
		else
		{
			LED2_off();
			LED1_off();
		}
			
		if (ppm_tx_is_good(0xFF))
		{
			if (ppm_is_new_data(0xFF) != 0)
			{
				if (ppm_chan_read(cal_data.unlock_ppm_chan) + ppm_center(cal_data.unlock_ppm_chan) > ticks_500us * 3 + ticks_500us / 2 || button_is_pressed()) // channel 6 button is pressed
				{
					presscnt++;
				}
				else
				{
					presscnt = 0;
				}
			
				ppm_is_new_data(0);
			}
			
			if (presscnt >= cal_data.button_hold_down) // if held down long enough
			{
				break;
			}
		}
		else
		{
			LED1_on();
			presscnt = 0;
		}
			
		if (esc_is_done())
		{
			flashcnt = (flashcnt + 1) % 25;
			esc_start_next();
		}
	}
}

int main()
{
	// test code goes here
	
	//test_user_io();
	//test_esc();
	//test_calibration_eeprom();
	//test_ser(0);
	//test_ser(1);
	test_sensors();
	//test_ppm();
	//test_ppm_to_esc();
	
	return 0;
	
	// actual initialization here
	
	user_io_init();
	
	calibration_default(&cal_data);
	
	sei();
	
	// module initialization
	
	debug_initialize();
	
	sens_init();
	ppm_init();
	esc_init();
	timer0_init();
	
	ppm_calibrate(10);
	
	fprintf_P(&serdebugstream, PSTR("waiting for unlock signal\r\n"));
	
	hold_esc();
	
	fprintf_P(&serdebugstream, PSTR("unlocked\r\n"));
	
	ppm_is_new_data(0);
	while (ppm_is_new_data(0xFF) == 0);
	
	sens_calibrate(10);
	
	// variable initialization
	
	PID_data roll_level_pid = PID_init();
	PID_data pitch_level_pid = PID_init();
	PID_data roll_rate_pid = PID_init();
	PID_data pitch_rate_pid = PID_init();
	PID_data yaw_pid = PID_init();
	
	signed long zero_G_val;
	signed long one_G_val;

	signed long roll_ang = 0; 
	signed long pitch_ang = 0;
	
	unsigned char report_requested = 0;
	unsigned char is_flying = 1;
	unsigned char off_cnt = 0;
	
	LED1_off();
	
	while (1)
	{
		// check for computer interface commands, set flag if debug info requested
		if (debug_check_msg(&cal_data) != 0)
		{
			report_requested = 1;
		}

		signed long roll_gyro_val;
		signed long pitch_gyro_val;
		signed long prev_roll_gyro_val;
		signed long prev_pitch_gyro_val;

		// new samples!
		if (adc_rounds_cnt(0xFF) != 0)
		{
			LED2_tog();
			
			// calculate center accelerometer values
			zero_G_val = (cal_data.vert_accel_top + cal_data.vert_accel_bot + 1) / 2;
			one_G_val = sens_offset(vert_accel_chan) - zero_G_val;
			
			signed long roll_accel_val = ((signed long)sens_read(roll_accel_chan) - ((cal_data.roll_accel_bot + cal_data.roll_accel_top + 1) / 2));
			signed long pitch_accel_val = ((signed long)sens_read(pitch_accel_chan) - ((cal_data.pitch_accel_bot + cal_data.pitch_accel_top + 1) / 2));
			signed long vert_accel_val = ((signed long)sens_read(vert_accel_chan) - ((cal_data.vert_accel_bot + cal_data.vert_accel_top + 1) / 2));
			
			// read gyros
			roll_gyro_val = (signed long)sens_read(roll_gyro_chan) - (signed long)sens_offset(roll_gyro_chan);
			pitch_gyro_val = (signed long)sens_read(pitch_gyro_chan) - (signed long)sens_offset(pitch_gyro_chan);

			// calculate time taken to take samples
			signed long delta_time;
			if (cal_data.delta_time_const != 0)
			{
				delta_time = cal_data.delta_time_const * adc_rounds_cnt(0xFF);
			}
			else
			{
				delta_time = timer0_elapsed();
			}
			
			// calculate angle using trig
			signed long roll_trig;
			signed long pitch_trig;

			#ifdef use_atan
			roll_trig = calc_atan2(roll_accel_val, vert_accel_val);
			pitch_trig = calc_atan2(pitch_accel_val, vert_accel_val);
			#endif

			#ifdef use_asin
			roll_trig = calc_asin(roll_accel_val, one_G_val);
			pitch_trig = calc_asin(pitch_accel_val, one_G_val);
			#endif

			// apply physical offset to angle readings
			roll_trig += cal_data.roll_angle_offset;
			pitch_trig += cal_data.pitch_angle_offset;

			roll_trig = calc_ang_range(roll_trig);
			pitch_trig = calc_ang_range(pitch_trig);

			// mix accel and gyro readings using complementary filter
			roll_ang = complementary_filter(&roll_ang, roll_trig, calc_multi(((roll_gyro_val + prev_roll_gyro_val + 1) / 2), cal_data.roll_gyro_to_rate, MATH_MULTIPLIER), cal_data.comp_filter_w, delta_time);
			pitch_ang = complementary_filter(&pitch_ang, pitch_trig, calc_multi(((pitch_gyro_val + prev_pitch_gyro_val + 1) / 2), cal_data.pitch_gyro_to_rate, MATH_MULTIPLIER), cal_data.comp_filter_w, delta_time);

			roll_ang = calc_ang_range(roll_ang);
			pitch_ang = calc_ang_range(pitch_ang);
			
			prev_pitch_gyro_val = pitch_gyro_val;
			prev_roll_gyro_val = roll_gyro_val;
			
			// computer requested debug data
			if (report_requested == 1)
			{
				fprintf_P(&serdebugstream, PSTR("z_G_val: %d, one_G_val: %d\r\n"), zero_G_val, one_G_val);
				fprintf_P(&serdebugstream, PSTR("roll_accel_val: %d, pitch_accel_val: %d, vert_accel_val: %d\r\n"), roll_accel_val, pitch_accel_val, vert_accel_val);
				fprintf_P(&serdebugstream, PSTR("roll_gyro_val: %d - %d, pitch_gyro_val: %d - %d\r\n"), roll_gyro_val, sens_offset(roll_gyro_chan), pitch_gyro_val, sens_offset(pitch_gyro_chan));
				fprintf_P(&serdebugstream, PSTR("delta_time: %d\r\n"), delta_time);
				fprintf_P(&serdebugstream, PSTR("roll_trig: %d, pitch_trig: %d\r\n"), roll_trig, pitch_trig);
				fprintf_P(&serdebugstream, PSTR("roll_ang: %d, pitch_ang: %d\r\n"), roll_ang, pitch_ang);
				report_requested = 2;
			}
			
			adc_rounds_cnt(0);
		}

		// new ESC period
		if (esc_is_done())
		{
			// level PID calculations for roll and pitch

			signed long roll_tgt_rate = PID_mv(&roll_level_pid, cal_data.roll_level_kp, cal_data.roll_level_ki, cal_data.roll_level_kd, calc_multi(roll_ang, cal_data.roll_ppm_scale, MATH_MULTIPLIER), (signed long)ppm_chan_read((unsigned char)cal_data.roll_ppm_chan));
			signed long pitch_tgt_rate = PID_mv(&pitch_level_pid, cal_data.pitch_level_kp, cal_data.pitch_level_ki, cal_data.pitch_level_kd, calc_multi(pitch_ang, cal_data.pitch_ppm_scale, MATH_MULTIPLIER), (signed long)ppm_chan_read((unsigned char)cal_data.pitch_ppm_chan));

			// angular rate PID calculations for roll and pitch
			
			signed long roll_mot = PID_mv(&roll_rate_pid, cal_data.roll_rate_kp, cal_data.roll_rate_ki, cal_data.roll_rate_kd, roll_tgt_rate, roll_gyro_val);
			signed long pitch_mot = PID_mv(&pitch_rate_pid, cal_data.pitch_rate_kp, cal_data.pitch_rate_ki, cal_data.pitch_rate_kd, pitch_tgt_rate, pitch_gyro_val);

			// attempt to adjust yaw
			signed long yaw_gyro_val = (signed long)sens_read(yaw_gyro_chan) - (signed long)sens_offset(yaw_gyro_chan);
			signed long yaw_mot = PID_mv(&yaw_pid, cal_data.yaw_kp, cal_data.yaw_ki, cal_data.yaw_kd, calc_multi(yaw_gyro_val, cal_data.yaw_ppm_scale, MATH_MULTIPLIER), ppm_chan_read(cal_data.yaw_ppm_chan));

			// calculate throttle
			signed long throttle_cmd = calc_multi((signed long)ppm_chan_read(cal_data.throttle_ppm_chan) + ppm_center(cal_data.throttle_ppm_chan) - ticks_500us * 3, cal_data.throttle_ppm_scale, MATH_MULTIPLIER);
			throttle_cmd += cal_data.throttle_hover;

			// apply final throttle to all motors
			signed long f_mot = cal_data.f_mot_bot + calc_multi((signed long)(throttle_cmd + yaw_mot + pitch_mot), cal_data.f_mot_scale, MATH_MULTIPLIER);
			signed long b_mot = cal_data.b_mot_bot + calc_multi((signed long)(throttle_cmd + yaw_mot - pitch_mot), cal_data.b_mot_scale, MATH_MULTIPLIER);
			signed long l_mot = cal_data.l_mot_bot + calc_multi((signed long)(throttle_cmd - yaw_mot + roll_mot), cal_data.l_mot_scale, MATH_MULTIPLIER);
			signed long r_mot = cal_data.r_mot_bot + calc_multi((signed long)(throttle_cmd - yaw_mot - roll_mot), cal_data.r_mot_scale, MATH_MULTIPLIER);

			esc_set_speed(f_mot_chan, f_mot);
			esc_set_speed(b_mot_chan, b_mot);
			esc_set_speed(l_mot_chan, l_mot);
			esc_set_speed(r_mot_chan, r_mot);
			
			// computer requested debug data
			if (report_requested == 2)
			{
				fprintf_P(&serdebugstream, PSTR("roll_ppm: %d - %d\r\n"), ppm_chan_read(cal_data.roll_ppm_chan), ppm_center(cal_data.roll_ppm_chan));
				fprintf_P(&serdebugstream, PSTR("pitch_ppm: %d - %d\r\n"), ppm_chan_read(cal_data.pitch_ppm_chan), ppm_center(cal_data.pitch_ppm_chan));
				fprintf_P(&serdebugstream, PSTR("yaw_ppm: %d - %d\r\n"), ppm_chan_read(cal_data.yaw_ppm_chan), ppm_center(cal_data.yaw_ppm_chan));
				fprintf_P(&serdebugstream, PSTR("throttle_ppm: %d - %d\r\n"), ppm_chan_read(cal_data.throttle_ppm_chan), ppm_center(cal_data.throttle_ppm_chan));
				
				fprintf_P(&serdebugstream, PSTR("roll_level_pid err: %d, %d\r\n"), roll_level_pid.err_sum, roll_level_pid.err_last);
				fprintf_P(&serdebugstream, PSTR("roll_rate_pid err: %d, %d\r\n"), roll_rate_pid.err_sum, roll_rate_pid.err_last);
				fprintf_P(&serdebugstream, PSTR("roll_tgt_rate: %d\r\n"), roll_tgt_rate);
				fprintf_P(&serdebugstream, PSTR("roll_mot: %d\r\n"), roll_mot);
				
				fprintf_P(&serdebugstream, PSTR("pitch_level_pid err: %d, %d\r\n"), pitch_level_pid.err_sum, pitch_level_pid.err_last);
				fprintf_P(&serdebugstream, PSTR("pitch_rate_pid err: %d, %d\r\n"), pitch_rate_pid.err_sum, pitch_rate_pid.err_last);
				fprintf_P(&serdebugstream, PSTR("pitch_tgt_rate: %d\r\n"), pitch_tgt_rate);
				fprintf_P(&serdebugstream, PSTR("pitch_mot: %d\r\n"), pitch_mot);
				
				fprintf_P(&serdebugstream, PSTR("yaw_pid err: %d, %d\r\n"), yaw_pid.err_sum, yaw_pid.err_last);
				fprintf_P(&serdebugstream, PSTR("yaw_gyro_val: %d - %d\r\n"), yaw_gyro_val, sens_offset(yaw_gyro_chan));
				fprintf_P(&serdebugstream, PSTR("yaw_mot: %d\r\n"), yaw_mot);
				
				fprintf_P(&serdebugstream, PSTR("throttle_cmd: %d\r\n"), throttle_cmd);
				
				fprintf_P(&serdebugstream, PSTR("motor speed: f-%d, b-%d, l-%d, r-%d\r\n"), f_mot, b_mot, l_mot, r_mot);
				
				report_requested = 0;
			}
			
			esc_start_next();
		}
	}
	
	return 0;
}