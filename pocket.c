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
#include "raster/raster.h"
#include "bitmaps/bitmaps.h"

void main_init_buffers(UINT32 *buffers[2]);
void play_game();
bool display_menu();

/* ==== Function: main ====
PURPOSE: Main game setup and loop

INPUT: N/A

OUTPUT: N/A
*/
int main()
{
	if(display_menu())
		play_game();
	
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

void play_game(){

	UINT32 time_then, time_now, time_flip;
	Model model;
	UINT32 *buffers[2];
	UINT8 buffer = 1;
	bool quit, render_ready;

	time_then = get_time();
	model_init(&model, song, SONG_NOTES, time_then);

	main_init_buffers(buffers);
	render(buffers[0], 0, &model);
	render(buffers[1], 1, &model);

	time_then = get_time();

	quit = false;
	while (!quit)
	{
		time_now = get_time();

		if (has_input())
			asynch_key_hit(&model, get_input());
			
		if (!render_ready && (time_now > time_then))
		{
			synch_clock_tick(&model, time_now);

			cond_check_key_buffer(&model); /* Apply key hit/misses */
			cond_check_misses(&model); /* Apply passed note misses */
			quit = cond_game_over(&model);

			set_screen(buffers[buffer]); /* Show previous back buffer */
			buffer = 1 - buffer; /* Swap back buffer index */

			time_flip = time_now;
			render_ready = true; /* Ready to render on next tick */
		}
		else if (render_ready && (time_now > time_flip))
		{
			render(buffers[buffer], buffer, &model); /* Render to back buffer */
			time_then = get_time();
			render_ready = false; /* No longer ready to render */
		}
	}

	render(buffers[0], 0, &model);
	set_screen(buffers[0]);
}

/* ==== Function: display_menu ====
PURPOSE: Displays splash screen / main menu.

INPUT: N/A

OUTPUT: N/A
*/

bool display_menu(){

	UINT32 time_then, time_now;
	bool play;
	char c;
	UINT32 *buffers[2];
	UINT8 buffer = 1;
	UINT8 button = 1;
	main_init_buffers(buffers);
	time_then=get_time();

	render_menu(buffers[0],0);
	render_menu(buffers[1],0);

    while (!has_input())
    {
        time_now = get_time();

        if (time_now - time_then >= 35)
        {
            if (button == 0)
                button = 2;
            else
                button = 0;

            render_menu(buffers[buffer], button);
            set_screen(buffers[buffer]);
            buffer = 1 - buffer;
            time_then = time_now;
        }
    }

    c = get_input();	
	if(c=='a') play=true;
	else if(c=='d') play=false;
	

	return play;
}