CC = arm-none-eabi-gcc
MCPU = cortex-m4
CFLAGS = -c -Iinc -mcpu=$(MCPU) -mthumb -mfloat-abi=soft -std=gnu11 -Wall -Wextra -pedantic -O0

LD = arm-none-eabi-ld
LS = src/GCC/linker_script.ld
LDFLAGS = -T $(LS)

SOURCES := $(wildcard src/*.c)
OBJECTS := $(patsubst src/%.c, build/obj/%.o, $(SOURCES))

OBJDUMP = arm-none-eabi-objdump
ODFLAGS = -t build/final.elf > build/map/final.map

all: build/final.elf

build/obj/%.o: src/%.c | build/obj
	$(CC) $(CFLAGS) -o $@ $<

build/final.elf : $(OBJECTS) | build
	$(LD) $(LDFLAGS) -o $@ $^

build:
	mkdir -p $@

build/obj:
	mkdir -p $@

build/map:
	mkdir -p $@

map: | build/map
	$(OBJDUMP) $(ODFLAGS)

ocd:
	openocd -f board/st_nucleo_f4.cfg
 
clean:
	rm -rf build