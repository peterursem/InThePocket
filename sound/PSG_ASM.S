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

; ==== Function: set_tone ====
; Purpose: Loads the tone registers (coarse and fine) for the given channel (0=A, 1=B, 2=C)
;          with the given {12-bit} tuning.
; Input: Channel(UINT8) - The channel (A, B, or C) that is being written to
;        Tuning(UINT16) - 12-bit tone that will be written to the specified channel
; Output: None
;		xdef		_set_tone
;
;tone_channel	equ		5
;tone_tune	equ		6
;
;_set_tone:
;		move.b		tone_tune(sp),d0
;
;
;		move.b		tone_channel(sp),d1	; Get channel
;		cmpi.b		#3,d1
;		bgt.b		tone_exit	; If channel > 3, invalid. Reject.
;		; ^ Costs 8 cycles, but needed for spec?
;		moveq.l		#1,d0
;		lsl.b		d1,d0	; Shift to get 1, 2, or 4 for channel register starts
;		; Mask to get 0, 2, or 4 for actual channel tone register starts
;		andi.b		#6,d0	; (Faster than a branch)
;
;tone_exit:
;		rts

; ==== Function: set_volume ====
; Purpose: Set the volume level for the given channel
; Input: Channel(UINT8) - The channel (A, B, or C) that is being written to
;        Volume(UINT8) - The volume value to be written to specified channel
; 
; Output: None

; ==== Function: enable_channel ====
; Purpose: Turns the given channel’s (0=A, 1=B, 2=C) tone/noise signals on/off (0=off, 1=on).
; Input: Channel(UINT8) - The channel (A, B, or C) that is being written to
;        Tone(UINT8) - Set the tone for the specified channel to be either on or off
;        Noise(UINT8) - Set the noise for the specified channel to be either on or off
; Output: None


; ==== Function: set_noise ====
; Purpose: Load the Noise register with the given tuning.
; Input: Tuning(UINT8) - The 5-bit tuning value loaded to the noise register
; Output: None


; ==== Function: set_envelope ====
; Purpose: Loads the PSG envelope control registers with the given envelope shape and 16-bit sustain.
; Input: Shape(UINT8) - The shape loaded into the envelope control registers
;        Sustain(UINT16) - The sustain value being written to the envelope control registers
; Output: None



; ==== Function: stop_sound ====
; Purpose: Silences all PSG sound production.
; Input: None
; Output: None

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