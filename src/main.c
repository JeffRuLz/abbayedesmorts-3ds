/* Abbaye des Morts */
/* Version 2.0 */

/* (c) 2010 - Locomalito & Gryzor87 */
/* 2013 - David "Nevat" Lara */

/* GPL v3 license */

 
# include "main.h"

int main () {

	uint8_t exit = 0;
	uint8_t state = 0; /* 0-intro,1-history,2-game,3-gameover,4-ending,5-exit */
	uint8_t grapset = 0; /* 0-8bits, 1-16bits */
	uint8_t fullscreen = 0; /* 0-Windowed,1-Fullscreen */

	/* 3DS initialization */
	gfx_Init();
	aud_Init();

	romfsInit();

	while (exit != 1 && aptMainLoop()) {
		switch (state) {
			case 0: startscreen(&state,&grapset,&fullscreen);
							break;
			case 1: history(&state,&grapset,&fullscreen);
							break;
			case 2: game(&state,&grapset,&fullscreen);
							break;
			case 3: gameover(&state);
							break;
			case 4: ending(&state);
							break;
			default: exit = 1;
							break;
		}
	}

	/* Cleaning */
	romfsExit();

	aud_Exit();
	gfx_Exit();

	/* Exiting normally */
	return 0;

}
