#ifndef __TGA_LOAD_H__
#define __TGA_LOAD_H__

#include <stdio.h>
#include <stdlib.h>
#include "framebuf.h"

FRAMEBUFFER* load_tga(const char* filename);

#endif