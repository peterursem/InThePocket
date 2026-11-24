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
#include "../types.h"
#include "../system/system.h"

#define C7  00065

const UINT16 tones[12] = {
	00326, 00312, 00276, 00264,
	00252, 00240, 00227, 00217,
	00207, 00177, 00170, 00161};

static UINT8 cheer_time = 0;
static UINT8 miss_time = 0;
static UINT8 press_time = 0;

void update_fx()
{

}

void fx_cheer()
{	/* Trigger a crowd cheer sound for each multiplier up */
	set_tone(2, C7);
	set_noise(2);
	enable_channel(2, 1, 1);
	set_volume(2, 0x1F);
	set_envelope(0x8, 0x0FFF);
}

void fx_miss()
{	/* Trigger a buzzer or off key note for a missed note */
	UINT16 tone = tones[get_time() % 12];
	set_tone(2, tone);
	enable_channel(2, 1, 0);
	set_volume(2, 0x1F);
	set_envelope(0x9, 0x0FFF);
}

void fx_press()
{	/* Trigger a percussion sound for each keypress */

}