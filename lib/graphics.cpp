#include <stdlib.h>
#include <stdint.h>
#include "framebuf.h"

FRAMEBUFFER* _motion_blur_buffer = NULL;

void graphics_init(size_t width, size_t height) {
    _motion_blur_buffer = framebuffer_new(width, height);
}

void graphics_release() {
    framebuffer_free(_motion_blur_buffer);
}

void color_fullscreen(FRAMEBUFFER* buffer, uint8_t r,uint8_t g,uint8_t b) {
    if (buffer == NULL) return; 

    uint32_t color = (r << 16) | (g << 8) | b;

    for (int i = 0; i < buffer->screen_size; ++i) {
        buffer->screen[i] = color;
    }
}

void gradient_fullscreen(FRAMEBUFFER* buffer) {
    
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

void motion_blur_fullscreen(FRAMEBUFFER *buffer, uint32_t speed) {

  	if (buffer == NULL || speed == 0) return; 
    
    framebuffer_copy(buffer, _motion_blur_buffer);

    // Iterate through each pixel and apply the motion blur effect
    for (int i = 0; i < _motion_blur_buffer->screen_size; ++i) {
        // Initialize the color accumulators
        uint32_t blurR = 0, blurG = 0, blurB = 0;

        // Accumulate the color values of 'speed' number of pixels to the right
        for (int j = 0; j < speed; ++j) {
            // Wrap around the screen buffer if needed
            int index = (i + j) % _motion_blur_buffer->screen_size;
            uint32_t pixelColor = _motion_blur_buffer->screen[index];
            
            // Extract RGB components from the pixel and accumulate them
            blurR += (pixelColor >> 16) & 0xFF;
            blurG += (pixelColor >> 8) & 0xFF;
            blurB += pixelColor & 0xFF;
        }

        // Calculate the average color value for the motion blur effect
        blurR /= speed;
        blurG /= speed;
        blurB /= speed;

        // Combine the averaged RGB values back into a single pixel
        buffer->screen[i] = (blurR << 16) | (blurG << 8) | blurB;
    }
}

void subtract_fullscreen(FRAMEBUFFER* buffer, uint8_t r,uint8_t g,uint8_t b) {
    if (buffer == NULL) return; 

    for (size_t i = 0; i < buffer->screen_size; i++) {
        // Extract the individual color components of the current pixel
        uint8_t pixelR = (buffer->screen[i] >> 16) & 0xFF;
        uint8_t pixelG = (buffer->screen[i] >> 8) & 0xFF;
        uint8_t pixelB = buffer->screen[i] & 0xFF;

        // Subtract the color, ensuring no underflow
        pixelR = (r > pixelR) ? 0 : (pixelR - r);
        pixelG = (g > pixelG) ? 0 : (pixelG - g);
        pixelB = (b > pixelB) ? 0 : (pixelB - b);

        // Reassemble the pixel and write it back to the buffer
        buffer->screen[i] = (buffer->screen[i] & 0xFF000000) | // Preserve the alpha channel
                                 ((uint32_t)pixelR << 16) |
                                 ((uint32_t)pixelG << 8) |
                                 (uint32_t)pixelB;
    }    
}