#pragma once

#include <citro3d.h>

typedef struct
{
	int x, y, w, h;
} Rect;

typedef struct
{
	unsigned char r, g, b;
} RGB;

typedef struct
{
	int w, h;
	C3D_Tex* data;
} Texture;

void gfx_Init();
void gfx_Exit();

Texture* gfx_LoadTexture(char* fname, RGB* colorKey);
void gfx_FreeTexture(Texture* tex);

void gfx_Clear();
void gfx_Flip();

void gfx_RenderCopy(Texture* in, Rect* src, Rect* dst);