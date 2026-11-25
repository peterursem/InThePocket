/*
	Peter Ursem
	purse327@mtroyal.ca

	Logan Campbell
	lcamp702@mtroyal.ca

	COMP2659-001
	Steve Kalmar

	In the Pocket - Checkpoint 4
	Due: Nov 25th, 2026 (with extension)

	Test driver for the effects module. Each test starts an effect, reads the
	channel C registers back with read_psg, and prints pass or FAIL for each check.
	Then each effect is played so it can be checked by ear.

	sound/tests/fxtst.c
*/

#include "../effects.h"
#include "../psg.h"
#include <osbind.h>
#include <stdio.h>

/*------ Function: test_fx_miss ------
PURPOSE: Starts the miss effect and checks the channel C tone, the mixer and the envelope.

INPUT: N/A

OUTPUT: N/A
*/
void test_fx_miss()
{
	/*
	TEST #	REASON					TEST DATA		EXPECTED RESULT			ACTUAL RESULT
	1		miss tone should be		fx_miss()		regs 4-5 between
			one of the out of						00061 and 00226
			tone notes
	2		miss should use			fx_miss()		reg 7 bit 2 = 0,
			tone, not noise							bit 5 = 1
	3		miss should use the		fx_miss()		reg 10 = 0x1F,
			envelope								reg 13 = 0xA
	*/

    UINT8 fine = 0;
    UINT8 coarse = 0;
    UINT8 mixer = 0;
    UINT8 volume = 0;
    UINT8 shape = 0;
    UINT16 tone;
    long exit;

    fx_miss();

    exit = Super(0);
    read_psg(4, &fine);
    read_psg(5, &coarse);
    read_psg(7, &mixer);
    read_psg(10, &volume);
    read_psg(13, &shape);
    Super(exit);

    tone = (coarse << 8) | fine;

    if (tone >= 00061 && tone <= 00226)
        printf("fx_miss tone: pass\r\n");
    else
        printf("fx_miss tone: FAIL\r\n");

    if ((mixer & 0x04) == 0 && (mixer & 0x20) != 0)
        printf("fx_miss tone on, noise off: pass\r\n");
    else
        printf("fx_miss tone on, noise off: FAIL\r\n");

    if (volume == 0x1F && shape == 0xA)
        printf("fx_miss envelope: pass\r\n");
    else
        printf("fx_miss envelope: FAIL\r\n");

    fflush(stdout);
}

/*------ Function: test_miss_end ------
PURPOSE: Starts the miss effect, lets its 15 frames run out, and checks that channel C is off.

INPUT: N/A

OUTPUT: N/A
*/
void test_miss_end()
{
	/*
	TEST #	REASON					TEST DATA		EXPECTED RESULT			ACTUAL RESULT
	4		miss should stop		fx_miss(),		reg 10 = 0,
			after 15 frames			update_fx(15)	reg 7 bits 2 and 5
													set
	*/

    UINT8 mixer = 0;
    UINT8 volume = 0;
    long exit;

    fx_miss();
    update_fx(15);

    exit = Super(0);
    read_psg(7, &mixer);
    read_psg(10, &volume);
    Super(exit);

    if (volume == 0 && (mixer & 0x24) == 0x24)
        printf("fx_miss ends: pass\r\n");
    else
        printf("fx_miss ends: FAIL\r\n");

    fflush(stdout);
}

/*------ Function: test_fx_press ------
PURPOSE: Starts the press effect and checks the noise, the mixer and the envelope.

INPUT: N/A

OUTPUT: N/A
*/
void test_fx_press()
{
	/*
	TEST #	REASON					TEST DATA		EXPECTED RESULT			ACTUAL RESULT
	5		press should set		fx_press()		reg 6 = 0x1F
			the noise tuning
	6		press should use		fx_press()		reg 7 bit 2 = 1,
			noise, not tone							bit 5 = 0
	7		press should use the	fx_press()		reg 10 = 0x1F,
			envelope								reg 11 = 0xFF,
													reg 12 = 0x07,
													reg 13 = 0x0
	*/

    UINT8 noise = 0;
    UINT8 mixer = 0;
    UINT8 volume = 0;
    UINT8 fine = 0;
    UINT8 coarse = 0;
    UINT8 shape = 0;
    long exit;

    fx_press();

    exit = Super(0);
    read_psg(6, &noise);
    read_psg(7, &mixer);
    read_psg(10, &volume);
    read_psg(11, &fine);
    read_psg(12, &coarse);
    read_psg(13, &shape);
    Super(exit);

    if (noise == 0x1F)
        printf("fx_press noise tuning: pass\r\n");
    else
        printf("fx_press noise tuning: FAIL\r\n");

    if ((mixer & 0x04) != 0 && (mixer & 0x20) == 0)
        printf("fx_press noise on, tone off: pass\r\n");
    else
        printf("fx_press noise on, tone off: FAIL\r\n");

    if (volume == 0x1F && fine == 0xFF && coarse == 0x07 && shape == 0x0)
        printf("fx_press envelope: pass\r\n");
    else
        printf("fx_press envelope: FAIL\r\n");

    fflush(stdout);
}

