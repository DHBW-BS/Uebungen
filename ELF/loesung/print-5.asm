;print.asm
BITS 32
[ORG 0x400000]

ehdr:                   ; Elf64_Ehdr
    db 0x7F, "ELF"      ;   e_ident
    db 2                ;     class 64 bit
    db 1                ;     data little endian
    db 1                ;     current version of ELF
    db 0                ;     OS ABI System V
    db 0                ;     ABI version
    times 7 db 0        ;     reserved
    dw 2                ;   e_type executable file
    dw 0x3e             ;   e_machine AMX X86_64
    dd 1                ;   e_version original version of ELF
    dq _start           ;   e_entry
    dq phdr - $$        ;   e_phoff
    dq 0                ;   e_shoff
    dd 0                ;   e_flags
    dw ehdrsize         ;   e_ehsize
    dw phdrsize         ;   e_phentsize
    dw 1                ;   e_phnum
    dw 0                ;   e_shentsize
    dw 0                ;   e_shnum
    dw 0                ;   e_shstrndx

    ehdrsize equ $ - ehdr

phdr:                   ; Elf64_Phdr
    dd 1                ;   p_type
    dd 5                ;   p_flags readable and executable
    dq 0                ;   p_offset
    dq $$               ;   p_vaddr
    dq $$               ;   p_paddr
    dq filesize         ;   p_filesz
    dq filesize         ;   p_memsz
    dq 0x200000         ;   p_align

    phdrsize equ $ - phdr

_start:
    mov edx, len                ; load length of message
    mov ecx, msg                ; load pointer to message
    mov ebx, 1
    mov eax, 4                  ; system call number
    int 0x80                    ; call kernel

    mov ebx, 0                  ; set return code
    mov eax, 1                  ; system call number
    int 0x80                    ; call kernel

data:
    msg db "Hello World", 0xA   ; message with end byte
    len equ $ - msg             ; compute length of message

    filesize equ $ - $$
