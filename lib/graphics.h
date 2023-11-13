#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include "framebuf.h"

void graphics_init(size_t width, size_t height);
void graphics_release();

void color_fullscreen(FRAMEBUFFER* buffer, uint8_t r,uint8_t g,uint8_t b);
void gradient_fullscreen(FRAMEBUFFER* buffer);
void motion_blur_fullscreen(FRAMEBUFFER *buffer, uint32_t speed);
void subtract_fullscreen(FRAMEBUFFER* buffer, uint8_t r,uint8_t g,uint8_t b);

#endif