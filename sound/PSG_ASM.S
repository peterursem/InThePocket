reg_sel		equ		$FF8800	
reg_val		equ		$FF8802

; ==== Function: read_psg ====
; Purpose: Attempts to read a value from the given PSG register (0-15). This is a helper
;          routine that will be helpful to test the other routines in this module.
; Input: Register(UINT8) - The register that is being read from
;        Value(UINT8 *) - The value that was read from the register
;                        Value is valid, if and only if the output is true
; Output: Boolean indicating if a value was successfully read or not
		xdef		_read_psg

read_reg	equ		5
read_val	equ		7

_read_psg:
		movea.l		#reg_sel,a0		; Load register select address
		move.b		read_reg(sp),(a0)	; Set register select number in memory

		movea.l		#reg_val,a0		; Load value address
		move.b		(a0),read_val(sp)	; Read value from memory

		moveq.l		#-1,d0		; Return true for a good read
		rts

; ==== Function: write_psg ====
; Purpose: Writes the given byte value (0-255) to the given PSG register (0-15). This is a helper
;          routine to be used by the other functions in this module.
; Input: Register(UINT8) - Register that is being written to
;        Value(UINT8) - Value being written to reg
; Output: None
		xdef		_write_psg

write_reg	equ		5
write_val	equ		7

_write_psg:
		movea.l		#reg_sel,a0		; Load register select address
		move.b		write_reg(sp),(a0)	; Set register select number in memory

		movea.l		#reg_val,a0		; Load value address
		move.b		write_val(sp),(a0)	; Read value from memory
		rts

; ==== Function: super ====
; Purpose: Enter supervisor mode, saving the old SSP on the user stack.
; Input: None
; Output: None
; Credit: https://nguillaumin.github.io/perihelion-m68k-tutorials/_of_various_things_mystic_and_important_mainly_concerning_the_art_of_understanding_digits_and_performing_traps.html

super:
		clr.l	-(a7)
		move.w	#32,-(a7)
		trap	#1
		addq.l	#6,a7
		move.l	d0,old_stack
		rts

; ==== Function: super ====
; Purpose: Exit supervisor mode, restoring the SSP.
; Input: None
; Output: None
; Credit: https://nguillaumin.github.io/perihelion-m68k-tutorials/_of_various_things_mystic_and_important_mainly_concerning_the_art_of_understanding_digits_and_performing_traps.html

user:
		move.l	old_stack,-(a7)
		move.w	#32,-(a7)
		trap	#1
		addq.l	#6,a7
		rts

old_stack:	dc.l		0