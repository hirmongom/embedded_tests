PROJECT_ROOT := ../..
DRIVERS_DIR := $(PROJECT_ROOT)/drivers/include
STARTUP_DIR := $(PROJECT_ROOT)/startup

CC = arm-none-eabi-gcc
MCPU = cortex-m4
CFLAGS = -c -I$(DRIVERS_DIR) -mcpu=$(MCPU) -mthumb -mfloat-abi=soft -std=gnu11 -Wall -Wextra -pedantic -O0

LD = arm-none-eabi-ld
LS = $(PROJECT_ROOT)/tools/linker_script.ld
LDFLAGS = -T $(LS) -Map=build/final.map

SOURCES := $(wildcard src/*.c)
OBJECTS := $(patsubst src/%.c, build/obj/%.o, $(SOURCES))


OBJDUMP = arm-none-eabi-objdump
ODFLAGS = -t build/final.elf > build/map/final.map

all: build/final.elf

build/obj/%.o: src/%.c | build/obj
	$(CC) $(CFLAGS) -o $@ $<

build/obj/startup.o : $(STARTUP_DIR)/startup.c | build/obj
	$(CC) $(CFLAGS) -o $@ $<

build/final.elf : $(OBJECTS) build/obj/startup.o | build
	$(LD) $(LDFLAGS) -o $@ $^

build:
	mkdir -p $@

build/obj:
	mkdir -p $@

ocd:
	openocd -f board/st_nucleo_f4.cfg
 
clean:
	rm -rf build