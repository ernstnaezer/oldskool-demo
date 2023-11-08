#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "./usm/usmplay.h"

extern bool debugmode;

USM	*music;

void sound_init(char *filename) {
	printf("sound: init\n");

	printf("sound: hardware init\n");
	HardwareInit(_psp);

    if (debugmode){
    	USS_Setup();
	}
	else{
	    printf("sound: auto setup\n");
	    USS_AutoSetup();
	}

    printf("sound: loading audio %s\n", filename);
	music=XM_Load(LM_File,0x020202020,filename);

    if (Error_Number!=0){
        Display_Error(Error_Number);
        exit(0);
    }

	printf("sound: output device: %s\n",DEV_Name);
}

void sound_do(){
	printf("sound: do\n");

	printf("sound: play\n");
	USMP_StartPlay(music);

	if (Error_Number!=0) { 
        Display_Error(Error_Number); 
        exit(-1); 
    }
}

void sound_deinit() {
	printf("sound: de-init\n");

	printf("sound: stop play\n");
	USMP_StopPlay();

	printf("sound: free module\n");
	USMP_FreeModule(music);
}