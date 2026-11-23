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

void init_music(const UINT8 *load_track);
void update_music(UINT32 time_elapsed);
void stop_music();

#endif