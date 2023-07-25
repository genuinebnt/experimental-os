ASM=nasm
CC=i686-elf-gcc
LD=i686-elf-gcc
CFLAGS= -ffreestanding -O2 -nostdlib

BUILD_DIR=build
SRC_DIR=src

OBJECTS_C = $(wildcard $(BUILD_DIR)/*.o)

.PHONY: all always boot kernel myos clean

all: always boot kernel myos

boot: ${BUILD_DIR}/boot.o

${BUILD_DIR}/boot.o:
	${MAKE} -C ${SRC_DIR}/boot BUILD_DIR=$(abspath ${BUILD_DIR})

kernel: ${BUILD_DIR}/kernel.o

${BUILD_DIR}/kernel.o:
	${MAKE} -C ${SRC_DIR}/kernel BUILD_DIR=$(abspath ${BUILD_DIR}) CC=${CC} LD=${LD}

myos: ${BUILD_DIR}/myos.bin

${BUILD_DIR}/myos.bin: boot kernel
	${LD} -T linker.ld -o ${BUILD_DIR}/myos.bin ${CFLAGS} $(BUILD_DIR)/*.o -lgcc

always: 
	mkdir -p build/

clean:
	rm -rf build/*
