org 0x7C00
bits 16

_start:
  xor ax, ax
  mov ds, ax

  mov ss, ax
  mov sp, 0x7e00

  mov si, msg
  call print

  cli 
  hlt

.halt:
  jmp .halt

print:
  push ax
  push bx
  push si

.loop:
  lodsb
  test al, al
  jz .done

  mov ah, 0Eh
  mov bh, 0
  int 10h

  jmp .loop

.done:
  pop si
  pop bx
  pop ax
  ret

msg: db 'Hello, world!', 13, 10, 0
times 510-($-$$) db 0

dw 0xAA55