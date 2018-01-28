/* drawing.c */

# include "drawing.h"

void drawscreen (uint stagedata[][22][32],Texture *tiles,uint room[],uint counter[],uint changeflag,Sound *fx[],uint changetiles) {

	Rect srctiles = {0,0,8,8};
	Rect destiles = {0,0,8,8};

	for (uint8_t coordy=0; coordy<=21; coordy++) {
		for (uint8_t coordx=0; coordx<=31; coordx++) {
			uint16_t data = stagedata[room[0]][coordy][coordx];
			if ((data > 0) && (data != 99)) {
				destiles.x = coordx * 8;
				destiles.y = coordy * 8;
				if (data < 200) {
					srctiles.w = 8;
					srctiles.h = 8;
					if (data < 101) {
						srctiles.y = 0;
						if (data == 84) /* Cross brightness */
							srctiles.x = (data - 1) * 8 + (counter[0]/8 * 8);
						else
							srctiles.x = (data - 1) * 8;
					}
					else {
						if (data == 154) {
							srctiles.x=600 + ((counter[0] / 8) * 16);
							srctiles.y=0;
							srctiles.w=16;
							srctiles.h=24;
						}
						else {
							srctiles.y = 8;
							srctiles.x = (data - 101) * 8;
						}
					}
				}
				if ((data > 199) && (data < 300)) {
					srctiles.x = (data - 201) * 48;
					srctiles.y = 16;
					srctiles.w = 48;
					srctiles.h = 48;
				}
				if ((data > 299) && (data < 399)) {
					srctiles.x = 96 + ((data - 301) * 8);
					srctiles.y = 16;
					srctiles.w = 8;
					srctiles.h = 8;
					/* Door movement */
					if ((room[0] == 7) && ((counter[1] > 59) && (counter[1] < 71))) {
						if ((data == 347) || (data == 348) || (data == 349) || (data == 350)) {
							destiles.x += 2;
							if ((data == 350) && (counter[1] == 70))
								aud_PlaySound(-1, fx[3], 0); /* Sound of door */
						}
					}
				}
				/* Hearts */
				if ((data > 399) && (data < 405)) {
					srctiles.x = 96 + ((data - 401) * 8) + (32 * (counter[0] / 15));
					srctiles.y = 24;
					srctiles.w = 8;
					srctiles.h = 8;
				}
				/* Crosses */
				if ((data > 408) && (data < 429)) {
					srctiles.x = 96 + ((data - 401) * 8) + (32 * (counter[1] / 23));
					srctiles.y = 24;
					srctiles.w = 8;
					srctiles.h = 8;
				}

				if ((data > 499) && (data < 599)) {
					srctiles.x = 96 + ((data - 501) * 8);
					srctiles.y = 32;
					srctiles.w = 8;
					srctiles.h = 8;
				}
				if ((data > 599) && (data < 650)) {
					srctiles.x = 96 + ((data - 601) * 8);
					srctiles.y = 56;
					srctiles.w = 8;
					srctiles.h = 8;
				}
				if (data == 650) { /* Cup */
					srctiles.x = 584;
					srctiles.y = 87;
					srctiles.w = 16;
					srctiles.h = 16;
				}
				destiles.w = srctiles.w;
				destiles.h = srctiles.h;
				if ((data == 152) || (data == 137) || (data == 136)) {
					if (changeflag == 0) {
						srctiles.y = srctiles.y + (changetiles * 120);
						gfx_RenderCopy(tiles,&srctiles,&destiles);
					}
				}
				else {
					srctiles.y = srctiles.y + (changetiles * 120);
					gfx_RenderCopy(tiles,&srctiles,&destiles);
				}
			}
		}
	}

}

void statusbar (Texture *tiles,uint room[],int lifes,int crosses,Texture *fonts,uint changetiles) {

	Rect srcbar = {448,104,13,12};
	Rect desbar = {0,177,13,12};
	Rect srcnumbers = {0,460,10,10};
	Rect desnumbers = {18,178,10,10};
	Rect srctext = {0,0,140,20};
	Rect destext = {115,176,136,18};

	/* Show heart and crosses sprites */
	if (changetiles == 1)
		srcbar.y = 224;
	gfx_RenderCopy(tiles,&srcbar,&desbar);
	srcbar.x = 461;
	srcbar.w = 12;
	desbar.x = 32;
	gfx_RenderCopy(tiles,&srcbar,&desbar);

	for (uint8_t i=0; i<=2; i++) {
		switch (i) {
			case 0: 	srcnumbers.x = lifes * 10;
						gfx_RenderCopy(fonts,&srcnumbers,&desnumbers);
						break;
			case 1: 	if (crosses < 10) {
							desnumbers.x = 50;
							srcnumbers.x = crosses * 10;
							gfx_RenderCopy(fonts,&srcnumbers,&desnumbers);
						}
						else {
							desnumbers.x = 50;
							srcnumbers.x = 10;
							gfx_RenderCopy(fonts,&srcnumbers,&desnumbers);
							desnumbers.x = 55;
							srcnumbers.x = (crosses - 10) * 10;
							gfx_RenderCopy(fonts,&srcnumbers,&desnumbers);
						}
						break;
			case 2: 	if ((room[0] > 0) && (room[0] < 4)) {
							srctext.y = (room[0] - 1) * 20;
							gfx_RenderCopy(fonts,&srctext,&destext);
					  	}
						if (room[0] > 4) {
							srctext.y = (room[0] - 2) * 20;
							gfx_RenderCopy(fonts,&srctext,&destext);
						}
						break;
		}

	}

}

