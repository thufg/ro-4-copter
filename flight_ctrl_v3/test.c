#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include <avr/pgmspace.h>

#include "test.h"

#include "macros.h"
#include "pindef.h"
#include "config.h"

#include "esc.h"
#include "main.h"
#include "calibration.h"
#include "ser.h"
#include "sensor.h"
#include "ppm.h"

FILE ostream_0 = FDEV_SETUP_STREAM(ser_tx_0, NULL, _FDEV_SETUP_WRITE);

#ifdef __AVR_ATmega644P__
FILE ostream_1 = FDEV_SETUP_STREAM(ser_tx_1, NULL, _FDEV_SETUP_WRITE);
#endif

void test_user_io()
{
	// test user buttons, dip switches, and the LEDs
	
	user_io_init();
	
	// perform test forever
	while (1)
	{
		if (button_is_pressed())
		{
			// LEDs on when button is pressed
			LED1_on();
			LED2_on();
		}
		else
		{
			int delay1 = 200;
			int delay2 = 200;
			
			if (switch_1_is_down() && switch_2_is_down())
			{
				delay1 = 400;
			}
			else if (!switch_1_is_down() && switch_2_is_down())
			{
				delay1 = 600;
			}
			else if (switch_1_is_down() && !switch_2_is_down())
			{
				delay1 = 800;
			}
			
			if (switch_3_is_down() && switch_4_is_down())
			{
				delay2 = 300;
			}
			else if (!switch_3_is_down() && switch_4_is_down())
			{
				delay2 = 600;
			}
			else if (switch_3_is_down() && !switch_4_is_down())
			{
				delay2 = 800;
			}
			
			LED1_on();
			LED2_off();
			_delay_ms(delay1);

			LED1_off();
			LED2_on();
			_delay_ms(delay2);
		}
	}
}

/**
 * This test only tests the shift register
 * The ESC will not actually arm
 *
*/
void test_esc()
{
	// initialize stuff
	
	user_io_init();
	
	esc_init();
	
	sei();
	
	while (1)
	{
		// switch 1 is used as safety switch
		if (switch_1_is_down())
			esc_safe(0);
		else
			esc_safe(1);
			
		if(esc_is_done())
		{
			// set test width
			uint16_t testWidth = ticks_500us * 3;
			
			esc_set_width(f_mot_chan, testWidth + testWidth / 2);
			esc_set_width(b_mot_chan, testWidth + testWidth / 4);
			esc_set_width(l_mot_chan, testWidth + testWidth / 8);
			esc_set_width(r_mot_chan, testWidth + testWidth / 16);
			
			esc_start_next();
		}
	}
}

void test_calibration_eeprom()
{
	user_io_init();
	
	LED1_off();
	LED2_off();
	
	Calibration data1;
	Calibration data2;
	
	uint8_t * d1 = &data1;
	uint8_t * d2 = &data2;
	
	calibration_default(&data1);
	
	// make sure data are different
	for (uint32_t i = 0; i < sizeof(Calibration); i++)
	{
		d2[i] = ~d1[i];
	}
	
	calibration_save(&data1);
	calibration_load(&data2);
	
	if (memcmp(d1, d2, sizeof(Calibration)) == 0)
	{
		// data matches
		
		LED2_on();
		LED1_off();
	}
	else
	{
		// data does not match
		
		LED1_on();
		LED2_off();
	}
	
	while (1);
}

void test_ser(uint8_t port)
{
	void (* ser_init)(uint16_t, uint8_t, uint8_t) = ser0_init;
	FILE * ostream = &ostream_0;
	
	#ifdef __AVR_ATmega644P__
	if (port == 1)
	{
		ser_init = ser1_init;
		ostream = &ostream_1;
	}
	#endif
	
	user_io_init();
	
	ser_init(129, 32, 32);
	
	sei();
	
	fprintf_P(ostream, PSTR("\r\ntest_ser\r\n"));
	
	while (1)
	{
		uint8_t r;
		uint8_t d = ser_rx(port, &r);
		if (r != 0)
		{
			ser_tx(port, d);
		}
		else if (button_is_pressed())
		{
			fprintf_P(ostream, PSTR("\r\nbutton\r\n"));
			
			while (button_is_pressed());
		}
	}
}

