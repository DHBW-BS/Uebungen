;print.asm
global _start                   ; must be declared for linker

section .text                   ; code
_start:
    mov edx, len                ; load length of message
    mov ecx, msg                ; load pointer to message
    mov ebx, 1
    mov eax, 4                  ; system call number
    int 0x80                    ; call kernel

    mov ebx, 0                  ; set return code
    mov eax, 1                  ; system call number
    int 0x80                    ; call kernel

section .data                   ; data
msg db "Hello World", 0x0A      ; message with end byte
len equ $ - msg                 ; compute length of message
