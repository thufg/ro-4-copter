#include <avr/eeprom.h>

#include "config.h"

#include "calibration.h"

void eeprom_write_byte_if_different(uint32_t addr, uint8_t data)
{
	if (eeprom_read_byte(addr) != data)
	{
		eeprom_write_byte(addr, data);
	}
}

void calibration_save(Calibration * x)
{
	eeprom_write_byte_if_different(0, 'B');
	eeprom_write_byte_if_different(1, 'O');
	eeprom_write_byte_if_different(2, 'O');
	eeprom_write_byte_if_different(3, 'B');
	eeprom_write_byte_if_different(4, 'I');
	eeprom_write_byte_if_different(5, 'E');
	eeprom_write_byte_if_different(6, 'S');
	
	uint8_t * c = x;
	
	for (uint32_t addr = 0; addr < sizeof(Calibration); addr++)
	{
		eeprom_write_byte_if_different(addr + 7, c[addr]);
	}
}

uint8_t calibration_load(Calibration * x)
{
	if (eeprom_read_byte(0) == 'B' && 
		eeprom_read_byte(1) == 'O' && 
		eeprom_read_byte(2) == 'O' && 
		eeprom_read_byte(3) == 'B' && 
		eeprom_read_byte(4) == 'I' && 
		eeprom_read_byte(5) == 'E' && 
		eeprom_read_byte(6) == 'S')
	{	
		uint8_t * c = x;
		
		for (uint32_t addr = 0; addr < sizeof(Calibration); addr++)
		{
			c[addr] = eeprom_read_byte(addr + 7);
		}
		
		return 1;
	}
	else
	{
		calibration_default(x);
		calibration_save(x);
		
		return 0;
	}
}

#include "calibration_autogen_functs.h"