#include <stdlib.h>
#include <stdint.h>
#include "framebuf.h"

void draw_fullscreen_color(FRAMEBUFFER* buffer, uint8_t r,uint8_t g,uint8_t b){
    if (buffer == NULL) return; 

    uint32_t color = (r << 16) | (g << 8) | b;

    for (int i = 0; i < buffer->screen_size; ++i) {
        buffer->screen[i] = color;
    }
}

void draw_fullscreen_gradient(FRAMEBUFFER* buffer) {
    
    if (buffer == NULL) return;
 
    for (int y = 0; y < buffer->height; ++y) {

        uint8_t redValue = (uint8_t)(255 * y / (buffer->height - 1));
        uint32_t color = (0xFF << 24) | (redValue << 16) | (0x00 << 8) | 0x00;

        for (int x = 0; x < buffer->width; ++x) {
            int index = (y * buffer->width) + x;
            buffer->screen[index] = color;
        }
    }
}
