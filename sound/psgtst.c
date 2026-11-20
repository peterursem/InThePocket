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
#define WHOLE_TIME 163 /* Frame wait for a whole note (16800/BPM) */
#define HALF_TIME 82 /* Frame wait for a half note (8400/BPM)*/
#define QUARTER_TIME 41 /* Frame wait for a quarter note (4200/BPM)*/
#define EIGHTH_TIME 20 /* Frame wait for an eighth note (2100/BPM) */
#define SIXTEENTH_TIME 10 /* Frame wait for an eighth note (1050/BPM) */

#define TONE_LO_E 01247
#define TONE_LO_F 01201
#define TONE_LO_G 01073
#define TONE_LO_A 00774
#define TONE_LO_B 00705
#define TONE_LO_C 00654
#define TONE_LO_D 00575
#define TONE_HI_E 00523
#define TONE_HI_F 00500
#define TONE_HI_FS 00456
#define TONE_HI_G 00435
#define TONE_HI_A 00376
#define TONE_HI_B 00342
#define TONE_HI_C 00326
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
    set_tone(0, TONE_HI_A);
    set_volume(0, 15);
    sync_wait(SIXTEENTH_TIME);
    set_tone(0, TONE_HI_G);
    sync_wait(SIXTEENTH_TIME);
    set_tone(0, TONE_HI_A);
    sync_wait(SIXTEENTH_TIME);
    set_volume(0, 0);
    sync_wait(SIXTEENTH_TIME);
    set_tone(0, TONE_HI_E);
    set_volume(0, 15);
    sync_wait(EIGHTH_TIME);
    set_tone(0, TONE_LO_D);
    sync_wait(SIXTEENTH_TIME);
    set_tone(0, TONE_LO_C);
    sync_wait(SIXTEENTH_TIME - 1);
    set_volume(0, 0);
    sync_wait(2);
    set_volume(0, 15);
    sync_wait(SIXTEENTH_TIME - 1);
    set_tone(0, TONE_LO_D);
    sync_wait(SIXTEENTH_TIME);
    set_volume(0, 0);
    sync_wait(SIXTEENTH_TIME);
    set_tone(0, TONE_LO_A);
    set_volume(0, 15);
    sync_wait(SIXTEENTH_TIME + EIGHTH_TIME);
    set_tone(0, TONE_LO_C);
    sync_wait(EIGHTH_TIME);
    set_volume(0, 0);
    sync_wait(EIGHTH_TIME);
    set_tone(0, TONE_HI_E);
    set_volume(0, 14);
    sync_wait(EIGHTH_TIME);
    set_volume(0, 0);
    sync_wait(SIXTEENTH_TIME);
    set_tone(0, TONE_HI_G);
    set_volume(0, 15);
    sync_wait(SIXTEENTH_TIME);
    set_volume(0, 0);
    sync_wait(SIXTEENTH_TIME);
    set_tone(0, TONE_HI_FS);
    set_volume(0, 15);
    sync_wait(HALF_TIME);
	/* BAR 8 */
	set_tone(0, TONE_HI_A);
    sync_wait(SIXTEENTH_TIME);
    set_tone(0, TONE_HI_G);
    sync_wait(SIXTEENTH_TIME);
    set_tone(0, TONE_HI_A);
    sync_wait(SIXTEENTH_TIME);
	set_volume(0, 0);
	sync_wait(SIXTEENTH_TIME);
	set_tone(0, TONE_HI_C);
	set_volume(0, 15);
	sync_wait(EIGHTH_TIME);
	set_tone(0, TONE_HI_A);
	sync_wait(SIXTEENTH_TIME);
	set_tone(0, TONE_HI_G);
	sync_wait(SIXTEENTH_TIME);
	set_tone(0, TONE_HI_E);
	sync_wait(SIXTEENTH_TIME);
	set_tone(0, TONE_HI_G);
	sync_wait(SIXTEENTH_TIME);
	set_volume(0, 0);
	sync_wait(SIXTEENTH_TIME);
	set_tone(0, TONE_LO_D);
	set_volume(0, 15);
	sync_wait(SIXTEENTH_TIME + EIGHTH_TIME);
	set_tone(0, TONE_LO_C);
	sync_wait(EIGHTH_TIME);
	set_volume(0, 0);
	sync_wait(EIGHTH_TIME);
	set_tone(0, TONE_HI_E);
	set_volume(0, 15);
	sync_wait(EIGHTH_TIME);
	set_volume(0, 0);
	sync_wait(SIXTEENTH_TIME);
	set_tone(0, TONE_HI_G);
	set_volume(0, 15);
	sync_wait(SIXTEENTH_TIME);
	set_volume(0, 0);
	sync_wait(EIGHTH_TIME);
	set_tone(0, TONE_HI_A);
	set_volume(0, 15);
	sync_wait(QUARTER_TIME + EIGHTH_TIME);
	set_tone(0, TONE_HI_B);
	sync_wait(EIGHTH_TIME);
    set_tone(0, TONE_HI_A);
    sync_wait(SIXTEENTH_TIME);
    set_tone(0, TONE_HI_G);
    sync_wait(SIXTEENTH_TIME);
    set_tone(0, TONE_HI_A);
    sync_wait(SIXTEENTH_TIME);
    set_volume(0, 0);
    sync_wait(SIXTEENTH_TIME);
    set_tone(0, TONE_HI_E);
    set_volume(0, 15);
    sync_wait(EIGHTH_TIME);
    set_tone(0, TONE_LO_D);
    sync_wait(SIXTEENTH_TIME);
    set_tone(0, TONE_LO_C);
    sync_wait(SIXTEENTH_TIME - 1);
    set_volume(0, 0);
    sync_wait(2);
    set_volume(0, 15);
    sync_wait(SIXTEENTH_TIME - 1);
    set_tone(0, TONE_LO_D);
    sync_wait(SIXTEENTH_TIME);
    set_volume(0, 0);
    sync_wait(SIXTEENTH_TIME);
    set_tone(0, TONE_LO_A);
    set_volume(0, 15);
    sync_wait(SIXTEENTH_TIME + EIGHTH_TIME);
    set_tone(0, TONE_LO_C);
    sync_wait(EIGHTH_TIME);
    stop_sound();

    Super(exit);

    return 0;
}