;boot.asm
[ORG 0x7C00]
    xor ax, ax          ; make it zero
    mov ds, ax          ; data segment starts at zero

    mov si, msg         ; load pointer to msg

ch_loop:
    lodsb               ; load char from string into al
    or al, al           ; zero means end of string
    jz halt             ; go to end of program on zero
    mov ah, 0x0E        ; color in hi byte of word
    int 0x10            ; use bios for print
    jmp ch_loop         ; go to next char

halt:
    cli                 ; disable interrupts
    hlt                 ; stop execution

msg	db 'Hey You', 13, 10, 0

    times 510-($-$$) db 0
    db 0x55             ; write boot sector signature at
    db 0xAA             ; and of sector