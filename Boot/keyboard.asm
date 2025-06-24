;boot.asm
[ORG 0x7C00]
	xor ax, ax
	mov ds, ax
	mov ss, ax
	mov sp, 0x9C00

	cli
	mov bx, 0x09
	shl bx, 2
	xor ax, ax
	mov gs, ax
	mov [gs:bx], word keyhandler	;register keyboard irpt handler
	mov [gs:bx+2], ds
	sti

	jmp hang			;go into endless loop

;------------------------------------
hang:
	jmp hang

;------------------------------------
keyhandler:
	in 	al, 0x60		;get key data
	mov bl, al
	mov byte[port60], al

	in  al, 0x61		;keyboard control
	mov ah, al
	or  al, 0x80		;disable bit 7
	out 0x61, al		;send it back
	xchg ah, al		;get original
	out 0x61, al		; send that back

	mov al, 0x20		;end of interrupt
	out 0x20, al

	and bl, 0x80		;key released
	jnz done		;don't repeat

	mov  ax, [port60]	;show code of pressed key
	mov  word[reg16], ax
	call printreg16

	mov  si, lineend	;print CR/LF
	call sprint

done:
	iret

;------------------------------------
dochar:
	call cprint
sprint:
	lodsb
	cmp al, 0
	jne dochar
	ret

cprint:
	mov ah, 0x0E
	int 0x10
	ret

;------------------------------------
printreg16:
	mov di, outstr16
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

	mov si, outstr16
	call sprint

	ret

;------------------------------------
hexstr		db '0123456789ABCDEF'
outstr16	db '0000', 0
reg16		dw 0
port60		dw 0

lineend 	db 13, 10, 0

;------------------------------------
	times 510-($-$$) db 0
	db 0x55
	db 0xAA
;------------------------------------
