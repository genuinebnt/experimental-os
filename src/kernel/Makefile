CC?=i686-elf-gcc
LD?=i686-elf-gcc
CFLAGS?=-std=gnu99 -ffreestanding -O2 -Wall -Wextra

BUILD_DIR?=build/

SOURCES_C=$(wildcard *.c)
HEADERS_C=$(wildcard *.h)
OBJECTS_C = $(addprefix $(BUILD_DIR)/, $(SOURCES_C:.c=.o))


.PHONY: all clean

all: $(OBJECTS_C)

$(BUILD_DIR)/%.o: %.c ${HEADERS_C} | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf ${OBJECTS_C}