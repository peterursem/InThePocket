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

/*------ Function: sync_wait ------
PURPOSE: Waits for a number of vertical blanks (70 per second).

INPUT: frames, the number of vertical blanks to wait

OUTPUT: N/A
*/
void sync_wait(UINT16 frames)
{
    UINT16 i;
    for (i = 0; i < frames; i++)
        Vsync();
}

/*------ Function: main ------
PURPOSE: Loops the track, calling update_music after a random wait of 1-4 frames
each time, to check that the music keeps time when frames are late. Stops on a keypress.

INPUT: N/A

OUTPUT: 0
*/
int main()
{
	/*
	TEST #	REASON					TEST DATA		EXPECTED RESULT			ACTUAL RESULT
	1		track should play		track			song plays on			as expected
			on channel A							channel A
	2		song should loop		track			song restarts			as expected
			back to the start						after the last
													note
	3		timing should hold		random 1-4		notes keep the			as expected
			when frames are			frame waits		same tempo
			late
	*/

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
