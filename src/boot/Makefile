ASM?=nasm

BUILD_DIR?=build/

.PHONY: all clean

all: ${BUILD_DIR}/boot.o

${BUILD_DIR}/boot.o:
	${ASM}	-felf32 boot.asm -o ${BUILD_DIR}/boot.o

clean:
	rm -rf ${BUILD_DIR}/boot.o