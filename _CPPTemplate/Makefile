CC = arm-none-eabi-gcc
CXX = arm-none-eabi-g++
MACH = cortex-m4
CFLAGS = -c -Icmsis -Iinc -mcpu=$(MACH) -mthumb -Wall -O0

LD = arm-none-eabi-ld
LS = src/GCC/gcc_arm.ld
LDFLAGS = -T $(LS) -e Reset_Handler -shared -fno-exceptions

OBJCOPY = arm-none-eabi-objcopy

CSOURCES := $(wildcard src/*.c)
CPPSOURCES := $(wildcard src/*.cpp)
OBJECTS := $(patsubst src/%.c, obj/%.o, $(CSOURCES)) $(patsubst src/%.cpp, obj/%.o, $(CPPSOURCES))

all : build/final.bin

obj/%.o : src/%.c | obj
	$(CC) $(CFLAGS) -o $@ $<

obj/%.o : src/%.cpp | obj
	$(CXX) $(CFLAGS) -o $@ $<

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
