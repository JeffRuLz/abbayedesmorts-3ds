#include "input.h"
#include <3ds.h>

static u32 kDown, kHeld, kUp;
/*
Button 	btnUp,
	  	btnDown,
	  	btnLeft,
	  	btnRight,

	  	btnAccept,
	  	btnDecline,

	  	btnJump,
	  	btnAttack,
	  	btnWeapon,

	  	btnStart,
	  	btnSelect,

	  	btnL,
	 	btnR;*/

static void updateKey(Button* btn, u32 key)
{
	btn->pressed = kDown & key;
	btn->held = kHeld & key;
	btn->released = kUp & key;
}

void inp_ScanInput()
{
	hidScanInput();
	kDown = hidKeysDown();
	kHeld = hidKeysHeld();
	kUp = hidKeysUp();

	updateKey(&btnUp, KEY_UP);
	updateKey(&btnDown, KEY_DOWN);
	updateKey(&btnLeft, KEY_LEFT);
	updateKey(&btnRight, KEY_RIGHT);

	updateKey(&btnA, KEY_A);
	updateKey(&btnB, KEY_B);
	updateKey(&btnX, KEY_X);
	updateKey(&btnY, KEY_Y);

	updateKey(&btnStart, KEY_START);
	updateKey(&btnSelect, KEY_SELECT);
}