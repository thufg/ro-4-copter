#include <avr/eeprom.h>

#include "calibration.h"

#include "config.h"

void eeprom_write_byte_if_different(uint32_t addr, uint8_t data)
{
	if (eeprom_read_byte(addr) != data)
	{
		eeprom_write_byte(addr, data);
	}
}

void calibration_save(Calibration * x)
{
	uint8_t * c = x;
	
	for (uint32_t addr = 0; addr < sizeof(Calibration); addr++)
	{
		eeprom_write_byte_if_different(addr, c[addr]);
	}
}

void calibration_load(Calibration * x)
{
	uint8_t * c = x;
	
	for (uint32_t addr = 0; addr < sizeof(Calibration); addr++)
	{
		c[addr] = eeprom_read_byte(addr);
	}
}

#include "calibration_autogen_functs.h"