/*------ Function: test_press_end ------
PURPOSE: Starts the press effect, lets its 15 frames run out, and checks that channel C is off.

INPUT: N/A

OUTPUT: N/A
*/
void test_press_end()
{
	/*
	TEST #	REASON					TEST DATA		EXPECTED RESULT			ACTUAL RESULT
	8		press should stop		fx_press(),		reg 10 = 0,
			after 15 frames			update_fx(15)	reg 7 bits 2 and 5
													set
	*/

    UINT8 mixer = 0;
    UINT8 volume = 0;
    long exit;

    fx_press();
    update_fx(15);

    exit = Super(0);
    read_psg(7, &mixer);
    read_psg(10, &volume);
    Super(exit);

    if (volume == 0 && (mixer & 0x24) == 0x24)
        printf("fx_press ends: pass\r\n");
    else
        printf("fx_press ends: FAIL\r\n");

    fflush(stdout);
}

/*------ Function: test_fx_multi ------
PURPOSE: Starts the multiplier effect and checks that it starts on C5 with the right envelope.

INPUT: N/A

OUTPUT: N/A
*/
void test_fx_multi()
{
	/*
	TEST #	REASON					TEST DATA		EXPECTED RESULT			ACTUAL RESULT
	9		multi should start		fx_multi()		reg 4 = 0xD6 (C5),
			on C5 with the							reg 5 = 0,
			envelope								reg 12 = 0x04,
													reg 13 = 0x9
	*/

    UINT8 fine = 0;
    UINT8 coarse = 0;
    UINT8 env = 0;
    UINT8 shape = 0;
    long exit;

    fx_multi();

    exit = Super(0);
    read_psg(4, &fine);
    read_psg(5, &coarse);
    read_psg(12, &env);
    read_psg(13, &shape);
    Super(exit);

    if (fine == 0xD6 && coarse == 0 && env == 0x04 && shape == 0x9)
        printf("fx_multi starts on C5: pass\r\n");
    else
        printf("fx_multi starts on C5: FAIL\r\n");

    update_fx(30);
    fflush(stdout);
}

/*------ Function: test_multi_notes ------
PURPOSE: Steps the multiplier effect through its arpeggio and checks each note.

INPUT: N/A

OUTPUT: N/A
*/
void test_multi_notes()
{
	/*
	TEST #	REASON					TEST DATA		EXPECTED RESULT			ACTUAL RESULT
	10		second note at 25		fx_multi(),		reg 4 = 0xAA (E5)
			frames left				update_fx(5)
	11		third note at 20		update_fx(5)	reg 4 = 0x8F (G5)
			frames left
	12		last note at 10			update_fx(10)	reg 4 = 0x6B (C6)
			frames left
	*/

    UINT8 n2 = 0;
    UINT8 n3 = 0;
    UINT8 n4 = 0;
    long exit;

    fx_multi();

    update_fx(5);
    exit = Super(0);
    read_psg(4, &n2);
    Super(exit);

    update_fx(5);
    exit = Super(0);
    read_psg(4, &n3);
    Super(exit);

    update_fx(10);
    exit = Super(0);
    read_psg(4, &n4);
    Super(exit);

    if (n2 == 0xAA)
        printf("fx_multi note 2 (E5): pass\r\n");
    else
        printf("fx_multi note 2 (E5): FAIL\r\n");

    if (n3 == 0x8F)
        printf("fx_multi note 3 (G5): pass\r\n");
    else
        printf("fx_multi note 3 (G5): FAIL\r\n");

    if (n4 == 0x6B)
        printf("fx_multi note 4 (C6): pass\r\n");
    else
        printf("fx_multi note 4 (C6): FAIL\r\n");

    update_fx(30);
    fflush(stdout);
}

