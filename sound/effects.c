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
#include <osbind.h>

#define C7          00065
#define CHEER_DUR   70
#define MISS_DUR    35
#define PRESS_DUR   7

const UINT16 tones[12] = {
	00326, 00312, 00276, 00264,
	00252, 00240, 00227, 00217,
	00207, 00177, 00170, 00161};

static UINT8 cheer_time = 0;
static UINT8 miss_time = 0;
static UINT8 press_time = 0;

void update_fx()
{
	UINT8 elapsed;
	UINT8 vol;
	UINT8 noise;
	long exit_ssp = 0;

	if (cheer_time > 0)
	{
		exit_ssp = Super(0);
		cheer_time--;
		if (cheer_time == 0)
		{
			set_volume(2, 0);
			enable_channel(2, 0, 0);
		}
		else
		{
			elapsed = CHEER_DUR - cheer_time;

			if (elapsed < 12)
			{
				/* Swell up as the crowd erupts */
				vol = 6 + (elapsed * 9) / 12;
				noise = 0x1A - (elapsed / 2);
			}
			else if (elapsed < 45)
			{
				/* Sustained roar and applause texture */
				vol = (elapsed & 1) ? 13 : 15;
				noise = (elapsed & 2) ? 0x14 : 0x17;
			}
			else
			{
				/* Gradual fade-out */
				vol = (cheer_time * 14) / 25;
				noise = 0x16 + ((25 - cheer_time) / 8);
			}

			set_noise(noise);
			set_volume(2, vol);
		}
	}
	else if (miss_time > 0)
	{
		exit_ssp = Super(0);
		miss_time--;
		if (miss_time == 0)
		{
			set_volume(2, 0);
			enable_channel(2, 0, 0);
		}
	}
	else if (press_time > 0)
	{
		exit_ssp = Super(0);
		press_time--;
		if (press_time == 0)
		{
			set_volume(2, 0);
			enable_channel(2, 0, 0);
		}
	}

	if (exit_ssp)
		Super(exit_ssp);
}

void fx_cheer()
{	/* Trigger a crowd cheer sound for each multiplier up */
	long exit_ssp = Super(0);
	enable_channel(2, 0, 1);
	set_noise(0x1A);
	set_volume(2, 6);

	cheer_time = CHEER_DUR;
	miss_time = 0;
	press_time = 0;
	Super(exit_ssp);
}

void fx_miss()
{	/* Trigger a buzzer or off key note for a missed note */
	UINT16 tone = tones[get_time() % 12];
	long exit_ssp = Super(0);
	set_tone(2, tone);
	enable_channel(2, 1, 0);
	set_volume(2, 0x1F);
	set_envelope(0x9, 0x0FFF);

	miss_time = MISS_DUR;
	cheer_time = 0;
	press_time = 0;
	Super(exit_ssp);
}

void fx_press()
{	/* Trigger a percussion sound for each keypress */
	long exit_ssp;

	if (cheer_time > 0)
		return;

	exit_ssp = Super(0);

	set_noise(0x10);
	enable_channel(2, 0, 1);
	set_volume(2, 0x1F);
	set_envelope(0x9, 0x0400);

	press_time = PRESS_DUR;
	miss_time = 0;

	Super(exit_ssp);
}