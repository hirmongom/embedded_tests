CC = arm-none-eabi-gcc
MACH = cortex-m4
CFLAGS = -c -Icmsis -Iinc -mcpu=$(MACH) -mthumb -Wall -O0

LD = arm-none-eabi-ld
LS = src/GCC/gcc_arm.ld
LDFLAGS = -T $(LS) -e Reset_Handler

OBJCOPY = arm-none-eabi-objcopy

SOURCES := $(wildcard src/*.c)
OBJECTS := $(patsubst src/%.c, obj/%.o, $(SOURCES))

all : build/final.bin

obj/%.o : src/%.c | obj
	$(CC) $(CFLAGS) -o $@ $<

src/startup_TM4C123.s : obj/startup_TM4C123.o
	$(CC) $(CFLAGS) -o $@ $^

build/final.elf : $(OBJECTS) | build
	$(LD) $(LDFLAGS) -o $@ $^

build/final.bin : build/final.elf | build
	$(OBJCOPY) -O binary $< $@

obj:
	mkdir -p $@

build:
	mkdir -p $@

flash:
	lm4flash build/final.bin

clean:
	rm -rf obj build
