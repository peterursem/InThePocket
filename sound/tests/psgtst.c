/*
	Peter Ursem
	purse327@mtroyal.ca

	Logan Campbell
	lcamp702@mtroyal.ca

	COMP2659-001
	Steve Kalmar

	In the Pocket - Checkpoint 4
	Due: Nov 25th, 2026 (with extension)

	Test driver for the PSG module. Each test writes to the PSG through psg.c,
	reads the registers back with read_psg, and prints pass or FAIL for each check.

	sound/tests/psgtst.c
*/

#include "../psg.h"
#include <osbind.h>
#include <stdio.h>

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


/*------ Function: test_read_write ------
PURPOSE: Writes a value to a PSG register and reads it back, then tries to read a register that does not exist.

INPUT: N/A

OUTPUT: N/A
*/
void test_read_write()
{
	/*
	TEST #	REASON					TEST DATA		EXPECTED RESULT			ACTUAL RESULT
	1		write_psg then			reg 0, 0x55		read_psg returns		as expected
			read_psg should							true, value is 0x55
			give back the same
			value
	2		read_psg should			reg 16			read_psg returns		as expected
			reject a register						false
			outside 0-15
	*/

    UINT8 value = 0;
    bool ok;

    write_psg(0, 0x55);
    ok = read_psg(0, &value);

    if (ok && value == 0x55)
        printf("read/write register 0: pass\r\n");
    else
        printf("read/write register 0: FAIL\r\n");

    ok = read_psg(16, &value);

    if (!ok)
        printf("read invalid register 16: pass\r\n");
    else
        printf("read invalid register 16: FAIL\r\n");
}

/*------ Function: test_set_tone ------
PURPOSE: Sets a tone on channel A and checks both tone registers, then checks that a bad channel and a bad tuning are ignored.

INPUT: N/A

OUTPUT: N/A
*/
void test_set_tone()
{
	/*
	TEST #	REASON					TEST DATA		EXPECTED RESULT			ACTUAL RESULT
	3		valid tone should		channel 0,		reg 0 = 0x23,			as expected
			land in the fine		0x123			reg 1 = 0x01
			and coarse
			registers
	4		bad channel should		channel 3,		regs 0 and 1			as expected
			be ignored				0x456			unchanged
	5		tuning over 12 bits		channel 0,		regs 0 and 1			as expected
			should be ignored		0x1000			unchanged
	*/

    UINT8 fine = 0;
    UINT8 coarse = 0;

    set_tone(0, 0x123);
    read_psg(0, &fine);
    read_psg(1, &coarse);

    if (fine == 0x23 && coarse == 0x01)
        printf("set_tone valid: pass\r\n");
    else
        printf("set_tone valid: FAIL\r\n");

    set_tone(3, 0x456);
    read_psg(0, &fine);
    read_psg(1, &coarse);

    if (fine == 0x23 && coarse == 0x01)
        printf("set_tone bad channel 3: pass\r\n");
    else
        printf("set_tone bad channel 3: FAIL\r\n");

    set_tone(0, 0x123);
    set_tone(0, 0x1000);
    read_psg(0, &fine);
    read_psg(1, &coarse);

    if (fine == 0x23 && coarse == 0x01)
        printf("set_tone bad tuning: pass\r\n");
    else
        printf("set_tone bad tuning: FAIL\r\n");

    fflush(stdout);
}

/*------ Function: test_set_volume ------
PURPOSE: Sets the volume on channel A and reads it back, then checks that a bad channel and a bad volume are ignored.

INPUT: N/A

OUTPUT: N/A
*/
void test_set_volume()
{
	/*
	TEST #	REASON					TEST DATA		EXPECTED RESULT			ACTUAL RESULT
	6		valid volume should		channel 0, 10	reg 8 = 10				as expected
			land in the volume
			register
	7		bad channel should		channel 3, 5,	reg 11 still			as expected
			be ignored				reg 11 preset	0x77
									to 0x77
	8		volume over 5 bits		channel 0,		reg 8 still 10			as expected
			should be ignored		0x20
	*/

    UINT8 value = 0;

    set_volume(0, 10);
    read_psg(8, &value);

    if (value == 10)
        printf("set_volume valid: pass\r\n");
    else
        printf("set_volume valid: FAIL\r\n");

    write_psg(11, 0x77);
    set_volume(3, 5);
    read_psg(11, &value);

    if (value == 0x77)
        printf("set_volume bad channel 3: pass\r\n");
    else
        printf("set_volume bad channel 3: FAIL\r\n");

    set_volume(0, 0x20);
    read_psg(8, &value);

    if (value == 10)
        printf("set_volume bad volume: pass\r\n");
    else
        printf("set_volume bad volume: FAIL\r\n");

    fflush(stdout);
}

/*------ Function: test_enable_channel ------
PURPOSE: Turns channel A tone and noise on and off and checks the mixer bits, then checks that a bad channel is ignored. Puts the mixer back the way it was when done.

INPUT: N/A

OUTPUT: N/A
*/
void test_enable_channel()
{
	/*
	TEST #	REASON					TEST DATA		EXPECTED RESULT			ACTUAL RESULT
	9		tone on, noise off		channel 0,		reg 7 bit 0 = 0,		as expected
			should clear the		1, 0			bit 3 = 1
			tone bit and set
			the noise bit
	10		tone off, noise on		channel 0,		reg 7 bit 0 = 1,		as expected
			should do the			0, 1			bit 3 = 0
			opposite
	11		bad channel should		channel 3,		reg 7 unchanged			as expected
			be ignored				1, 1
	*/

    UINT8 value = 0;
    UINT8 before = 0;

    enable_channel(0, 1, 0);
    read_psg(7, &value);

    if ((value & 0x01) == 0 && (value & 0x08) != 0)
        printf("enable_channel tone on: pass\r\n");
    else
        printf("enable_channel tone on: FAIL\r\n");

    enable_channel(0, 0, 1);
    read_psg(7, &value);

    if ((value & 0x01) != 0 && (value & 0x08) == 0)
        printf("enable_channel noise on: pass\r\n");
    else
        printf("enable_channel noise on: FAIL\r\n");

    read_psg(7, &before);
    enable_channel(3, 1, 1);
    read_psg(7, &value);

    if (value == before)
        printf("enable_channel bad channel 3: pass\r\n");
    else
        printf("enable_channel bad channel 3: FAIL\r\n");

    write_psg(7, before);
    fflush(stdout);
}

