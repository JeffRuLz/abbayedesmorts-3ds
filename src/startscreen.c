/* startscreen.c */

# include "base.h"

void startscreen(uint8_t *state,uint8_t *grapset,uint8_t *fullscreen) {

	uint8_t exit = 0;
	uint8_t musicplay = 0;

	Rect srcintro = {0,0,256,192};
	Rect desintro = {0,0,256,192};

	//SDL_Event keyp;

	/* Loading PNG */
	Texture *intro = gfx_LoadTexture("/graphics/intro.png", NULL);
	Texture *intromd = gfx_LoadTexture("/graphics/intromd.png", NULL);

	/* Load audio */
	Music *music = aud_LoadMusic("/sounds/MainTitleN.wav");

	while (exit != 1  && aptMainLoop()) {

		/* Cleaning the renderer */
		gfx_Clear();

		/* Put image on renderer */
		if (*grapset == 0)
			gfx_RenderCopy(intro, &srcintro, &desintro);
		else
			gfx_RenderCopy(intromd, &srcintro, &desintro);

		/* Flip ! */
		gfx_Flip();

		/* Play music if required */
		if (musicplay == 0) {
			musicplay = 1;
			aud_PlayMusic(music, 0);
		}

		/* Check keyboard */
		inp_ScanInput();

		// Change graphic set
		if (btnX.pressed == 1) {
			if (*grapset == 0)
				*grapset = 1;
			else
				*grapset = 0;
		}

		// Show instructions
		if (btnY.pressed == 1) {
			if (srcintro.y == 0)
				srcintro.y = 192;
			else {
				srcintro.y = 0;
				musicplay = 0;
			}
		}

		// Start game
		if (btnStart.pressed == 1) {
			*state = 1;
			exit = 1;
		}

		// Exit game
		if (btnSelect.pressed == 1) {
			exit = 1;
			*state = 6;
		}
	}

	/* Cleaning */
	gfx_FreeTexture(intro);
	gfx_FreeTexture(intromd);
	aud_StopMusic(music);
	aud_FreeMusic(music);
}
