/* gameover.c */

# include "gameover.h"

void gameover (uint8_t *state) {

	Texture *gameover = gfx_LoadTexture("/graphics/gameover.png", NULL);
	
	Music *bso = aud_LoadMusic("/sounds/GameOverV2N.wav");

	gfx_Clear();
	gfx_RenderCopy(gameover,NULL,NULL);

	/* Flip */
	gfx_Flip();
	aud_PlayMusic(bso, 0);

	/* Wait */
	sleep(8);

	/* Cleaning */
	aud_FreeMusic (bso);
	gfx_FreeTexture(gameover);

	*state = 0;

}
