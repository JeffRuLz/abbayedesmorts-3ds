/* history.c */

# include "base.h"

void history(uint8_t *state,uint8_t *grapset,uint8_t *fullscreen) {

	//SDL_Event keyp;

	/* Load audio */
	Music *music = aud_LoadMusic("/sounds/ManhuntN.wav");

	/* Loading PNG */
	Texture *tiles = gfx_LoadTexture("/graphics/tiles.png", NULL);
	Texture *text = gfx_LoadTexture("/graphics/history.png", NULL);

	Rect srcjean = {384,88,16,24};
	Rect desjean = {0,100,16,24};
	Rect srcenem = {96,64,16,24};
	Rect desenem = {0,100,16,24};

	uint8_t exit = 0;
	float posjean = -16;
	float posenem[4] = {-17,-17,-17,-17};
	uint8_t animation = 0;
	uint8_t musicload = 0;

	while (exit != 1 && aptMainLoop()) {

		/* Cleaning the renderer */
		gfx_Clear();

		/* Play music at start */
		if (musicload == 0) {
			musicload = 1;
			aud_PlayMusic(music, 0);
		}

		/* Show text */
		gfx_RenderCopy(text,NULL,NULL);

		/* Animation control */
		if (animation < 13)
			animation ++;
		else
			animation = 0;

		/* Jean running */
		if (posjean < 257) {
			posjean += 0.75;
			desjean.x = posjean;
			srcjean.x = 384 + ((animation / 7) * 16); /* Walking animation */
			srcjean.y = 88 + (*grapset * 120); /* 8 or 16 bits sprite */
			gfx_RenderCopy(tiles,&srcjean,&desjean);
		}

		/* Crusaders running */
		/* When start running */
		for (uint16_t i=0;i<4;i++) {
			if (posjean > (35 + (30 * i)))
				posenem[i] += 0.65;
		}
		/* Draw */
		for (uint16_t i=0;i<4;i++) {
			if ((posenem[i] > -17) && (posenem[i] < 257)) {
				desenem.x = posenem[i];
				srcenem.x = 96 + ((animation / 7) * 16);
				srcenem.y = 64 + (*grapset * 120);
				gfx_RenderCopy(tiles,&srcenem,&desenem);
			}
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

		// Start game
		if (btnStart.pressed == 1) {
			*state = 2;
			exit = 1;
		}

		// Exit game
		if (btnSelect.pressed == 1) {
			exit = 1;
			*state = 6;
		}

		if (posenem[3] > 256) { /* Ending history */
			exit = 1;
			*state = 2;
		}

		/* Flip ! */
		gfx_Flip();

	}

	/* Cleaning */
	gfx_FreeTexture(tiles);
	gfx_FreeTexture(text);
	aud_StopMusic(music);
	aud_FreeMusic(music);

}
