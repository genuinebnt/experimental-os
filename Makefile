ASM=nasm
GCC=i686-elf-gcc
LD=i686-elf-gcc

BUILD_DIR=build
SRC_DIR=src

.PHONY: all always boot kernel myos clean

all: always boot kernel myos

boot: ${BUILD_DIR}/boot.o

${BUILD_DIR}/boot.o:
	${ASM}	-felf32 ${SRC_DIR}/boot.asm -o ${BUILD_DIR}/boot.o

kernel: ${BUILD_DIR}/kernel.o

${BUILD_DIR}/kernel.o:
	${GCC} -c ${SRC_DIR}/kernel.c -o ${BUILD_DIR}/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

myos: ${BUILD_DIR}/myos.bin

${BUILD_DIR}/myos.bin: boot kernel
	${LD} -T ${SRC_DIR}/linker.ld -o ${BUILD_DIR}/myos.bin -ffreestanding -O2 -nostdlib ${BUILD_DIR}/boot.o ${BUILD_DIR}/kernel.o -lgcc

always: 
	mkdir -p build/

clean:
	rm -rf build/*