void drawrope (struct enem enemies,Texture *tiles,uint changetiles) {

	Rect srctile = {424,8,16,8};
	Rect destile = {0,0,16,8};

	for (uint8_t i=2; i<6; i++) {
		int16_t blocks = (enemies.y[i] - (enemies.limleft[i] - 8)) / 8;
		for (uint8_t j=0; j<=blocks; j++) {
			srctile.y = 8 + (changetiles * 120);
	  		destile.x = enemies.x[i];
	  		destile.y = (enemies.limleft[i] - 8) + (8 * j);
			gfx_RenderCopy(tiles,&srctile,&destile);
		}
	}

}

void drawshoots (float proyec[],Texture *tiles,struct enem *enemies,uint changetiles) {
/* Shoots from skeletons & gargoyles */

	Rect srctile = {656,24,16,8};
	Rect destile = {0,0,0,0};

	srctile.y = 24 + (changetiles * 120);

	for (uint8_t n=0; n<=4; n+=2) {
		if (proyec[n] > 0) {
	  		uint8_t i = proyec[n+1];
	  		if (enemies->type[i] == 15) {
				srctile.h = 16;
				srctile.x = 640 - (16 * enemies->direction[i]);
	  		}

		  	/* Move shoot */
		  	if (enemies->direction[i] == 1) {
					if (proyec[n] > enemies->limleft[i])
					  proyec[n] -= 2.5;
					else {
					  enemies->fire[i] = 0;
					  enemies->speed[i] = 0;
					  proyec[n] = 0;
					}
	  		}
	  		else {
					if (proyec[n] < enemies->limright[i])
		  			proyec[n] += 2.5;
					else {
		  			enemies->fire[i] = 0;
					  enemies->speed[i] = 0;
					  proyec[n] = 0;
					}
	  		}
	  		destile.w = srctile.w;
			destile.h = srctile.h;

	  		/* Draw shoot */
	  		switch (enemies->direction[i]) {
					case 0: 	if ((proyec[n] < (enemies->limright[i] - 8)) && (proyec[n] != 0)) {
							  		destile.x = proyec[n];
									destile.y = enemies->y[i] + 8;
									gfx_RenderCopy(tiles,&srctile,&destile);
								}
								break;
					case 1: 	if (proyec[n] > (enemies->limleft[i] + 8)) {
									destile.x = proyec[n];
									destile.y = enemies->y[i] + 8;
									gfx_RenderCopy(tiles,&srctile,&destile);
								}
								break;
	  		}
		}

	}

}

void showparchment (uint *parchment) {
	
	gfx_Flip();

	Texture* yparchment = NULL;

	switch (*parchment) {
		case 3: yparchment = gfx_LoadTexture("/graphics/parchment1.png", NULL);
						break;
		case 8:	yparchment = gfx_LoadTexture("/graphics/parchment2.png", NULL);
						break;
		case 12: yparchment = gfx_LoadTexture("/graphics/parchment3.png", NULL);
						 break;
		case 14: yparchment = gfx_LoadTexture("/graphics/parchment4.png", NULL);
						 break;
		case 16: yparchment = gfx_LoadTexture("/graphics/parchment5.png", NULL);
						 break;
		case 21: yparchment = gfx_LoadTexture("/graphics/parchment6.png", NULL);
						 break;
	}

	gfx_Clear();

	gfx_RenderCopy(yparchment,NULL,NULL);
	gfx_FreeTexture(yparchment);
}

void redparchment (struct hero *jean) {

	gfx_Flip();

	Texture *rparchment = gfx_LoadTexture("/graphics/redparch.png", NULL);

	gfx_Clear();

	gfx_RenderCopy(rparchment,NULL,NULL);
	gfx_FreeTexture(rparchment);

	jean->flags[6] = 4;

}

void blueparchment (struct hero *jean) {

	gfx_Flip();

	Texture *bparchment = gfx_LoadTexture("/graphics/blueparch.png", NULL);

	gfx_Clear();

	gfx_RenderCopy(bparchment,NULL,NULL);
	gfx_FreeTexture(bparchment);

}
