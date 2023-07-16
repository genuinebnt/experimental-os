SRC_DIR=src/
BUILD_DIR=build/

ASM=nasm
CC=gcc

.PHONY: all clean

all: floppy bootloader 

floppy: ${BUILD_DIR}/main_floppy.img

${BUILD_DIR}/main_floppy.img: bootloader
	dd if=/dev/zero of=${BUILD_DIR}/main_floppy.img bs=512 count=2880
	dd if=${BUILD_DIR}/bootloader.bin of=${BUILD_DIR}/main_floppy.img seek=0 count=1 conv=notrunc

bootloader: ${BUILD_DIR}/bootloader.bin

${BUILD_DIR}/bootloader.bin:
	${ASM} ${SRC_DIR}/boot.asm -f bin -o ${BUILD_DIR}/bootloader.bin

clean:
	rm -rf build/*
