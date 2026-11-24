/*
	Peter Ursem
	purse327@mtroyal.ca

	Logan Campbell
	lcamp702@mtroyal.ca

	COMP2659-001
	Steve Kalmar

	In the Pocket - Checkpoint 4
	Due: Nov 25th, 2026 (with extension)

	Tests for PSG control functions.

	sound/psgtst.c
*/

#include "psg.h"
#include <osbind.h>

/*
240/BPM = S per whole note
1/70 = S per frame
note s / frame s = frame wait
(240/BPM)/(1/70) = 16800/BPM (Whole note frames)
*/

/*
    DEFINES FOR 103 BPM
*/
#define WHOLE_TIME 160 /* Frame wait for a whole note (16800/BPM) */
#define HALF_TIME 80 /* Frame wait for a half note (8400/BPM)*/
#define QUARTER_TIME 40 /* Frame wait for a quarter note (4200/BPM)*/
#define EIGHTH_TIME 20 /* Frame wait for an eighth note (2100/BPM) */
#define SIXTEENTH_TIME 10 /* Frame wait for an eighth note (1050/BPM) */

#define TONE_E4 01247
#define TONE_F4 01201
#define TONE_G4 01073
#define TONE_A4 00774
#define TONE_B4 00705
#define TONE_C5 00654
#define TONE_D5 00575
#define TONE_E5 00523
#define TONE_F5 00500
#define TONE_FS5 00456
#define TONE_G5 00435
#define TONE_A5 00376
#define TONE_B5 00342
#define TONE_C6 00326
#define TONE_HI_D 00276

void sync_wait(int syncs) 
{
    int i;
    for(i=0; i<syncs; i++)
        Vsync();
}

int main()
{
    long exit = Super(0);
    set_tone(0, 01247);
    enable_channel(0, true, false);
    set_volume(0, 15);
    set_envelope(0x0E, 0xFFFF);
    /*
    sync_wait(326);
    set_volume(0, 0x00);
    sync_wait(489);
    */

    /* A */
    set_tone(0, TONE_A5);
    set_volume(0, 15);
    sync_wait(SIXTEENTH_TIME);
    set_tone(0, TONE_G5);
    sync_wait(SIXTEENTH_TIME);
    set_tone(0, TONE_A5);
    sync_wait(SIXTEENTH_TIME);
    set_volume(0, 0);
    sync_wait(SIXTEENTH_TIME);
    set_tone(0, TONE_E5);
    set_volume(0, 15);
    sync_wait(EIGHTH_TIME);
    set_tone(0, TONE_D5);
    sync_wait(SIXTEENTH_TIME);
    set_tone(0, TONE_C5);
    sync_wait(SIXTEENTH_TIME - 1);
    set_volume(0, 0);
    sync_wait(2);
    set_volume(0, 15);
    sync_wait(SIXTEENTH_TIME - 1);
    set_tone(0, TONE_D5);
    sync_wait(SIXTEENTH_TIME);
    set_volume(0, 0);
    sync_wait(SIXTEENTH_TIME);
    set_tone(0, TONE_A4);
    set_volume(0, 15);
    sync_wait(SIXTEENTH_TIME + EIGHTH_TIME);
    set_tone(0, TONE_C5);
    sync_wait(EIGHTH_TIME);
    set_volume(0, 0);
    sync_wait(EIGHTH_TIME);
    set_tone(0, TONE_E5);
    set_volume(0, 14);
    sync_wait(EIGHTH_TIME);
    set_volume(0, 0);
    sync_wait(SIXTEENTH_TIME);
    set_tone(0, TONE_G5);
    set_volume(0, 15);
    sync_wait(SIXTEENTH_TIME);
    set_volume(0, 0);
    sync_wait(SIXTEENTH_TIME);
    set_tone(0, TONE_FS5);
    set_volume(0, 15);
    sync_wait(HALF_TIME);
	/* BAR 8 */
	set_tone(0, TONE_A5);
    sync_wait(SIXTEENTH_TIME);
    set_tone(0, TONE_G5);
    sync_wait(SIXTEENTH_TIME);
    set_tone(0, TONE_A5);
    sync_wait(SIXTEENTH_TIME);
	set_volume(0, 0);
	sync_wait(SIXTEENTH_TIME);
	set_tone(0, TONE_C6);
	set_volume(0, 15);
	sync_wait(EIGHTH_TIME);
	set_tone(0, TONE_A5);
	sync_wait(SIXTEENTH_TIME);
	set_tone(0, TONE_G5);
	sync_wait(SIXTEENTH_TIME);
	set_tone(0, TONE_E5);
	sync_wait(SIXTEENTH_TIME);
	set_tone(0, TONE_G5);
	sync_wait(SIXTEENTH_TIME);
	set_volume(0, 0);
	sync_wait(SIXTEENTH_TIME);
	set_tone(0, TONE_D5);
	set_volume(0, 15);
	sync_wait(SIXTEENTH_TIME + EIGHTH_TIME);
	set_tone(0, TONE_C5);
	sync_wait(EIGHTH_TIME);
	set_volume(0, 0);
	sync_wait(EIGHTH_TIME);
	set_tone(0, TONE_E5);
	set_volume(0, 15);
	sync_wait(EIGHTH_TIME);
	set_volume(0, 0);
	sync_wait(SIXTEENTH_TIME);
	set_tone(0, TONE_G5);
	set_volume(0, 15);
	sync_wait(SIXTEENTH_TIME);
	set_volume(0, 0);
	sync_wait(EIGHTH_TIME);
	set_tone(0, TONE_A5);
	set_volume(0, 15);
	sync_wait(QUARTER_TIME + EIGHTH_TIME);
	set_tone(0, TONE_B5);
	sync_wait(EIGHTH_TIME);
    set_tone(0, TONE_A5);
    sync_wait(SIXTEENTH_TIME);
    set_tone(0, TONE_G5);
    sync_wait(SIXTEENTH_TIME);
    set_tone(0, TONE_A5);
    sync_wait(SIXTEENTH_TIME);
    set_volume(0, 0);
    sync_wait(SIXTEENTH_TIME);
    set_tone(0, TONE_E5);
    set_volume(0, 15);
    sync_wait(EIGHTH_TIME);
    set_tone(0, TONE_D5);
    sync_wait(SIXTEENTH_TIME);
    set_tone(0, TONE_C5);
    sync_wait(SIXTEENTH_TIME - 1);
    set_volume(0, 0);
    sync_wait(2);
    set_volume(0, 15);
    sync_wait(SIXTEENTH_TIME - 1);
    set_tone(0, TONE_D5);
    sync_wait(SIXTEENTH_TIME);
    set_volume(0, 0);
    sync_wait(SIXTEENTH_TIME);
    set_tone(0, TONE_A4);
    set_volume(0, 15);
    sync_wait(SIXTEENTH_TIME + EIGHTH_TIME);
    set_tone(0, TONE_C5);
    sync_wait(EIGHTH_TIME);
    stop_sound();

    Super(exit);

    return 0;
}