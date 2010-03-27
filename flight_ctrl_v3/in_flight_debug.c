#include <stdio.h>
#include <avr/pgmspace.h>

#include "config.h"
#include "pindef.h"
#include "macros.h"

#include "ser.h"
#include "calibration.h"

static FILE serstream = FDEV_SETUP_STREAM(ser_tx_1, NULL, _FDEV_SETUP_WRITE);

void debug_initialize()
{
	ser1_init(129, 128, 128); // 9600 baud
}

uint8_t debug_check_msg(Calibration * x)
{
	uint8_t rc = 0;
	uint8_t d = ser_rx(1, &rc);
	
	if (d == 0 || (d != '@' && d != 's' && d != 'd' && d != 'l' && d != 'c' && d != 'r' && d != 'R')) // nothing received or not sync-ed
	{
		return 0;
	}
	
	if (d == 's')
	{
		calibration_save(x);
		return 0;
	}
	else if (d == 'd')
	{
		calibration_default(x);
		return 0;
	}
	else if (d == 'l')
	{
		calibration_load(x);
		return 0;
	}
	else if (d == 'c')
	{
		debug_report_vars(x);
		return 0 ;
	}
	else if (d == 'r')
	{
		return 1;
	}
	else if (d == 'R')
	{
		return 3;
	}
	
	uint8_t * str = calloc(sizeof(uint8_t), 32);
	int stage = 0;
	int32_t addr = 0;
	
	for (uint8_t i = 0; ; i++)
	{
		rc = 0;
		do
		{
			d = ser_rx(1, &rc);
		}
		while (rc == 0);
		
		if (d >= '0' || d <= '9')
		{
			str[i] = d;
		}
		else
		{
			str[i] = 0;
			uint32_t res = strtol(str, 0, 10);
			if (stage == 0)
			{
				stage = 1;
				addr = res;
				i = 0;
			}
			else if (stage == 1)
			{
				calibration_write(x, addr, res);
				i = 0;
				stage = 2;
				break;
			}
		}
	}
	
	free(str);
	
	return 0;
}

#include "debug_autogen_functs.h"