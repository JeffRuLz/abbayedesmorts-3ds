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



/*

#include <string>

typedef struct
{
	unsigned char r, g, b;
} RGB;

RGB gfx_NewRGB(unsigned char r, unsigned char g, unsigned char b);

class Surface
{
public:
	Surface()
	{
		w = -1;
		h = -1;
		data = nullptr;
	}
	Surface(std::string fname);
	~Surface();
	
	int w;
	int h;
	
	void* data;
};


void gfx_FrameStart();
void gfx_FrameEnd();

//Event that occurs when the screen is resized
//Rarely needed for console ports
void gfx_ScreenResized();

void gfx_DrawSurface(Surface* surf, float x, float y);
void gfx_DrawSurfacePart(Surface* surf, float x, float y, int cx, int cy, int w, int h);

void gfx_DrawRectangle(float x, float y, int w, int h, RGB c);*/