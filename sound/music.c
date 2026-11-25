/*
	Peter Ursem
	purse327@mtroyal.ca

	Logan Campbell
	lcamp702@mtroyal.ca

	COMP2659-001
	Steve Kalmar

	In the Pocket - Checkpoint 4
	Due: Nov 25th, 2026 (with extension)

	Functions for playing the music track.

	sound/music.c
*/

#include "music.h"
#include "psg.h"
#include <osbind.h>

#define TRACK_END                 0x00

static UINT8 *track;
static UINT16 delay_elapsed;

void music_update_regs(UINT16 mod);
void disable_keyclick();

/* ==== Function: init_music ====
Purpose: Setup variables for music playback.

Input: load_track(UINT8 *) Pointer to track to play

Output: None
*/
void init_music(const UINT8 *load_track)
{
	disable_keyclick();
	track = load_track;
	delay_elapsed = 0;
}

/* ==== Function: update_music ====
Purpose: Perform a track frame action for every vblank passed.

Input: time_elapsed(UINT32) Time passed since the last update.

Output: None
*/
void update_music(UINT32 time_elapsed)
{	/* Play music events for this track frame */
	UINT8 in_super = 0;
	long exit_ssp;

	while (time_elapsed > 0 && *track != TRACK_END)
	{
		if ((*track) & 0x80)
		{	/* Register data track frame */
			UINT16 mod = (((UINT16)*track) << 8) | *(track+1);	/* Get modified register flags */
			mod &= 0x7FFF;
			track += 2;

			if(!in_super) 
			{	/* Enter super mode if not in super */
				exit_ssp = Super(0);
				in_super = 1;
			}

			music_update_regs(mod);
		}
		else
		{	/* Delay track frame */
			UINT16 time_remain = (UINT16)(*track) - delay_elapsed;
			if (time_elapsed >= time_remain)	
			{/* If delay is done, continue */
				time_elapsed -= time_remain; /* Subtract waiting frames from time */
				delay_elapsed = 0;	/* Reset delay_elapsed counter */
				track++;	/* Next frame */
			} else {
				delay_elapsed += time_elapsed; /* Add elapsed time to delay_elapsed counter*/
				time_elapsed = 0; /* No more frames to process */
			}
		}
	}

	if(in_super)
		Super(exit_ssp);
}

/* ==== Function: stop_music ====
Purpose: Stop all sound playback (Wrapper for stop_sound in Super mode()).

Input: None

Output: None
*/
void stop_music()
{
	long exit_ssp = Super(0);

	stop_sound();

	Super (exit_ssp);
}

/* ==== Function: music_update_regs ====
Purpose: Write register data for a provided modification word and pointer to register data.

Input: mod(UINT16) Modification word. Each 1 indicates a modified register (LSB = 0). Top 2 bits are unused.

Output: None
*/
void music_update_regs(UINT16 mod) {
	UINT8 reg = 0; /* Register # being written to in mod loop */

	mod &= 0x3FFF /* Ignore top 2 bits */

	while (mod)
	{
		if (mod & 1)
			write_psg(reg, *track++); /* Write to register and advance track to next byte of track frame */
			
		reg++;
		mod >>= 1;
	}
}

/* ==== Function: disable_keyclick ====
Purpose: Disable the system key press click noise.

Input: None

Output: None
*/
void disable_keyclick() {
    long exit_ssp = Super(0L);

    unsigned char *conterm = (unsigned char *)0x484;
    *conterm &= 0xFE;

    Super(exit_ssp);
}