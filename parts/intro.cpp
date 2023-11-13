#include "intro.h"

void intro_init(){
	printf("intro: init\n");
}

void intro_release(){
	printf("intro: release\n");
}

#define grayval_low 150

void intro_fade_out(FRAMEBUFFER* buffer) {
    const unsigned long fadePeriodTicks = 60; // 0.5 seconds at 60hz
    unsigned long currentTick = Timer % fadePeriodTicks;
    float colorStep = 255 / fadePeriodTicks;
    uint8_t subtractAmount = currentTick * colorStep;
   
	subtract_fullscreen(buffer, subtractAmount, subtractAmount, subtractAmount);
}

void intro_do(FRAMEBUFFER* buffer, SURFACE* screen) {

	while(Order <3) {
		
		intro_fade_out(buffer);

		if	(Row == 0x001) color_fullscreen(buffer, grayval_low, grayval_low, grayval_low);
		if	(Row == 0x03c) color_fullscreen(buffer, grayval_low, grayval_low, grayval_low);
		if	(Row == 0x040) color_fullscreen(buffer, grayval_low, grayval_low, grayval_low);
		if	(Row == 0x07c) color_fullscreen(buffer, grayval_low, grayval_low, grayval_low);

		// if (Row & 1 == 1) {
		// 	motion_blur_fullscreen(buffer,10);		
		// }
		VGAwait_vr();
		blit_to_lfb(buffer, screen);
	}

	while(Order == 3) {

		intro_fade_out(buffer);
		
		if	(Row == 0x001) color_fullscreen(buffer, grayval_low, grayval_low, grayval_low);
		if	(Row == 0x03c) color_fullscreen(buffer, grayval_low, grayval_low, grayval_low);
		if	(Row == 0x064) color_fullscreen(buffer, 255, 255, 255);
		if	(Row == 0x070) color_fullscreen(buffer, 255, 255, 255);
		if	(Row == 0x040) color_fullscreen(buffer, grayval_low, grayval_low, grayval_low);
		if	(Row == 0x07c) color_fullscreen(buffer, grayval_low, grayval_low, grayval_low);

		// if (Row & 1 == 1) {
		// 	motion_blur_fullscreen(buffer,10);
		// }

		VGAwait_vr();
		blit_to_lfb(buffer, screen);
	}

	
}
