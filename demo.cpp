#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

#include "lib/vesa.h"
#include "lib/sound.h"
#include "lib/timer.h"
#include "lib/framebuf.h"
#include "lib/graphics.h"

#include "parts/intro.h"

bool debugmode;

int main(void) {

    SURFACE* screen = NULL;
    FRAMEBUFFER* framebuffer = NULL;

    // system
    timer_init(70);
    sound_init("./assets/music/mtz_aldj.xm");
    graphics_init(320, 240);

    framebuffer = framebuffer_new(320, 240);

    // demo parts
    intro_init();

    // jump into graphics mode
    screen = vesa_init(320, 240);

    // and go

    sound_do();
    intro_do(framebuffer, screen);

    // draw_fullscreen_gradient(framebuffer);
    // blit_to_lfb(framebuffer, screen);
    // getch();

    // release system
    vesa_release(screen);
    framebuffer_free(framebuffer);

    sound_release();
    graphics_release();
   
    timer_release();

    // release parts
    intro_release();
    
    return 0;
}