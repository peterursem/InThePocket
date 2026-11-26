/*
	Peter Ursem
	purse327@mtroyal.ca

	Logan Campbell
	lcamp702@mtroyal.ca

	COMP2659-001
	Steve Kalmar

	In the Pocket - Checkpoint 3
	Due: Nov 13, 2026

	The main game module for In the Pocket.
	This module will orchestrate the main game loop using submodule functions.
	pocket.c
*/

#include "types.h"
#include "model/model.h"
#include "render/render.h"
#include "system/system.h"
#include "system/input.h"
#include "events/events.h"
#include "song/song.h"
#include "sound/music.h"
#include "sound/track.h"
#include "sound/effects.h"

#define CREDIT_SCREEN_TIME 3 /* Credit screen linger time in seconds */
#define END_SCREEN_TIME 3 /* End screen linger time in seconds */

void main_init_buffers(UINT32 *buffers[2]);
void play_game(UINT32 *buffers[2], UINT8 *buffer);
bool display_menu(UINT32 *buffers[2], UINT8 *buffer);

/* ==== Function: main ====
PURPOSE: Main game setup and loop

INPUT: N/A

OUTPUT: N/A
*/
int main()
{
	UINT32 *buffers[2];
	UINT8 buffer = 0;

	main_init_buffers(buffers);

	while(display_menu(buffers, &buffer)) /* Allow for replay after the game */
		play_game(buffers, &buffer);
	
	set_screen(buffers[0]);

	return 0;
}

/* ==== Function: main_init_buffers ====
PURPOSE: Initialize the buffer pointer array and disable cursor flash

INPUT: (UINT32 *[2]) Pointer to array of 2 buffer pointers

OUTPUT: N/A
*/
void main_init_buffers(UINT32 *buffers[2])
{
	/* Stop OS cursor blink */
	disable_cursor();
	/* Initialize buffer pointers */
	buffers[0] = get_pbase();
	buffers[1] = buff_256();
}

/* ==== Function: play_game ====
PURPOSE: Plays In the Pocket.

INPUT: N/A

OUTPUT: N/A
*/
void play_game(UINT32 *buffers[2], UINT8 *buffer){

	UINT32 time_then, time_now, time_flip;
	Model model;

	bool quit = false;
	bool render_ready = false;

	time_then = get_time();
	model_init(&model, song, SONG_NOTES, time_then);

	render_init();
	render(buffers[*buffer], *buffer, &model);
	time_then = get_time();

	init_music(track);

	quit = false;
	while (!quit)
	{
		time_now = get_time();

		if (has_input())
			asynch_key_hit(&model, get_scan_input());
			
		if (!render_ready && (time_now > time_then))
		{
			synch_clock_tick(&model, time_now);

			cond_check_key_buffer(&model); /* Apply key hit/misses */
			cond_check_misses(&model); /* Apply passed note misses */
			quit = cond_game_over(&model);
			update_fx(model.last_interval);
			update_music(model.last_interval);

			set_screen(buffers[*buffer]); /* Show previous back buffer */
			*buffer = 1 - *buffer; /* Swap back buffer index */

			time_flip = time_now;
			render_ready = true; /* Ready to render on next tick */
		}
		else if (render_ready && (time_now > time_flip))
		{
			render(buffers[*buffer], *buffer, &model); /* Render to back buffer */
			time_then = get_time();
			render_ready = false; /* No longer ready to render */
		}
	}

	stop_music();
	render(buffers[*buffer], *buffer, &model);
	set_screen(buffers[*buffer]);
	*buffer = 1 - *buffer;

	time_now = get_time();
	while((get_time() - time_now) < (70 * END_SCREEN_TIME)); /* Show end screen for 3 seconds */
}

/* ==== Function: display_menu ====
PURPOSE: Displays main menu.

INPUT: N/A

OUTPUT: N/A
*/

bool display_menu(UINT32 *buffers[2], UINT8 *buffer){

	UINT32 time_then = get_time();
	UINT32 time_now;
    bool play = true;
	char c;

	UINT8 button = 1;
	bool selected = false;
    UINT8 shown = 0;

    while (!selected)
    {
        if (has_input())
        {
            c = get_scan_input();

            if (c == SCAN_A || c == SCAN_LEFT)
            {
                button = 1;
                play = true;
            }
            else if (c == SCAN_D || c == SCAN_RIGHT)
            {
                button = 2;
                play = false;
            }
            else if (c == SCAN_RETURN || c== SCAN_SPACE || c == SCAN_ENTER)
                selected = true;
        }

        time_now = get_time();

        if (time_now - time_then >= 35)
        {
            if (shown == 0)
                shown = button;
            else
                shown = 0;

            render_menu(buffers[*buffer], shown);
            set_screen(buffers[*buffer]);
            *buffer = 1 - *buffer;
            time_then = time_now;
        }
    }

	if (play)
	{	/* Show pre-game credits */
		render_credit_splash(buffers[*buffer]);
		set_screen(buffers[*buffer]);
		*buffer = 1 - *buffer; /* Swap back buffer index */
		while(get_time() < (time_now + CREDIT_SCREEN_TIME * 70));
	}
	
    return play;
}