#include "tga_load.h"

#pragma pack(push, 1)  // Ensure that struct is packed
typedef struct {
    // [other TGA header fields as needed]
    unsigned char id_length;
    unsigned char colormap_type;
    unsigned char image_type;
    unsigned short colormap_origin;
    unsigned short colormap_length;
    unsigned char colormap_depth;
    unsigned short x_origin;
    unsigned short y_origin;
    unsigned short width;
    unsigned short height;
    unsigned char bit_depth;
    unsigned char image_descriptor;
} TGAHeader;
#pragma pack(pop)

FRAMEBUFFER* load_tga(const char* filename) {
    
    FILE* file;
    TGAHeader header;
    unsigned int pixel_index;
    unsigned char packet_header;
    unsigned char is_rle_packet;
    unsigned char pixel_count;
    unsigned long pixel;
    unsigned int i;

    file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Error: Unable to open file\n");
        return NULL;
    }

    fread(&header, sizeof(TGAHeader), 1, file);
    fseek(file, header.id_length, SEEK_CUR);  // Skip the ID field

    FRAMEBUFFER* buffer = framebuffer_new(header.width, header.height);

    if (header.image_type == 2) {
        // Handle uncompressed RGB images...
        fread(buffer->screen, sizeof(unsigned long), header.width * header.height, file);
    }
    else if (header.image_type == 10) {
        // Handle RLE RGB images...
        pixel_index = 0;
        while (pixel_index < header.width * header.height) {
            fread(&packet_header, 1, 1, file);

            is_rle_packet = packet_header >> 7;
            pixel_count = (packet_header & 0x7F) + 1;

            if (is_rle_packet) {
                fread(&pixel, 4, 1, file);  // Assuming 32-bit depth, adjust if needed

                for (i = 0; i < pixel_count; ++i) {
                    buffer->screen[pixel_index++] = pixel;
                }
            }
            else {
                for (i = 0; i < pixel_count; ++i) {
                    fread(&buffer->screen[pixel_index++], 4, 1, file);  // Assuming 32-bit depth, adjust if needed
                }
            }
        }
    }
    else {
        fclose(file);
        framebuffer_release(buffer);
        fprintf(stderr, "Error: Unsupported image type\n");
        return NULL;
    }

    fclose(file);
    return buffer;
}
