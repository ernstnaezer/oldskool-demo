#ifndef __intro_h__
#define __intro_h__

#include <stdlib.h>
#include <stdint.h>

#include "../lib/framebuf.h"
#include "../lib/vesa.h"
#include "../lib/graphics.h"
#include "../lib/usm/USMPLAY.H"
#include "../lib/sound.H"
#include "../lib/timer.H"

void intro_init();
void intro_release();
void intro_do(FRAMEBUFFER* buffer, SURFACE* screen);

#endif
