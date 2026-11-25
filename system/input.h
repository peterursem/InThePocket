/*
	Peter Ursem
	purse327@mtroyal.ca

	Logan Campbell
	lcamp702@mtroyal.ca

	COMP2659-001
	Steve Kalmar

	In the Pocket - Checkpoint 3
	Due: Nov 13, 2026

	Header file for the input.c file. Contains function prototypes for the functions in input.c.
	These functions will eventually be replaced when TOS is thrown out in favour of a custom ROM.

	system/input.h
*/

#include "../types.h"

#define SCAN_ESC	1

#define SCAN_A		30
#define SCAN_S		31
#define SCAN_D		32
#define SCAN_F		33

#define SCAN_LEFT	75
#define SCAN_RIGHT	77

#define SCAN_RETURN	28
#define SCAN_SPACE	57
#define SCAN_ENTER	114

/* ==== Function: has_input ====

PURPOSE: Check wether an input is waiting in the buffer.

INPUT: N/A

OUTPUT: (bool) Is there an input waiting in the buffer?
*/
bool has_input();

/* ==== Function: get_ascii_input ====

PURPOSE: Read an input from the input buffer.

INPUT: N/A

OUTPUT: (UINT8) ASCII input code from buffer.
*/
UINT8 get_ascii_input();

/* ==== Function: get_scan_input ====

PURPOSE: Read an input from the input buffer.

INPUT: N/A

OUTPUT: (UINT8) Scancode for input from buffer.
*/
UINT8 get_scan_input();