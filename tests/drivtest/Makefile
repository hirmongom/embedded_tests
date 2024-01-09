PROJECT_ROOT := ../..
STARTUP_DIR := $(PROJECT_ROOT)/startup
LIBRARY_DIR := $(PROJECT_ROOT)/lib
DRIVER_DIR := $(PROJECT_ROOT)/drivers/include

CC = arm-none-eabi-gcc
MCPU = cortex-m4
CFLAGS = -c -Iinclude -I$(DRIVER_DIR) -mcpu=$(MCPU) -mthumb -mfloat-abi=soft -std=gnu11 -Wall -Wextra -pedantic -O0

LD = arm-none-eabi-ld
LS = $(PROJECT_ROOT)/tools/linker_script.ld
LDFLAGS = -T $(LS) -Map=build/final.map

SOURCES := $(wildcard src/*.c)
OBJECTS := $(patsubst src/%.c, build/obj/%.o, $(SOURCES))

OBJDUMP = arm-none-eabi-objdump
ODFLAGS = -t build/final.elf > build/map/final.map

.PHONY: all
all: build/final.elf

build/obj/%.o: src/%.c | build/obj
	$(CC) $(CFLAGS) -o $@ $<

build/obj/startup.o : $(STARTUP_DIR)/startup.c | build/obj
	$(CC) $(CFLAGS) -o $@ $<

build/final.elf : $(OBJECTS) build/obj/startup.o | build
	$(LD) $(LDFLAGS) -L$(LIBRARY_DIR) -o $@ $^ -ldrivers

build:
	mkdir -p $@

build/obj:
	mkdir -p $@

.PHONY: ocd
ocd:
	openocd -f board/st_nucleo_f4.cfg
 
.PHONY:clean
clean:
	rm -rf build