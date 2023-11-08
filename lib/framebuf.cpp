#include "framebuf.h"

FRAMEBUFFER* framebuffer_new(size_t width, size_t height) {
    
    FRAMEBUFFER* framebuffer =(FRAMEBUFFER *)malloc(sizeof(FRAMEBUFFER));
    if(!framebuffer)
        return NULL;

    framebuffer->width       = width;
    framebuffer->height      = height;
    framebuffer->screen_size = width * height;

    framebuffer->screen = (uint32_t*)malloc(width * height * sizeof(uint32_t));
    memset(framebuffer->screen, 0, width * height * sizeof(uint32_t));

    return framebuffer;
}

void framebuffer_free(FRAMEBUFFER* framebuffer) {
    
    if(framebuffer == NULL) return;

    free(framebuffer->screen);
    free(framebuffer);
}

// Blits a 32-bit virtual screen buffer to a linear frame buffer.
void blit_to_lfb(FRAMEBUFFER* framebuffer, SURFACE* surface) {
    if (framebuffer == NULL || surface == NULL) return;

    // Calculate the size of the virtual screen in bytes
    size_t buffer_size = framebuffer->screen_size * sizeof(uint32_t);

    // Copy the buffer to the LFB
    memcpy(surface->lfb, framebuffer->screen, buffer_size);
}
