#include "track.h"

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
#define TONE_HI_FS 0456
#define TONE_HI_G 00435
#define TONE_HI_A 00376
#define TONE_HI_B 00342
#define TONE_HI_C 00326
#define TONE_HI_D 00276

#define TONE_FINE(t)              ((UINT8)((t) & 0xFF))
#define TONE_ROUGH(t)             ((UINT8)(((t) >> 8) & 0x0F))

/* Big-endian register frame macros (data bytes in ascending register order) */
#define FRAME_INIT_A(t, mix, vol) 0x81, 0x83, TONE_FINE(t), TONE_ROUGH(t), (mix), (vol)
#define FRAME_TONE_VOL_A(t, vol)  0x81, 0x03, TONE_FINE(t), TONE_ROUGH(t), (vol)
#define FRAME_TONE_A(t)           0x80, 0x03, TONE_FINE(t), TONE_ROUGH(t)
#define FRAME_VOL_A(vol)          0x81, 0x00, (vol)
#define FRAME_STOP_ALL()          0x87, 0x00, 0x00, 0x00, 0x00
#define TRACK_END                 0x00

/* Subtract 1 because the preceding data register frame already takes 1 VBL.
 * (For a 1-VBL note, omit WAIT() entirely and put the next data frame directly after.) */
#define WAIT(frames) ((UINT8)((frames) - 1) & 0x7F)

const UINT8 track[] = {
    /* A */
    /*  */
    FRAME_INIT_A(TONE_HI_A, 0xFE, 15),   WAIT(SIXTEENTH_TIME),
    FRAME_TONE_A(TONE_HI_G),             WAIT(SIXTEENTH_TIME),
    FRAME_TONE_A(TONE_HI_A),             WAIT(SIXTEENTH_TIME),
    FRAME_VOL_A(0),                      WAIT(SIXTEENTH_TIME),
    FRAME_TONE_VOL_A(TONE_HI_E, 15),     WAIT(EIGHTH_TIME),
    FRAME_TONE_A(TONE_LO_D),             WAIT(SIXTEENTH_TIME),
    FRAME_TONE_A(TONE_LO_C),             WAIT(SIXTEENTH_TIME - 1),
    FRAME_VOL_A(0),                      WAIT(2),
    FRAME_VOL_A(15),                     WAIT(SIXTEENTH_TIME - 1),
    FRAME_TONE_A(TONE_LO_D),             WAIT(SIXTEENTH_TIME),
    FRAME_VOL_A(0),                      WAIT(SIXTEENTH_TIME),
    FRAME_TONE_VOL_A(TONE_LO_A, 15),     WAIT(SIXTEENTH_TIME + EIGHTH_TIME),
    FRAME_TONE_A(TONE_LO_C),             WAIT(EIGHTH_TIME),
    FRAME_VOL_A(0),                      WAIT(EIGHTH_TIME),
    FRAME_TONE_VOL_A(TONE_HI_E, 14),     WAIT(EIGHTH_TIME),
    FRAME_VOL_A(0),                      WAIT(SIXTEENTH_TIME),
    FRAME_TONE_VOL_A(TONE_HI_G, 15),     WAIT(SIXTEENTH_TIME),
    FRAME_VOL_A(0),                      WAIT(SIXTEENTH_TIME),
    FRAME_TONE_VOL_A(TONE_HI_FS, 15),    WAIT(HALF_TIME),

    /* BAR 8 */
    FRAME_TONE_A(TONE_HI_A),             WAIT(SIXTEENTH_TIME),
    FRAME_TONE_A(TONE_HI_G),             WAIT(SIXTEENTH_TIME),
    FRAME_TONE_A(TONE_HI_A),             WAIT(SIXTEENTH_TIME),
    FRAME_VOL_A(0),                      WAIT(SIXTEENTH_TIME),
    FRAME_TONE_VOL_A(TONE_HI_C, 15),     WAIT(EIGHTH_TIME),
    FRAME_TONE_A(TONE_HI_A),             WAIT(SIXTEENTH_TIME),
    FRAME_TONE_A(TONE_HI_G),             WAIT(SIXTEENTH_TIME),
    FRAME_TONE_A(TONE_HI_E),             WAIT(SIXTEENTH_TIME),
    FRAME_TONE_A(TONE_HI_G),             WAIT(SIXTEENTH_TIME),
    FRAME_VOL_A(0),                      WAIT(SIXTEENTH_TIME),
    FRAME_TONE_VOL_A(TONE_LO_D, 15),     WAIT(SIXTEENTH_TIME + EIGHTH_TIME),
    FRAME_TONE_A(TONE_LO_C),             WAIT(EIGHTH_TIME),
    FRAME_VOL_A(0),                      WAIT(EIGHTH_TIME),
    FRAME_TONE_VOL_A(TONE_HI_E, 15),     WAIT(EIGHTH_TIME),
    FRAME_VOL_A(0),                      WAIT(SIXTEENTH_TIME),
    FRAME_TONE_VOL_A(TONE_HI_G, 15),     WAIT(SIXTEENTH_TIME),
    FRAME_VOL_A(0),                      WAIT(EIGHTH_TIME),
    FRAME_TONE_VOL_A(TONE_HI_A, 15),     WAIT(QUARTER_TIME + EIGHTH_TIME),
    FRAME_TONE_A(TONE_HI_B),             WAIT(EIGHTH_TIME),
    FRAME_TONE_A(TONE_HI_A),             WAIT(SIXTEENTH_TIME),
    FRAME_TONE_A(TONE_HI_G),             WAIT(SIXTEENTH_TIME),
    FRAME_TONE_A(TONE_HI_A),             WAIT(SIXTEENTH_TIME),
    FRAME_VOL_A(0),                      WAIT(SIXTEENTH_TIME),
    FRAME_TONE_VOL_A(TONE_HI_E, 15),     WAIT(EIGHTH_TIME),
    FRAME_TONE_A(TONE_LO_D),             WAIT(SIXTEENTH_TIME),
    FRAME_TONE_A(TONE_LO_C),             WAIT(SIXTEENTH_TIME - 1),
    FRAME_VOL_A(0),                      WAIT(2),
    FRAME_VOL_A(15),                     WAIT(SIXTEENTH_TIME - 1),
    FRAME_TONE_A(TONE_LO_D),             WAIT(SIXTEENTH_TIME),
    FRAME_VOL_A(0),                      WAIT(SIXTEENTH_TIME),
    FRAME_TONE_VOL_A(TONE_LO_A, 15),     WAIT(SIXTEENTH_TIME + EIGHTH_TIME),
    FRAME_TONE_A(TONE_LO_C),             WAIT(EIGHTH_TIME),

    /* stop_sound() */
    FRAME_STOP_ALL(),
    TRACK_END
};