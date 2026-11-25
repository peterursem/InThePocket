/*
	Peter Ursem
	purse327@mtroyal.ca

	Logan Campbell
	lcamp702@mtroyal.ca

	COMP2659-001
	Steve Kalmar

	In the Pocket - Checkpoint 4
	Due: Nov 25th, 2026 (with extension)

	Declarations for sound effect functions.

	sound/effects.h
*/
#ifndef EFFECTS_H
#define EFFECTS_H

#include "../types.h"

/* ==== Function: update_fx ====
Purpose: Update the PSG registers for SFX end / note changes

Input: elapsed(UINT32) Time since last music update (last render frame)

Output: None
*/
void update_fx(UINT32 elapsed);

/* ==== Function: fx_miss ====
Purpose: Start the missed / wrong note effect (out of tone note).
		Overrides all other SFX.

Input: None

Output: None
*/
void fx_miss();

/* ==== Function: fx_press ====
Purpose: Start the percussion SFX for hitting a note.
		Overrides miss SFX.

Input: None

Output: None
*/
void fx_press();

/* ==== Function: fx_multi ====
Purpose: Play a level up arpeggio for multiplier increases.
		Overrides all other SFX.

Input: None

Output: None
*/
void fx_multi();

#endif