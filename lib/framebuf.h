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
void framebuffer_free(FRAMEBUFFER* framebuffer);
void blit_to_lfb(FRAMEBUFFER* framebuffer, SURFACE* lfb);

#endif
