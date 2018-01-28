/* ending.c */

# include "base.h"

void ending (uint8_t *state) {

	Texture *tiles = gfx_LoadTexture("/graphics/tiles.png", NULL);
	Texture *text = gfx_LoadTexture("/graphics/ending.png", NULL);

	Rect srcdoor = {600,72,64,48};
	Rect desdoor = {96,72,64,48};

	Music *bso = aud_LoadMusic("/sounds/PrayerofHopeN.wav");

	int16_t x = 0;

	aud_PlayMusic (bso,0);

	for (int16_t i=0;i<951;i++) {

		/* Cleaning the renderer */
		gfx_Clear();

		if (i<360)
			x = i/60;
		else
			x = 5;
		
		if (i > 365)
			gfx_RenderCopy(text,NULL,NULL);

		srcdoor.x = 600 + (64 * x);
		gfx_RenderCopy(tiles,&srcdoor,&desdoor);

		/* Flip */
		gfx_Flip();

	}

	/* Cleaning */
	gfx_FreeTexture (tiles);
	gfx_FreeTexture(text);
	aud_FreeMusic (bso);

	*state = 0;

}
