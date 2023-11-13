#ifndef __FRAMEBUFFER_H__
#define __FRAMEBUFFER_H__

#include <stdint.h>
#include <stdlib.h>
#include "vesa.h"

// Surface information: 
typedef struct {
    size_t     width;                  
    size_t     height;
    size_t     screen_size;
    uint32_t*  screen;
}  FRAMEBUFFER;

FRAMEBUFFER* framebuffer_new(size_t width, size_t height);
void framebuffer_release(FRAMEBUFFER* framebuffer);
void framebuffer_clear(FRAMEBUFFER* framebuffer);
void framebuffer_copy(FRAMEBUFFER* src, FRAMEBUFFER* dst);
void blit_to_lfb(FRAMEBUFFER* framebuffer, SURFACE* screen);

#endif
