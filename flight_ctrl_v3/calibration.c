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

#include "calibration_autogen_functs.h"