// report ADC readings to serial port
void test_sensors()
{
	user_io_init();
	
	ser1_init(129, 128, 128);
	
	sens_init();
	
	sei();
	
	sens_calibrate(10);
	
	fprintf_P(&ostream_1, PSTR("\r\ntest_sensors\r\n"));
	
	while (1)
	{
		if (adc_rounds_cnt(0xFF))
		{			
			if (button_is_pressed())
			{
				// report center values
				for (uint8_t i = 0; i < 8; i++)
				{
					fprintf_P(&ostream_1, PSTR("cal %d: %d\r\n"), i, sens_offset(i));
				}
				
				while (button_is_pressed());
			}
			else
			{
				// report ADC channel readings
				for (uint8_t i = 0; i < 8; i++)
				{
					fprintf_P(&ostream_1, PSTR("adc %d: %d\r\n"), i, sens_read(i));
				}
				
				_delay_ms(100);
			}
			
			while (ser_tx_is_busy(1)); // wait for data to be sent
			
			adc_rounds_cnt(0);
		}
	}
}

// report PPM readings to serial port
void test_ppm()
{
	user_io_init();
	
	ser1_init(129, 128, 128);
	
	ppm_init();
	
	sei();
	
	ppm_calibrate(10);
	
	fprintf_P(&ostream_0, PSTR("\r\ntest_ppm\r\n"));
	
	while (1)
	{
		// indicate TX status using LEDs
		if (ppm_tx_is_good(0xFF))
		{
			LED2_on();
			LED1_off();
		}
		else
		{
			LED1_on();
			LED2_off();
		}
		
		if (ppm_is_new_data(0xFF))
		{			
			if (button_is_pressed())
			{
				// report center values
				for (uint8_t i = 0; i < 6; i++)
				{
					fprintf_P(&ostream_0, PSTR("cal %d: %d\r\n"), i, ppm_center(i));
				}
				
				while (button_is_pressed());
			}
			else
			{
				// report channel values
				for (uint8_t i = 0; i < 6; i++)
				{
					fprintf_P(&ostream_0, PSTR("ppm %d: %d\r\n"), i, ppm_chan_read(i));
				}
				
				_delay_ms(100);
			}
			
			while (ser_tx_is_busy(0)); // wait for data to be sent
			
			ppm_is_new_data(0);
		}
	}
}

// simply let the RC TX control each ESC channel
void test_ppm_to_esc()
{
	user_io_init();
	
	LED1_on();
	LED2_off();
	
	esc_init();
	ppm_init();
	
	sei();
	
	ppm_calibrate(10);
	
	hold_esc();
	
	while (1)
	{
		// switch 1 is used as safety switch
		// esc safe when tx is off
		if (ppm_tx_is_good(0xFF))
		{
			LED2_on();
			LED1_off();
			if (switch_1_is_down())
			{
				esc_safe(0);
			}
			else 
			{
				esc_safe(1);
			}
		}
		else
		{
			LED1_on();
			LED2_off();
			esc_safe(1);
		}
			
		if(esc_is_done())
		{			
			for (uint8_t i = 0; i < 6; i++)
			{
				esc_set_width(i, ppm_chan_read(i) + ppm_center(i));
			}
			
			esc_start_next();
		}
	}
}

void test_calc(uint8_t port)
{
	void (* ser_init)(uint16_t, uint8_t, uint8_t) = ser0_init;
	FILE * ostream = &ostream_0;
	
	#ifdef __AVR_ATmega644P__
	if (port == 1)
	{
		ser_init = ser1_init;
		ostream = &ostream_1;
	}
	#endif
	
	user_io_init();
	
	ser0_init(129, 32, 32);
	
	sei();
	
	fprintf_P(ostream, PSTR("\r\ntest_calc\r\n"));
	
	
}