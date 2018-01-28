/* loading.c */

# include "base.h"

void loaddata(uint stagedata[][22][32],int enemydata[][7][15]) {

	FILE *datafile = NULL;
	uint8_t line[129],temp[4],line2[61];
	temp[3] = 0;

	/* Loading stage data file */
	datafile = fopen("romfs:/data/map.txt", "r");
	fgets (line, 129, datafile);
	fgets (line, 129, datafile);

	/* Loading data into the array */
	for (uint8_t i=0; i<=24; i++) {
		for (uint8_t j=0; j<=21; j++) {
			for (uint8_t k=0; k<=31; k++) {
				temp[0] = line[k*4];
				temp[1] = line[(k*4) + 1];
				temp[2] = line[(k*4) + 2];
				sscanf (temp, "%d", &stagedata[i][j][k]);
			}
			fgets (line, 129, datafile);
		}
		fgets (line, 129, datafile);
	}

	/* Closing file */
	fclose (datafile);

	/* Loading enemies data file */
	datafile = fopen("romfs:/data/enemies.txt", "r");
	fgets (line2, 61, datafile);
	fgets (line2, 61, datafile);

	/* Loading data into the array */
	for (uint8_t i=0; i<=24; i++) {
		for (uint8_t j=0; j<7; j++) {
			for (uint8_t k=0; k<15; k++) {
				temp[0] = line2[k*4];
				temp[1] = line2[(k*4) + 1];
				temp[2] = line2[(k*4) + 2];
				sscanf (temp, "%d", &enemydata[i][j][k]);
			}
			fgets (line2, 61, datafile);
		}
		fgets (line2, 61, datafile);
	}

	/* Closing file */
	fclose (datafile);

}

void loadingmusic(Music *bso[],Sound *fx[]) {

	/* Musics */
	bso[0] = aud_LoadMusic("/sounds/PrayerofHopeN.wav");
	bso[1] = aud_LoadMusic("/sounds/AreaIChurchN.wav");
	bso[2] = aud_LoadMusic("/sounds/GameOverV2N.wav");
	bso[3] = aud_LoadMusic("/sounds/HangmansTree.wav");
	bso[4] = aud_LoadMusic("/sounds/AreaIICavesV2N.wav");
	bso[5] = aud_LoadMusic("/sounds/EvilFightN.wav");
	bso[6] = aud_LoadMusic("/sounds/AreaIIIHellN.wav");
	bso[7] = aud_LoadMusic("/sounds/ManhuntwoodN.wav");

	/* Fxs */
	fx[0] = aud_LoadSound("/sounds/shoot.wav");
	fx[1] = aud_LoadSound("/sounds/doorfx.wav");
	fx[2] = aud_LoadSound("/sounds/Item.wav");
	fx[3] = aud_LoadSound("/sounds/jump.wav");
	fx[4] = aud_LoadSound("/sounds/slash.wav");
	fx[5] = aud_LoadSound("/sounds/mechanismn.wav");
	fx[6] = aud_LoadSound("/sounds/onedeathn.wav");

}
