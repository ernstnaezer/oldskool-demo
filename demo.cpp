#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

#include "lib/vesa.h"
#include "lib/sound.h"
#include "lib/timer.h"
#include "lib/framebuf.h"
#include "lib/graphics.h"

bool debugmode;

int main(void) {

    int     err;
    SURFACE *screen;

    sound_init("./assets/music/mtz_aldj.xm");

    // initalise VESA driver:
    err=VESAdetect();
    if(err) VESAerror(err);

    screen=VESAopen_surface(320, 240, 32, LINEAR_MODE);
    if(!screen) {
        printf("320x240x32bits (LFB) not present!!!\n");
        exit(1);
    }                

    FRAMEBUFFER* framebuffer = framebuffer_new(320, 240);
    draw_fullscreen_gradient(framebuffer);
    blit_to_lfb(framebuffer, screen);

    timer_init(70);
    sound_do();

    getch();
    
    timer_deinit();
    sound_deinit();

    framebuffer_free(framebuffer);

    VESAclose_surface(screen);

    // shutdown VESA:
    VESAshutdown();

    // set mode back to dos:
    VESAset_mode(0x3);

    return 0;
}