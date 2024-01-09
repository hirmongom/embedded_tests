PROJECT_ROOT := ../

CC = arm-none-eabi-gcc
MCPU = cortex-m4
CFLAGS = -c -Iinclude -mcpu=$(MCPU) -mthumb -mfloat-abi=soft -std=gnu11 -Wall -Wextra -pedantic -O0

LIBRARY_OUTPUT := $(PROJECT_ROOT)/lib/libdrivers.a
AR := arm-none-eabi-ar
ARFLAGS := rcs

SOURCES := $(wildcard src/*.c)
OBJECTS := $(patsubst src/%.c, build/obj/%.o, $(SOURCES))

build/obj/%.o: src/%.c | build/obj
	$(CC) $(CFLAGS) -o $@ $<

$(LIBRARY_OUTPUT): $(OBJECTS) | $(PROJECT_ROOT)/lib
	$(AR) $(ARFLAGS) $@ $^


build:
	mkdir -p $@

build/obj:
	mkdir -p $@

$(PROJECT_ROOT)/lib:
	mkdir -p $@

.PHONY: all
all: build $(LIBRARY_OUTPUT)

.PHONY: clean
clean:
	rm -rf build
	rm -f $(PROJECT_ROOT)/lib/libdrivers.a