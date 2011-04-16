# Makefile for ATmegaBOOT
# E.Lins, 18.7.2005
# $Id$

# Modified for Ro4Copter by Frank26080115 on 20110415

# 16k bootloader addr = 0x3800
# 8k bootloader addr = 0x1800
# 32k bootloader addr for 4k bootloader = 0x7000
# 32k bootloader addr for 2k bootloader = 0x7800
# 64k bootloader addr for 4k bootloader = 0xF000
# 64k bootloader addr for 2k bootloader = 0xF800
# atmega644p fuses
# -U lfuse:w:0xFF:m -U hfuse:w:0x98:m -U lock:w:0xFF:m

# program name should not be changed...
PROGRAM    = Ro4Copter_Boot

# enter the target CPU frequency
AVR_FREQ   = 16000000L

MCU_TARGET = atmega644p
LDSECTION  = --section-start=.text=0xF000

OBJ1        = $(PROGRAM)_arduino.o
OBJ2        = $(PROGRAM)_stk500_w_btn.o
OPTIMIZE   = -O2

DEFS       = 
LIBS       = 

CC         = avr-gcc


# Override is only needed by avr-lib build system.

override CFLAGS        = -g -Wall $(OPTIMIZE) -mmcu=$(MCU_TARGET) -DF_CPU=$(AVR_FREQ) $(DEFS)
override LDFLAGS       = -Wl,$(LDSECTION)
#override LDFLAGS       = -Wl,-Map,$(PROGRAM).map,$(LDSECTION)

OBJCOPY        = avr-objcopy
OBJDUMP        = avr-objdump

all: CFLAGS += '-DMAX_TIME_COUNT=8000000L>>1' -DADABOOT
all: $(PROGRAM)_arduino.hex $(PROGRAM)_stk500_w_btn.hex

$(PROGRAM)_arduino.hex: $(PROGRAM)_arduino.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@
	$(OBJCOPY) -j .text -j .data -O ihex $< ../../$@
	
$(PROGRAM)_arduino.elf: $(OBJ1)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)
	
$(OBJ1): $(PROGRAM).c
	avr-gcc $(CFLAGS) $(LDFLAGS) -c -g -O2 -Wall -mmcu=$(MCU_TARGET) $(PROGRAM).c -o $(PROGRAM)_arduino.o
	
$(PROGRAM)_stk500_w_btn.hex: $(PROGRAM)_stk500_w_btn.elf
	$(OBJCOPY) -j .text -j .data -O ihex $< $@
	$(OBJCOPY) -j .text -j .data -O ihex $< ../../$@
	
$(PROGRAM)_stk500_w_btn.elf: $(OBJ2)
	$(CC) $(CFLAGS) -DAQ64_BOOT_BTN $(LDFLAGS) -o $@ $^ $(LIBS)
	
$(OBJ2): $(PROGRAM).c
	avr-gcc $(CFLAGS) -DAQ64_BOOT_BTN $(LDFLAGS) -c -g -O2 -Wall -mmcu=$(MCU_TARGET) $(PROGRAM).c -o $(PROGRAM)_stk500_w_btn.o

%.lst: %.elf
	$(OBJDUMP) -h -S $< > $@

%.srec: %.elf
	$(OBJCOPY) -j .text -j .data -O srec $< $@

%.bin: %.elf
	$(OBJCOPY) -j .text -j .data -O binary $< $@

clean:
	rm -rf *.o *.elf *.lst *.map *.sym *.lss *.eep *.srec *.bin *.hex
	