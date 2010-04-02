###############################################################################
# Makefile for the project Flight_CTRL_v3
###############################################################################

## General Flags
PROJECT = Flight_CTRL_v3
MCU = atmega644p
TARGET = Flight_CTRL_v3.elf
CC = avr-gcc

CPP = avr-g++

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99 -DF_CPU=20000000UL -O3 -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums -ffunction-sections -fdata-sections
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=Flight_CTRL_v3.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Objects that must be built in order to link
OBJECTS = main.o test.o esc.o timer.o sensor.o calc.o calibration.o ser.o ppm.o in_flight_debug.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) Flight_CTRL_v3.hex Flight_CTRL_v3.eep Flight_CTRL_v3.lss size

## Compile
main.o: ../main.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

test.o: ../test.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

esc.o: ../esc.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

timer.o: ../timer.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

sensor.o: ../sensor.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

calc.o: ../calc.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

calibration.o: ../calibration.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

ser.o: ../ser.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

ppm.o: ../ppm.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

in_flight_debug.o: ../in_flight_debug.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) Flight_CTRL_v3.elf dep/* Flight_CTRL_v3.hex Flight_CTRL_v3.eep Flight_CTRL_v3.lss Flight_CTRL_v3.map


## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

