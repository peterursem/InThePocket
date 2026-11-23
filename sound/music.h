#ifndef MUSIC_H
#define MUSIC_H

#include "../types.h"

void init_music(const UINT8 *load_track);
void update_music(UINT32 time_elapsed);
void stop_music();

#endif