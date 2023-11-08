#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include "framebuf.h"

void draw_fullscreen_color(FRAMEBUFFER* buffer, uint8_t r,uint8_t g,uint8_t b);
void draw_fullscreen_gradient(FRAMEBUFFER* buffer);

#endif