/*------ Function: test_multi_end ------
PURPOSE: Starts the multiplier effect, lets its 30 frames run out, and checks that channel C is off.

INPUT: N/A

OUTPUT: N/A
*/
void test_multi_end()
{
	/*
	TEST #	REASON					TEST DATA		EXPECTED RESULT			ACTUAL RESULT
	13		multi should stop		fx_multi(),		reg 10 = 0,
			after 30 frames			update_fx(30)	reg 7 bits 2 and 5
													set
	*/

    UINT8 mixer = 0;
    UINT8 volume = 0;
    long exit;

    fx_multi();
    update_fx(30);

    exit = Super(0);
    read_psg(7, &mixer);
    read_psg(10, &volume);
    Super(exit);

    if (volume == 0 && (mixer & 0x24) == 0x24)
        printf("fx_multi ends: pass\r\n");
    else
        printf("fx_multi ends: FAIL\r\n");

    fflush(stdout);
}

/*------ Function: test_priority ------
PURPOSE: Starts effects on top of each other and checks which one wins.

INPUT: N/A

OUTPUT: N/A
*/
void test_priority()
{
	/*
	TEST #	REASON					TEST DATA		EXPECTED RESULT			ACTUAL RESULT
	14		press should not		fx_multi(),		reg 13 = 0x9,
			cut off multi			fx_press()		reg 7 bit 2 = 0
	15		miss should cut			fx_press(),		reg 13 = 0xA,
			off press				fx_miss()		reg 7 bit 2 = 0
	16		multi should cut		fx_miss(),		reg 4 = 0xD6 (C5),
			off miss				fx_multi()		reg 13 = 0x9
	*/

    UINT8 mixer = 0;
    UINT8 shape = 0;
    UINT8 fine = 0;
    long exit;

    fx_multi();
    fx_press();
    exit = Super(0);
    read_psg(7, &mixer);
    read_psg(13, &shape);
    Super(exit);

    if (shape == 0x9 && (mixer & 0x04) == 0)
        printf("fx_press ignored during multi: pass\r\n");
    else
        printf("fx_press ignored during multi: FAIL\r\n");

    update_fx(30);
    fx_press();
    fx_miss();
    exit = Super(0);
    read_psg(7, &mixer);
    read_psg(13, &shape);
    Super(exit);

    if (shape == 0xA && (mixer & 0x04) == 0)
        printf("fx_miss overrides press: pass\r\n");
    else
        printf("fx_miss overrides press: FAIL\r\n");

    fx_multi();
    exit = Super(0);
    read_psg(4, &fine);
    read_psg(13, &shape);
    Super(exit);

    if (fine == 0xD6 && shape == 0x9)
        printf("fx_multi overrides miss: pass\r\n");
    else
        printf("fx_multi overrides miss: FAIL\r\n");

    update_fx(30);
    fflush(stdout);
}

/*------ Function: sync_fx ------
PURPOSE: Waits for a number of vertical blanks (70 per second), updating the effects once per blank.

INPUT: syncs, the number of vertical blanks to wait

OUTPUT: N/A
*/
void sync_fx(int syncs)
{
    int i;
    for (i = 0; i < syncs; i++)
    {
        Vsync();
        update_fx(1);
    }
}

/*------ Function: main ------
PURPOSE: Runs every effects test and prints the results, then plays each effect on a keypress to check it by ear.

INPUT: N/A

OUTPUT: 0
*/
int main()
{
	/*
	TEST #	REASON					TEST DATA		EXPECTED RESULT			ACTUAL RESULT
	17		miss should sound		fx_miss()		short out of tune
			out of tune								note
	18		press should sound		fx_press()		short percussive
			like a drum hit							noise
	19		multi should sound		fx_multi()		rising C5 E5 G5 C6
			like a level up							arpeggio
	*/

    test_fx_miss();
    test_miss_end();
    test_fx_press();
    test_press_end();
    test_fx_multi();
    test_multi_notes();
    test_multi_end();
    test_priority();

    printf("Press a key to hear the miss effect\r\n");
    Cnecin();
    fx_miss();
    sync_fx(70);

    printf("Press a key to hear the press effect\r\n");
    Cnecin();
    fx_press();
    sync_fx(70);

    printf("Press a key to hear the multiplier effect\r\n");
    Cnecin();
    fx_multi();
    sync_fx(70);

    printf("Press a key to exit\r\n");
    Cnecin();

    return 0;
}
