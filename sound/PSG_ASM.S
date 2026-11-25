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
read_val	equ		6

_read_psg:
		movea.l		#reg_sel,a0		; Load register select address
		move.b		read_reg(sp),(a0)	; Set register select number in memory

		movea.l		read_val(sp),a1
		move.b		(a0),(a1)

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