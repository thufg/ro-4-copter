// main.c created for project Flight_CTRL_v3 on 01/14/2010 02:53:50

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "main.h"

#include "pindef.h"
#include "macros.h"

#include "test.h"
#include "calibration.h"

static Calibration data;

void init();
void loop();

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

int main()
{
	// test code goes here
	
	//test_user_io();
	//test_esc();
	//test_calibration_eeprom();
	//test_ser(0);
	//test_sensors();
	//test_ppm();
	test_ppm_to_esc();
	
	init();
	while (1)
	{
		loop();
	}
	return 0;
}

void init()
{
	user_io_init();
	
	calibration_default(&data);
	
	sei();
}

void loop()
{
	
}