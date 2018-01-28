#pragma once

#include <3ds.h>

void inp_ScanInput();

typedef struct
{
	bool pressed;
	bool held;
	bool released;
} Button;

Button 	btnUp,
		btnDown,
		btnLeft,
		btnRight,

		btnA,
		btnB,
		btnX,
		btnY,

		btnStart,
		btnSelect;