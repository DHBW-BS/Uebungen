; load.asm
[ORG 0x7C00]
    xor ax, ax          ; make it zero
    mov ds, ax          ; data segment starts at zero
    mov ss, ax
    mov sp, 0x9C00

    mov si, msg         ; load pointer to msg

    call read_floppy
    jmp 0x0000:0x8000   ; Jump to the program's entry point

halt:
    cli                 ; disable interrupts
    hlt                 ; stop execution

msg	db 'Loading ...', 13, 10, 0

read_floppy:            ; Load the program from floppy
    mov ax, 0x0201      ; Read one sector from floppy
    mov bx, 0x0002      ; Destination buffer address: 0x0000:0x8000
    mov es, bx
    mov bx, 0x8000
    mov dl, 0x00        ; Drive number: floppy A
    mov dh, 0x00        ; Head number: 0
    mov cx, 0x0002      ; Sector number: 2
    mov ah, 0x02        ; BIOS disk function
    int 0x13            ; Call the BIOS to read the sector

    ret

    times 510-($-$$) db 0
	db 0x55                         ; write boot sector signature at
	db 0xAA                         ; and of sector