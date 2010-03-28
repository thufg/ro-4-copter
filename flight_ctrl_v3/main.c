// main.c created for project Flight_CTRL_v3 on 01/14/2010 02:53:50

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#include "pindef.h"
#include "macros.h"
#include "config.h"

#include "main.h"

#include "ser.h"
#include "test.h"
#include "calibration.h"
#include "calc.h"
#include "ppm.h"
#include "esc.h"
#include "timer.h"
#include "sensor.h"
#include "in_flight_debug.h"

FUSES = 
{
	.low = 0xFF,
	.high = (FUSE_SPIEN & FUSE_EESAVE),
	.extended = EFUSE_DEFAULT, // 0xFF
};

static volatile Calibration cal_data;

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
	esc_safe(0);
	
	int flashcnt = 0;
	int presscnt = 0;
	
	for (uint8_t i = 0; i < 6; i++)
	{
		esc_set_width(i, ticks_500us * 2);
	}
	
	ppm_is_new_data(0);
	while (ppm_is_new_data(0xFF) == 0);
	
	while (1)
	{
		debug_check_msg(&cal_data);
		
		if (flashcnt < 25)
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
				if (ppm_chan_read(cal_data.unlock_ppm_chan) + ppm_center(cal_data.unlock_ppm_chan) < (ticks_500us * 3) - (ticks_500us / 2) || button_is_pressed()) // channel 6 button is pressed
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
			flashcnt = (flashcnt + 1) % 50;
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
	//test_sensors();
	//test_ppm();
	//test_ppm_to_esc();
	
	//return 0;
	
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
	
	ppm_tx_is_good(0);
	while (ppm_tx_is_good(0xFF) == 0);
	_delay_ms(1000);
	
	ppm_calibrate(50);
	
	// if switch is up, then wait for user to unlock, or else just arm the ESCs
	if (switch_1_is_down() == 0)
	{
		hold_esc();
	}
	else
	{
		esc_safe(0);
		
		for (uint8_t i = 0; i < 6; i++)
		{
			esc_set_width(i, ticks_500us * 2);
		}
	
		for (int i = 0; i < 100 * 5; i++)
		{
			if (esc_is_done())
			{
				esc_start_next();
			}
		}
	}
	
	ppm_is_new_data(0);
	while (ppm_is_new_data(0xFF) == 0);
	
	sens_calibrate(20);
	
	// variable initialization
	
	volatile PID_data roll_level_pid = PID_init();
	volatile PID_data pitch_level_pid = PID_init();
	volatile PID_data roll_rate_pid = PID_init();
	volatile PID_data pitch_rate_pid = PID_init();
	volatile PID_data yaw_pid = PID_init();
	
	volatile static int32_t zero_G_val;
	volatile static int32_t one_G_val;

	volatile static int32_t roll_ang = 0; 
	volatile static int32_t pitch_ang = 0;
	
	volatile static uint8_t off_cnt = 0; // used to keep the time duration the "off" button is held down
	
	LED1_off();
	
	while (1)
	{
		// check for computer interface commands, set flag if debug info requested
		volatile uint8_t report_requested = debug_check_msg(&cal_data);
		
		// requested raw sensor readings
		if (report_requested == 3)
		{
			for (int i = 0; i < 8; i++)
			{
				fprintf_P(&serdebugstream, PSTR("sensor %d: "), i);
				fprintf_P(&serdebugstream, PSTR("%d - "), sens_read(i));
				fprintf_P(&serdebugstream, PSTR("%d\r\n"), sens_offset(i));
			}
			
			for (int i = 0; i < 6; i++)
			{
				fprintf_P(&serdebugstream, PSTR("ppm %d: "), i);
				fprintf_P(&serdebugstream, PSTR("%d + "), ppm_chan_read(i));
				fprintf_P(&serdebugstream, PSTR("%d\r\n"), ppm_center(i));
			}
			
			report_requested = 0;
		}
		
		// check if user is trying to switch off the motors
		if (ppm_tx_is_good(0xFF))
		{
			if (ppm_is_new_data(0xFF))
			{
				if (ppm_chan_read(cal_data.unlock_ppm_chan) > (ticks_500us / 2))
				{
					off_cnt++;
				}
				else
				{
					off_cnt = 0;
				}
				
				ppm_is_new_data(0);
				
				if (off_cnt >= cal_data.button_hold_down / 2)
				{
					hold_esc();
					LED1_off();
					off_cnt = 0;
				}
			}
		}
		else
		{
			LED1_on();
		}

		volatile static int32_t roll_gyro_val;
		volatile static int32_t pitch_gyro_val;
		volatile static int32_t prev_roll_gyro_val; // prev val kept for averaging
		volatile static int32_t prev_pitch_gyro_val;

		// new samples!
		if (adc_rounds_cnt(0xFF) != 0)
		{
			LED2_tog();
			
			// calculate center accelerometer values
			zero_G_val = (cal_data.vert_accel_top + cal_data.vert_accel_bot + 1) / 2;
			one_G_val = cal_data.vert_accel_top - zero_G_val;
			
			volatile static int32_t roll_accel_val;
			volatile static int32_t pitch_accel_val;
			volatile static int32_t vert_accel_val;
			
			roll_accel_val  = (sens_read(roll_accel_chan)  - ((cal_data.roll_accel_bot  + cal_data.roll_accel_top  + 1) / 2));
			pitch_accel_val = (sens_read(pitch_accel_chan) - ((cal_data.pitch_accel_bot + cal_data.pitch_accel_top + 1) / 2));
			vert_accel_val  = (sens_read(vert_accel_chan)  - ((cal_data.vert_accel_bot  + cal_data.vert_accel_top  + 1) / 2));
			
			// read gyros
			roll_gyro_val  = sens_read(roll_gyro_chan)  - sens_offset(roll_gyro_chan);
			pitch_gyro_val = sens_read(pitch_gyro_chan) - sens_offset(pitch_gyro_chan);

			// calculate time taken to take samples
			volatile static int32_t delta_time;
			if (cal_data.delta_time_const != 0)
			{
				delta_time = cal_data.delta_time_const * adc_rounds_cnt(0xFF);
			}
			else
			{
				delta_time = timer0_elapsed();
			}
			
			// calculate angle using trig
			volatile static int32_t roll_trig;
			volatile static int32_t pitch_trig;

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

			//roll_trig = calc_ang_range(roll_trig);
			//pitch_trig = calc_ang_range(pitch_trig);
			
			// mix accel and gyro readings using complementary filter
			roll_ang  = complementary_filter(&roll_ang,  roll_trig,  calc_multi(((roll_gyro_val  + prev_roll_gyro_val  + 1) / 2), cal_data.roll_gyro_to_rate,  MATH_MULTIPLIER), cal_data.comp_filter_w, delta_time);
			pitch_ang = complementary_filter(&pitch_ang, pitch_trig, calc_multi(((pitch_gyro_val + prev_pitch_gyro_val + 1) / 2), cal_data.pitch_gyro_to_rate, MATH_MULTIPLIER), cal_data.comp_filter_w, delta_time);

			//roll_ang = calc_ang_range(roll_ang);
			//pitch_ang = calc_ang_range(pitch_ang);
			
			prev_pitch_gyro_val = pitch_gyro_val;
			prev_roll_gyro_val = roll_gyro_val;
			
			// computer requested debug data
			if (report_requested == 1)
			{
				fprintf_P(&serdebugstream, PSTR("zero_G_val: %d, "), zero_G_val);
				fprintf_P(&serdebugstream, PSTR("one_G_val: %d\r\n"), one_G_val);
				
				fprintf_P(&serdebugstream, PSTR("roll_accel_val: %d, "), roll_accel_val);
				fprintf_P(&serdebugstream, PSTR("pitch_accel_val: %d, "), pitch_accel_val);
				fprintf_P(&serdebugstream, PSTR("vert_accel_val: %d\r\n"), vert_accel_val);
				
				fprintf_P(&serdebugstream, PSTR("roll_gyro_val: %d - "), roll_gyro_val);
				fprintf_P(&serdebugstream, PSTR("%d, "), sens_offset(roll_gyro_chan));
				fprintf_P(&serdebugstream, PSTR("pitch_gyro_val: %d - "), pitch_gyro_val);
				fprintf_P(&serdebugstream, PSTR("%d\r\n"), sens_offset(pitch_gyro_chan));
				
				fprintf_P(&serdebugstream, PSTR("delta_time: %d\r\n"), delta_time);
				
				fprintf_P(&serdebugstream, PSTR("roll_trig: %d, "), roll_trig);
				fprintf_P(&serdebugstream, PSTR("pitch_trig: %d\r\n"), pitch_trig);
				
				fprintf_P(&serdebugstream, PSTR("roll_ang: %d, "), roll_ang);
				fprintf_P(&serdebugstream, PSTR("pitch_ang: %d\r\n"), pitch_ang);
				
				report_requested = 2;
			}
			
			adc_rounds_cnt(0);
		}

		// new ESC period
		if (esc_is_done())
		{
			// level PID calculations for roll and pitch

			volatile int32_t roll_tgt_rate = PID_mv(&roll_level_pid, cal_data.roll_level_kp, cal_data.roll_level_ki, cal_data.roll_level_kd, calc_multi(roll_ang, cal_data.roll_ppm_scale, MATH_MULTIPLIER), (int32_t)ppm_chan_read((uint8_t)cal_data.roll_ppm_chan));
			volatile int32_t pitch_tgt_rate = PID_mv(&pitch_level_pid, cal_data.pitch_level_kp, cal_data.pitch_level_ki, cal_data.pitch_level_kd, calc_multi(pitch_ang, cal_data.pitch_ppm_scale, MATH_MULTIPLIER), (int32_t)ppm_chan_read((uint8_t)cal_data.pitch_ppm_chan));

			// angular rate PID calculations for roll and pitch
			
			volatile int32_t roll_mot = PID_mv(&roll_rate_pid, cal_data.roll_rate_kp, cal_data.roll_rate_ki, cal_data.roll_rate_kd, roll_tgt_rate, roll_gyro_val);
			volatile int32_t pitch_mot = PID_mv(&pitch_rate_pid, cal_data.pitch_rate_kp, cal_data.pitch_rate_ki, cal_data.pitch_rate_kd, pitch_tgt_rate, pitch_gyro_val);

			// attempt to adjust yaw
			volatile int32_t yaw_gyro_val = sens_read(yaw_gyro_chan) - sens_offset(yaw_gyro_chan);
			volatile int32_t yaw_mot = PID_mv(&yaw_pid, cal_data.yaw_kp, cal_data.yaw_ki, cal_data.yaw_kd, calc_multi(yaw_gyro_val, cal_data.yaw_ppm_scale, MATH_MULTIPLIER), ppm_chan_read(cal_data.yaw_ppm_chan));

			// calculate throttle
			volatile int32_t throttle_cmd = calc_multi(ppm_chan_read(cal_data.throttle_ppm_chan), cal_data.throttle_ppm_scale, MATH_MULTIPLIER);
			throttle_cmd += cal_data.throttle_hover;

			// apply final throttle to all motors
			volatile int32_t f_mot = cal_data.f_mot_bot + calc_multi((throttle_cmd + yaw_mot + pitch_mot), cal_data.f_mot_scale, MATH_MULTIPLIER);
			volatile int32_t b_mot = cal_data.b_mot_bot + calc_multi((throttle_cmd + yaw_mot - pitch_mot), cal_data.b_mot_scale, MATH_MULTIPLIER);
			volatile int32_t l_mot = cal_data.l_mot_bot + calc_multi((throttle_cmd - yaw_mot + roll_mot), cal_data.l_mot_scale, MATH_MULTIPLIER);
			volatile int32_t r_mot = cal_data.r_mot_bot + calc_multi((throttle_cmd - yaw_mot - roll_mot), cal_data.r_mot_scale, MATH_MULTIPLIER);

			esc_set_width(f_mot_chan, f_mot);
			esc_set_width(b_mot_chan, b_mot);
			esc_set_width(l_mot_chan, l_mot);
			esc_set_width(r_mot_chan, r_mot);
			
			// computer requested debug data
			if (report_requested == 2)
			{
				fprintf_P(&serdebugstream, PSTR("roll_ppm: %d - "), ppm_chan_read(cal_data.roll_ppm_chan));
				fprintf_P(&serdebugstream, PSTR("%d\r\n"), ppm_center(cal_data.roll_ppm_chan));
				
				fprintf_P(&serdebugstream, PSTR("pitch_ppm: %d - "), ppm_chan_read(cal_data.pitch_ppm_chan));
				fprintf_P(&serdebugstream, PSTR("%d\r\n"), ppm_center(cal_data.pitch_ppm_chan));
				
				fprintf_P(&serdebugstream, PSTR("yaw_ppm: %d - "), ppm_chan_read(cal_data.yaw_ppm_chan));
				fprintf_P(&serdebugstream, PSTR("%d\r\n"), ppm_center(cal_data.yaw_ppm_chan));
				
				fprintf_P(&serdebugstream, PSTR("throttle_ppm: %d - "), ppm_chan_read(cal_data.throttle_ppm_chan));
				fprintf_P(&serdebugstream, PSTR("%d\r\n"), ppm_center(cal_data.throttle_ppm_chan));
				
				//fprintf_P(&serdebugstream, PSTR("roll_level_pid err: %d, "), roll_level_pid.err_sum);
				//fprintf_P(&serdebugstream, PSTR("%d\r\n"), roll_level_pid.err_last);
				
				//fprintf_P(&serdebugstream, PSTR("roll_rate_pid err: %d, "), roll_rate_pid.err_sum);
				//fprintf_P(&serdebugstream, PSTR("%d\r\n"), roll_rate_pid.err_last);
				
				fprintf_P(&serdebugstream, PSTR("roll_tgt_rate: %d\r\n"), roll_tgt_rate);
				fprintf_P(&serdebugstream, PSTR("roll_mot: %d\r\n"), roll_mot);
				
				//fprintf_P(&serdebugstream, PSTR("pitch_level_pid err: %d, "), pitch_level_pid.err_sum);
				//fprintf_P(&serdebugstream, PSTR("%d\r\n"), pitch_level_pid.err_last);
				
				//fprintf_P(&serdebugstream, PSTR("pitch_rate_pid err: %d, "), pitch_rate_pid.err_sum);
				//fprintf_P(&serdebugstream, PSTR("%d\r\n"), pitch_rate_pid.err_last);
				
				fprintf_P(&serdebugstream, PSTR("pitch_tgt_rate: %d\r\n"), pitch_tgt_rate);
				fprintf_P(&serdebugstream, PSTR("pitch_mot: %d\r\n"), pitch_mot);
				
				//fprintf_P(&serdebugstream, PSTR("yaw_pid err: %d, "), yaw_pid.err_sum);
				//fprintf_P(&serdebugstream, PSTR("%d\r\n"), yaw_pid.err_last);
				
				fprintf_P(&serdebugstream, PSTR("yaw_gyro_val: %d - "), yaw_gyro_val);
				fprintf_P(&serdebugstream, PSTR("%d\r\n"), sens_offset(yaw_gyro_chan));
				
				fprintf_P(&serdebugstream, PSTR("yaw_mot: %d\r\n"), yaw_mot);
				
				fprintf_P(&serdebugstream, PSTR("throttle_cmd: %d\r\n"), throttle_cmd);
				
				fprintf_P(&serdebugstream, PSTR("motor speed: f= %d, "), f_mot);
				fprintf_P(&serdebugstream, PSTR("b= %d, "), b_mot);
				fprintf_P(&serdebugstream, PSTR("l= %d, "), l_mot);
				fprintf_P(&serdebugstream, PSTR("r= %d\r\n"), r_mot);
				
				report_requested = 0;
			}
			
			esc_start_next();
		}
	}
	
	return 0;
}