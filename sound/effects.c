/*
	Peter Ursem
	purse327@mtroyal.ca

	Logan Campbell
	lcamp702@mtroyal.ca

	COMP2659-001
	Steve Kalmar

	In the Pocket - Checkpoint 4
	Due: Nov 25th, 2026 (with extension)

	Functions for playing sound effects

	sound/effects.c
*/

#include "effects.h"
#include "psg.h"
#include "../system/system.h"
#include <osbind.h>

#define MISS_DUR	15
#define PRESS_DUR	15
#define MULTI_DUR	30
#define MULTI_N2	25
#define MULTI_N3	20
#define MULTI_N4	10

#define C5  00326
#define E5  00252
#define G5  00217
#define C6  00153
#define C7	00065

const UINT16 tones[12] = {
	00226, 00212, 00176, 00164,
	00152, 00140, 00127, 00117,
	00107, 00077, 00070, 00061};

static int multi_time = 0;
static int miss_time = 0;
static int press_time = 0;

/* ==== Function: update_fx ====
Purpose: Update the PSG registers for SFX end / note changes

Input: elapsed(UINT32) Time since last music update (last render frame)

Output: None
*/
void update_fx(UINT32 elapsed)
{
	long exit_ssp = 0;

	if (miss_time > 0)
	{
		exit_ssp = Super(0);
		miss_time -= elapsed;
		if (miss_time <= 0)
		{
			set_volume(2, 0);
			enable_channel(2, 0, 0);
		}
	}
	else if (press_time > 0)
	{
		exit_ssp = Super(0);
		press_time -= elapsed;
		if (press_time <= 0)
		{
			set_volume(2, 0);
			enable_channel(2, 0, 0);
		}
	}
	else if (multi_time > 0)
	{
		exit_ssp = Super(0);
		multi_time -= elapsed;
		if (multi_time <= 0)
		{
			set_volume(2, 0);
			enable_channel(2, 0, 0);
		}
		else if (multi_time >= MULTI_N4)
		{
			set_tone(2, C6);
			set_envelope(0x9, 0x0600);
		}
		else if (multi_time >= MULTI_N3)
		{
			set_tone(2, G5);
			set_envelope(0x9, 0x0400);
		}
		else if (multi_time >= MULTI_N2)
		{
			set_tone(2, E5);
			set_envelope(0x9, 0x0400);
		}
	}

	if (exit_ssp)
		Super(exit_ssp);
}

/* ==== Function: fx_miss ====
Purpose: Start the missed / wrong note effect (out of tone note).
		Overrides all other SFX.

Input: None

Output: None
*/
void fx_miss()
{
	UINT16 tone = tones[get_time() % 12];
	long exit_ssp = Super(0);

	set_tone(2, tone);
	enable_channel(2, 1, 0);
	set_volume(2, 0x1F);
	set_envelope(0xA, 0x000F);

	miss_time = MISS_DUR;
	multi_time = 0;
	press_time = 0;
	Super(exit_ssp);
}

/* ==== Function: fx_press ====
Purpose: Start the percussion SFX for hitting a note.
		Overrides miss SFX.

Input: None

Output: None
*/
void fx_press()
{
	long exit_ssp;

	if (multi_time > 0)
		return;

	exit_ssp = Super(0);

	set_noise(0x1F);
	enable_channel(2, 0, 1);
	set_volume(2, 0x1F);
	set_envelope(0x0, 0x07FF);

	press_time = PRESS_DUR;
	miss_time = 0;

	Super(exit_ssp);
}

/* ==== Function: fx_multi ====
Purpose: Play a level up arpeggio for multiplier increases.
		Overrides all other SFX.

Input: None

Output: None
*/
void fx_multi()
{
	long exit_ssp = Super(0);
	set_tone(2, C5);
	enable_channel(2, 1, 0);
	set_volume(2, 0x1F);
	set_envelope(0x9, 0x0400);

	multi_time = MULTI_DUR;
	miss_time = 0;
	press_time = 0;
	Super(exit_ssp);
}