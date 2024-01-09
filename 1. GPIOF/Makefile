CC = arm-none-eabi-gcc
MACH = cortex-m4
CFLAGS = -c -Iinc -mcpu=$(MACH) -mthumb -Wall -O0

LD = arm-none-eabi-ld
LS = src/GCC/gcc_arm.ld
LDFLAGS = -T $(LS) -e ResetISR

OBJCOPY = arm-none-eabi-objcopy

all : build/final.bin

obj/main.o : main.c
	$(CC) $(CFLAGS) -o $@ $^

obj/startup_TM4C.o : src/startup_TM4C.c
	$(CC) $(CFLAGS) -o $@ $^

build/final.elf : obj/main.o obj/startup_TM4C.o
	$(LD) $(LDFLAGS) -o $@ $^

build/final.bin : build/final.elf
	$(OBJCOPY) -O binary $< $@

flash:
	sudo lm4flash build/final.bin
	
clean:
	rm -rf obj/*.o buid/*.elf build/*.bin