#include "framebuf.h"

FRAMEBUFFER* framebuffer_new(size_t width, size_t height) {
    
    FRAMEBUFFER* framebuffer =(FRAMEBUFFER *)malloc(sizeof(FRAMEBUFFER));
    if(!framebuffer)
        return NULL;

    framebuffer->width       = width;
    framebuffer->height      = height;
    framebuffer->screen_size = width * height;

    framebuffer->screen = (uint32_t*)malloc(width * height * sizeof(uint32_t));
    
    framebuffer_clear(framebuffer);

    return framebuffer;
}

void framebuffer_release(FRAMEBUFFER* framebuffer) {
    if(framebuffer == NULL) return;

    free(framebuffer->screen);
    free(framebuffer);
}

void framebuffer_clear(FRAMEBUFFER* framebuffer) {
    if(framebuffer == NULL) return;

    size_t buffer_size = framebuffer->screen_size * sizeof(uint32_t);
    memset(framebuffer->screen, 0, buffer_size);
}

void framebuffer_copy(FRAMEBUFFER* src, FRAMEBUFFER* dst) {
    
    if(src == NULL || dst == NULL || src->screen_size != dst->screen_size) return;

    size_t buffer_size = src->screen_size * sizeof(uint32_t);
    memcpy(dst->screen, src->screen, buffer_size);
}

// Blits a 32-bit virtual screen buffer to a linear frame buffer.
void blit_to_lfb(FRAMEBUFFER* framebuffer, SURFACE* screen) {
    if (framebuffer == NULL || screen == NULL) return;

    // Calculate the size of the virtual screen in bytes
    size_t buffer_size = framebuffer->screen_size * sizeof(uint32_t);
    memcpy(screen->lfb, framebuffer->screen, buffer_size);
}
