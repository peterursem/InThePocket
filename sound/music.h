/*
	Peter Ursem
	purse327@mtroyal.ca

	Logan Campbell
	lcamp702@mtroyal.ca

	COMP2659-001
	Steve Kalmar

	In the Pocket - Checkpoint 4
	Due: Nov 25th, 2026 (with extension)

	Declarations of functions for playing the music track.

	sound/music.h
*/

#ifndef MUSIC_H
#define MUSIC_H

#include "../types.h"

/* ==== Function: init_music ====
Purpose: Setup variables for music playback.

Input: load_track(UINT8 *) Pointer to track to play

Output: None
*/
void init_music(const UINT8 *load_track);

/* ==== Function: update_music ====
Purpose: Perform a track frame action for every vblank passed.

Input: time_elapsed(UINT32) Time passed since the last update.

Output: None
*/
void update_music(UINT32 time_elapsed);

/* ==== Function: stop_music ====
Purpose: Stop all sound playback (Wrapper for stop_sound in Super mode()).

Input: None

Output: None
*/
void stop_music();

#endif