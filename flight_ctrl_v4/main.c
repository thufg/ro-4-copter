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
	
	// kill switch
	sbi(kill_switch_port, kill_switch_in_pin);
	cbi(kill_switch_ddr, kill_switch_in_pin);
	cbi(kill_switch_port, kill_switch_gnd1_pin);
	sbi(kill_switch_ddr, kill_switch_gnd1_pin);
	cbi(kill_switch_port, kill_switch_gnd2_pin);
	sbi(kill_switch_ddr, kill_switch_gnd2_pin);
}

uint8_t kill_switch_activated()
{
	if (switch_3_is_down() == 0)
	{
		return bit_is_set(kill_switch_in, kill_switch_in_pin);
	}
	else
	{
		return 0;
	}
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

void freeze()
{
	LED1_on();
	LED2_off();
	
	for (uint8_t i = 0; i < 6; i++)
	{
		esc_set_width(i, ticks_500us * 2);
	}
	
	while(1)
	{
		debug_check_msg(&cal_data);
		
		if (esc_is_done())
		{
			esc_start_next();
		}
	}
}

void check_ppm_calibration()
{
	for(uint8_t i = 0; i < 6; i++)
	{
		int32_t w = ppm_chan_read_raw(i);
		if (w < ticks_500us * 3 - ticks_500us / 5 || w > ticks_500us * 3 + ticks_500us / 5)
		{
			LED2_off();
			
			while(1)
			{
				LED1_on();
				_delay_ms(1000);
				LED1_off();
				_delay_ms(500);
			}
		}
	}
}

void check_sensor_calibration()
{	
	if ((sens_offset(yaw_gyro_chan) > cal_data.yaw_gyro_center + cal_data.gyro_miscalibrate_threshold) ||
		(sens_offset(yaw_gyro_chan) < cal_data.yaw_gyro_center - cal_data.gyro_miscalibrate_threshold) ||
		(sens_offset(roll_gyro_chan) > cal_data.roll_gyro_center + cal_data.gyro_miscalibrate_threshold) ||
		(sens_offset(roll_gyro_chan) < cal_data.roll_gyro_center - cal_data.gyro_miscalibrate_threshold) ||
		(sens_offset(pitch_gyro_chan) > cal_data.pitch_gyro_center + cal_data.gyro_miscalibrate_threshold) ||
		(sens_offset(pitch_gyro_chan) < cal_data.pitch_gyro_center - cal_data.gyro_miscalibrate_threshold)
	)
	{
		while(1)
		{
			LED2_off();
			
			while(1)
			{
				LED1_on();
				_delay_ms(1000);
				LED1_off();
				_delay_ms(500);
			}
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
	
	if (switch_2_is_down())
	{
		calibration_load(&cal_data);
	}
	
	sei();
	
	// module initialization
	
	debug_initialize();
	
	sens_init();
	ppm_init();
	esc_init();
	timer0_init();
	
	LED1_on();
	LED2_on();
	
	ppm_tx_is_good(0);
	while (ppm_tx_is_good(0xFF) == 0);
	_delay_ms(1000);
	
	ppm_calibrate(50);
	
	// freeze if miscalibrated
	check_ppm_calibration();
	
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
	
	sens_calibrate(40);
	
	check_sensor_calibration();
	
	// variable initialization

	volatile PID_data roll_rate_pid = PID_init();
	volatile PID_data pitch_rate_pid = PID_init();
	volatile PID_data yaw_pid = PID_init();
	
	volatile static uint32_t roll_gyro_val = 0;
	volatile static uint32_t yaw_gyro_val = 0;
	volatile static uint32_t pitch_gyro_val = 0;
	
	volatile static uint8_t off_cnt = 0; // used to keep the time duration the "off" button is held down
	
	LED1_off();
	
	while (1)
	{
		// check for computer interface commands, set flag if debug info requested
		volatile uint8_t report_requested = debug_check_msg(&cal_data);
		
		// requested raw sensor readings
		if (report_requested == 3)
		{
			for (int i = 0; i < 3; i++)
			{
				fprintf_P(&serdebugstream, PSTR("sensor "), i);
				ser_num(1, i);
				fprintf_P(&serdebugstream, PSTR(": "), sens_read(i));
				ser_num(1, sens_read(i));
				fprintf_P(&serdebugstream, PSTR(" - "));
				ser_num(1, sens_offset(i));
				fprintf_P(&serdebugstream, PSTR("\r\n"));
			}
			
			for (int i = 0; i < 6; i++)
			{
				fprintf_P(&serdebugstream, PSTR("ppm "), i);
				ser_num(1, i);
				fprintf_P(&serdebugstream, PSTR(": "), sens_read(i));
				ser_num(1, ppm_chan_read(i));
				fprintf_P(&serdebugstream, PSTR(" + "));
				ser_num(1, ppm_center(i));
				fprintf_P(&serdebugstream, PSTR("\r\n"));
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
					freeze();
				}
			}
			LED1_off();
		}
		else
		{
			LED1_on();
		}
		
		if (kill_switch_activated())
		{
			freeze();
		}
		
		// new samples!
		if (adc_rounds_cnt(0xFF) != 0)
		{
			roll_gyro_val =  calc_filter(roll_gyro_val,  sens_read(roll_gyro_chan) -  sens_offset(roll_gyro_chan),  cal_data.filter_w);
			pitch_gyro_val = calc_filter(pitch_gyro_val, sens_read(pitch_gyro_chan) - sens_offset(pitch_gyro_chan), cal_data.filter_w);
			yaw_gyro_val =   calc_filter(yaw_gyro_val,   sens_read(yaw_gyro_chan) -   sens_offset(yaw_gyro_chan),   cal_data.filter_w);
			
			adc_rounds_cnt(0);
		}

		// new ESC period
		if (esc_is_done())
		{
			// angular rate PID calculations for roll and pitch
			
			volatile int32_t roll_mot  = PID_mv(&roll_rate_pid,  cal_data.roll_rate_kp,  cal_data.roll_rate_ki,  cal_data.roll_rate_kd,  ppm_chan_read(cal_data.roll_ppm_chan),  roll_gyro_val *  cal_data.roll_gyro_scale);
			volatile int32_t pitch_mot = PID_mv(&pitch_rate_pid, cal_data.pitch_rate_kp, cal_data.pitch_rate_ki, cal_data.pitch_rate_kd, ppm_chan_read(cal_data.pitch_ppm_chan), pitch_gyro_val * cal_data.pitch_gyro_scale);
			
			// attempt to adjust yaw
			volatile int32_t yaw_gyro_val = sens_read(yaw_gyro_chan) - sens_offset(yaw_gyro_chan);
			volatile int32_t yaw_mot = PID_mv(&yaw_pid, cal_data.yaw_kp, cal_data.yaw_ki, cal_data.yaw_kd, yaw_gyro_val * cal_data.yaw_gyro_scale, ppm_chan_read(cal_data.yaw_ppm_chan));

			// calculate throttle
			volatile int32_t throttle_cmd = calc_multi_funct((ppm_chan_read_raw(cal_data.throttle_ppm_chan) - (ticks_500us * 3)), cal_data.throttle_ppm_scale, MATH_MULTIPLIER);
			throttle_cmd += cal_data.throttle_hover;

			// apply final throttle to all motors
			volatile int32_t f_mot = cal_data.f_mot_bot + calc_multi_funct((throttle_cmd + yaw_mot - pitch_mot), cal_data.f_mot_scale, MATH_MULTIPLIER);
			volatile int32_t b_mot = cal_data.b_mot_bot + calc_multi_funct((throttle_cmd + yaw_mot + pitch_mot), cal_data.b_mot_scale, MATH_MULTIPLIER);
			volatile int32_t l_mot = cal_data.l_mot_bot + calc_multi_funct((throttle_cmd - yaw_mot - roll_mot),  cal_data.l_mot_scale, MATH_MULTIPLIER);
			volatile int32_t r_mot = cal_data.r_mot_bot + calc_multi_funct((throttle_cmd - yaw_mot + roll_mot),  cal_data.r_mot_scale, MATH_MULTIPLIER);

			esc_set_width(f_mot_chan, f_mot);
			esc_set_width(b_mot_chan, b_mot);
			esc_set_width(l_mot_chan, l_mot);
			esc_set_width(r_mot_chan, r_mot);
			
			// computer requested debug data
			if (report_requested == 2)
			{
				fprintf_P(&serdebugstream, PSTR("roll_ppm: "));
				ser_num(1, ppm_chan_read(cal_data.roll_ppm_chan));
				fprintf_P(&serdebugstream, PSTR(" + "));
				ser_num(1, ppm_center(cal_data.roll_ppm_chan));
				fprintf_P(&serdebugstream, PSTR("\r\n"));
				
				fprintf_P(&serdebugstream, PSTR("pitch_ppm: "));
				ser_num(1, ppm_chan_read(cal_data.pitch_ppm_chan));
				fprintf_P(&serdebugstream, PSTR(" + "));
				ser_num(1, ppm_center(cal_data.pitch_ppm_chan));
				fprintf_P(&serdebugstream, PSTR("\r\n"));
				
				fprintf_P(&serdebugstream, PSTR("yaw_ppm: "));
				ser_num(1, ppm_chan_read(cal_data.yaw_ppm_chan));
				fprintf_P(&serdebugstream, PSTR(" + "));
				ser_num(1, ppm_center(cal_data.yaw_ppm_chan));
				fprintf_P(&serdebugstream, PSTR("\r\n"));
				
				fprintf_P(&serdebugstream, PSTR("throttle_ppm: "));
				ser_num(1, ppm_chan_read(cal_data.throttle_ppm_chan));
				fprintf_P(&serdebugstream, PSTR(" + "));
				ser_num(1, ppm_center(cal_data.throttle_ppm_chan));
				fprintf_P(&serdebugstream, PSTR("\r\n"));
				
				fprintf_P(&serdebugstream, PSTR("roll_mot: "));
				ser_num(1, roll_mot);
				fprintf_P(&serdebugstream, PSTR("\r\n"));
				
				fprintf_P(&serdebugstream, PSTR("pitch_mot: "));
				ser_num(1, pitch_mot);
				fprintf_P(&serdebugstream, PSTR("\r\n"));
				
				fprintf_P(&serdebugstream, PSTR("yaw_gyro_val: "));
				ser_num(1, yaw_gyro_val);
				fprintf_P(&serdebugstream, PSTR(" + "));
				ser_num(1, sens_offset(yaw_gyro_chan));
				fprintf_P(&serdebugstream, PSTR("\r\n"));
				
				fprintf_P(&serdebugstream, PSTR("yaw_mot: "));
				ser_num(1, yaw_mot);
				fprintf_P(&serdebugstream, PSTR("\r\n"));
				
				fprintf_P(&serdebugstream, PSTR("throttle_cmd: "));
				ser_num(1, throttle_cmd);
				fprintf_P(&serdebugstream, PSTR("\r\n"));
				
				fprintf_P(&serdebugstream, PSTR("motor speed: f= "));
				ser_num(1, f_mot);
				fprintf_P(&serdebugstream, PSTR(", b= "));
				ser_num(1, b_mot);
				fprintf_P(&serdebugstream, PSTR(", l= "));
				ser_num(1, l_mot);
				fprintf_P(&serdebugstream, PSTR(", r= "));
				ser_num(1, r_mot);
				fprintf_P(&serdebugstream, PSTR("\r\n"));
				
				report_requested = 0;
			}
			
			esc_start_next();
		}
	}
	
	return 0;
}