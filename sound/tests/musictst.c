/*
	Peter Ursem
	purse327@mtroyal.ca

	Logan Campbell
	lcamp702@mtroyal.ca

	COMP2659-001
	Steve Kalmar

	In the Pocket - Checkpoint 4
	Due: Nov 25th, 2026 (with extension)

	Tests for the music player.

	sound/musictst.c
*/

#include "music.h"
#include "track.h"
#include <osbind.h>
#include <stdlib.h>

void sync_wait(UINT16 frames)
{
    UINT16 i;
    for (i = 0; i < frames; i++)
        Vsync();
}

int main()
{
    UINT16 frames = 1; /* 1-4 frames of delay to test lag handling */

    init_music(track);

    Vsync();

    while(!Cconis()) {
        update_music(frames);
        frames = (rand() & 3) + 1;
        sync_wait(frames);
    }

    Cconin();
    return 0;
}
