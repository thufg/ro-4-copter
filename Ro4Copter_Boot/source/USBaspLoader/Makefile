# Modified for Ro4Copter by Frank26080115 on 20110412

# 16k bootloader addr = 0x3800
# 8k bootloader addr = 0x1800
# 32k bootloader addr for 4k bootloader = 0x7000
# 32k bootloader addr for 2k bootloader = 0x7800
# 64k bootloader addr for 4k bootloader = 0xF000
# 64k bootloader addr for 2k bootloader = 0xF800
# atmega644p fuses
# -U lfuse:w:0xFF:m -U hfuse:w:0x98:m -U lock:w:0xFF:m

F_CPU = 16000000
DEVICE = atmega644p
BOOTLOADER_ADDRESS = 0xF000

CC = avr-gcc

# Options:
DEFINES = #-DDEBUG_LEVEL=2
CFLAGS = -Wall -Os -I. -mmcu=$(DEVICE) -DF_CPU=$(F_CPU) $(DEFINES)
LDFLAGS = -Wl,--section-start=.text=$(BOOTLOADER_ADDRESS)

OBJECTS =  usbdrv/usbdrvasm.o main.o #usbdrv/oddebug.o

# symbolic targets:
all: main.hex

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

.S.o:
	$(CC) $(CFLAGS) -x assembler-with-cpp -c $< -o $@

.c.s:
	$(CC) $(CFLAGS) -S $< -o $@

clean:
	rm -f main.hex main.bin *.o usbdrv/*.o main.s usbdrv/oddebug.s usbdrv/usbdrv.s

main.bin:	$(OBJECTS)
	$(CC) $(CFLAGS) -o main.bin $(OBJECTS) $(LDFLAGS)

main.hex:	main.bin
	rm -f main.hex main.eep.hex ../../Ro4Copter_Boot_usbasp.hex
	avr-objcopy -j .text -j .data -O ihex main.bin main.hex
	avr-objcopy -j .text -j .data -O ihex main.bin ../../Ro4Copter_Boot_usbasp.hex
	avr-size main.hex

disasm:	main.bin
	avr-objdump -d main.bin

cpp:
	$(CC) $(CFLAGS) -E main.c