/*------ Function: test_set_noise ------
PURPOSE: Sets the noise tuning and reads it back, then checks that a bad tuning is ignored.

INPUT: N/A

OUTPUT: N/A
*/
void test_set_noise()
{
	/*
	TEST #	REASON					TEST DATA		EXPECTED RESULT			ACTUAL RESULT
	12		valid tuning should		0x15			reg 6 = 0x15			as expected
			land in the noise
			register
	13		tuning over 5 bits		0x20			reg 6 still 0x15		as expected
			should be ignored
	*/

    UINT8 value = 0;

    set_noise(0x15);
    read_psg(6, &value);

    if (value == 0x15)
        printf("set_noise valid: pass\r\n");
    else
        printf("set_noise valid: FAIL\r\n");

    set_noise(0x20);
    read_psg(6, &value);

    if (value == 0x15)
        printf("set_noise bad tuning: pass\r\n");
    else
        printf("set_noise bad tuning: FAIL\r\n");

    fflush(stdout);
}

/*------ Function: test_set_envelope ------
PURPOSE: Sets an envelope shape and sustain and checks all three envelope registers, then checks that a bad shape is ignored.

INPUT: N/A

OUTPUT: N/A
*/
void test_set_envelope()
{
	/*
	TEST #	REASON					TEST DATA		EXPECTED RESULT			ACTUAL RESULT
	14		valid shape and			shape 0x9,		reg 11 = 0x34,			as expected
			sustain should land		0x1234			reg 12 = 0x12,
			in regs 11-13							reg 13 = 0x9
	15		shape over 4 bits		shape 0x10,		regs 11-13				as expected
			should be ignored		0x5678			unchanged
	*/

    UINT8 fine = 0;
    UINT8 coarse = 0;
    UINT8 shape = 0;

    set_envelope(0x9, 0x1234);
    read_psg(11, &fine);
    read_psg(12, &coarse);
    read_psg(13, &shape);

    if (fine == 0x34 && coarse == 0x12 && shape == 0x9)
        printf("set_envelope valid: pass\r\n");
    else
        printf("set_envelope valid: FAIL\r\n");

    set_envelope(0x10, 0x5678);
    read_psg(11, &fine);
    read_psg(12, &coarse);
    read_psg(13, &shape);

    if (fine == 0x34 && coarse == 0x12 && shape == 0x9)
        printf("set_envelope bad shape: pass\r\n");
    else
        printf("set_envelope bad shape: FAIL\r\n");

    fflush(stdout);
}

/*------ Function: test_stop_sound ------
PURPOSE: Turns on every channel, calls stop_sound, and checks that everything is off without touching the I/O port bits. Puts the mixer back the way it was when done.

INPUT: N/A

OUTPUT: N/A
*/
void test_stop_sound()
{
	/*
	TEST #	REASON					TEST DATA		EXPECTED RESULT			ACTUAL RESULT
	16		stop_sound should		all channels	reg 7 bits 0-5			as expected
			turn off every			on				all set
			tone and noise
	17		stop_sound should		as above		reg 7 bits 6-7			as expected
			not touch the I/O						unchanged
			port bits
	*/

    UINT8 before = 0;
    UINT8 value = 0;

    read_psg(7, &before);
    enable_channel(0, 1, 1);
    enable_channel(1, 1, 1);
    enable_channel(2, 1, 1);
    stop_sound();
    read_psg(7, &value);

    if ((value & 0x3F) == 0x3F)
        printf("stop_sound all channels off: pass\r\n");
    else
        printf("stop_sound all channels off: FAIL\r\n");

    if ((value & 0xC0) == (before & 0xC0))
        printf("stop_sound I/O bits untouched: pass\r\n");
    else
        printf("stop_sound I/O bits untouched: FAIL\r\n");

    write_psg(7, before);
    fflush(stdout);
}

/*------ Function: sync_wait ------
PURPOSE: Waits for a number of vertical blanks (70 per second).

INPUT: syncs, the number of vertical blanks to wait

OUTPUT: N/A
*/
void sync_wait(int syncs) 
{
    int i;
    for(i=0; i<syncs; i++)
        Vsync();
}

/*------ Function: main ------
PURPOSE: Runs every PSG test and prints the results, then plays a short melody on channel A to check the sound by ear. Waits for a keypress before exiting.

INPUT: N/A

OUTPUT: 0
*/
int main()
{
	/*
	TEST #	REASON					TEST DATA		EXPECTED RESULT			ACTUAL RESULT
	18		melody should be		hand-written	melody plays			as expected
			heard on channel A		melody
	*/

    long exit = Super(0);
    test_read_write();
    test_set_tone();
    test_set_volume();
    test_enable_channel();
    test_set_noise();
    test_set_envelope();
    test_stop_sound();

    Super(exit);

    return 0;
}