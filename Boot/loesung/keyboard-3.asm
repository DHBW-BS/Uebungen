;keyboard.asm
[ORG 0x7C00]
    xor ax, ax                      ; make it zero
    mov ds, ax                      ; data segment starts at zero
    mov ss, ax
    mov sp, 0x9C00

    cli                             ; disable interrupts
    mov bx, 0x09                    ; set interrupt number
    shl bx, 2
    xor ax, ax
    mov gs, ax
    mov [gs:bx], word keyhandler    ; register keyboard irpt handler
    mov [gs:bx+2], ds
    sti                             ; enable interrupts

;------------------------------------
hang:
    hlt                             ; stop execution until next irpt
    jmp hang

;------------------------------------
keyhandler:
    in 	al, 0x60                    ; get key data
    mov bl, al
    mov byte[port60], al

    in  al, 0x61                    ; keyboard control
    mov ah, al
    or  al, 0x80                    ; disable bit 7
    out 0x61, al                    ; send it back
    xchg ah, al                     ; get original
    out 0x61, al                    ; send that back

    mov al, 0x20                    ; end of interrupt
    out 0x20, al

    cmp bl, 0xAA                    ; shift key released
    je set_lower_key

    cmp bl, 0x2A                    ; shift key pressed
    je set_upper_key

    and bl, 0x80                    ; key released
    jnz done                        ; don't repeat

    mov  ax, [port60]               ; show code of pressed key
    mov  word[reg16], ax
    call printreg16

    mov ax, 0x20                    ; print one blank
    call cprint
    mov bx, [port60]                ; get char out of keymap string
    mov cx, [keymap]                ; by index
    add bx, cx
    mov ax, [bx]
    call cprint                     ; print that char

    mov  si, lineend                ; print CR/LF
    call sprint

    jmp done

set_lower_key:
    mov cx, l_keymap                ; switch to lower case
    mov word[keymap], cx
    jmp done

set_upper_key:
    mov cx, u_keymap                ; switch to upper case
    mov word[keymap], cx

done:
    iret

;------------------------------------
dochar:
    call cprint
sprint:                             ; print string
    lodsb
    cmp al, 0
    jne dochar
    ret

cprint:                             ; print character
    mov ah, 0x0E
    int 0x10
    ret

;------------------------------------
printreg16:                         ; print 16-bit hex string
    mov di, outstr16                ; write into outstr16
    mov ax, [reg16]
    mov si, hexstr
    mov cx, 4
hexloop:
    rol ax, 4
    mov bx, ax
    and bx, 0x0F
    mov bl, [si+bx]
    mov [di], bl
    inc di
    dec cx
    jnz hexloop

    mov si, outstr16                ; print outstr16
    call sprint

    ret

;------------------------------------
hexstr      db '0123456789ABCDEF'
outstr16    db '0000', 0
reg16       dw 0
port60      dw 0
keymap      dw l_keymap
l_keymap    db '--1234567890----qwertzuiop----asdfghjkl-----yxcvbnm'
u_keymap    db '--1234567890----QWERTZUIOP----ASDFGHJKL-----YXCVBNM'

lineend     db 13, 10, 0

;------------------------------------
    times 510-($-$$) db 0
    db 0x55                         ; write boot sector signature at
    db 0xAA                         ; and of sector

;------------------------------------
