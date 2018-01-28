/* game.h */

#pragma once

# include <unistd.h>
# include "base.h"

# include "structs.h"

void keybpause (uint *keyp);
void music (uint room[],Music *bso[],uint *changeflag,int flag);
void changescreen (struct hero *jean,uint room[],uint *changeflag);
void events (struct hero *jean,uint stagedata[][22][32],uint room[],uint counter[],struct enem *enemies,Sound *fx[]);
void control (struct hero *jean,uint *keyp);
void counters (uint counter[]);
void animation (uint stagedata[][22][32],uint room[],uint counter[]);

/* enemies */
void blueparchment (struct hero *jean);
void redparchment (struct hero *jean);
void satan (struct enem *enemies,Texture *tiles,uint counter[],float proyec[],Sound *fx[],uint changetiles);
void death (struct enem *enemies,Texture *tiles,uint counter[],float proyec[],uint stagedata[][22][32],Sound *fx[],uint changetiles);
void fireball (struct enem *enemies,Texture *tiles,uint counter[],struct hero jean,uint stagedata[][22][32], uint changetiles);
void plants (struct enem *enemies,Texture *tiles,uint counter[],float proyec[],Sound *fx[],uint changetiles);
void dragon (struct enem *enemies,Texture *tiles,uint counter[],float proyec[],Sound *fx[],uint changetiles);
void crusaders (struct enem *enemies,Texture *tiles,uint counter[],uint room[],uint changetiles);
void movenemies (struct enem *enemies,uint stagedata[][22][32],uint counter[],float proyec[],struct hero jean,Sound *fx[]);
void drawenemies (struct enem *enemies,Texture *tiles,Sound *fx[],uint changetiles);
void searchenemies (uint room[], struct enem *enemies,uint *changeflag, int enemydata[][7][15]);

/* drawing */
void drawrope (struct enem enemies,Texture *tiles,uint changetiles);
void drawshoots (float proyec[],Texture *tiles,struct enem *enemies,uint changetiles);
void drawscreen (uint stagedata[][22][32],Texture *tiles,uint room[],uint counter[],uint changeflag,Sound *fx[],uint changetiles);
void statusbar (Texture *tiles,uint room[],int lifes,int crosses,Texture *fonts,uint changetiles);
void showparchment (uint *parchment);

/* loading */
void loadparchment(uint *parchment);
void loadingmusic(Music *bso[],Sound *fx[]);
void loaddata(uint stagedata[][22][32],int enemydata[][7][15]);

/* jean */
void drawjean (Texture *tiles,struct hero *jean,uint counter[],Sound *fx[],uint changetiles);
void movejean (struct hero *jean, Sound *fx[]);
void touchobj (struct hero *jean,uint stagedata[][22][32],uint room[],uint *parchment,uint *changeflag,struct enem *enemies,float proyec[],Sound *fx[]);
void contact (struct hero *jean,struct enem enemies,float proyec[],uint room[]);
void collisions (struct hero *jean,uint stagedata[][22][32],uint room[]);
