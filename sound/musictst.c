#include "music.h"
#include "track.h"
#include <osbind.h>

int main()
{
    init_music(track);

    while(!Cconis()) {
        update_music(1);
        Vsync();
    }

    Cconin();
    return 0;
}
