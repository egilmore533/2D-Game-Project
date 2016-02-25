#ifndef _GRAPHICS_
#define _GRAPHICS_
/*
 *			graphics.h
 *			Originaly written by Donald Kehoe for the NJIT Introduction to game development class
 *			This file contains data structures, constants and function prototypes needed to initialize SDL and
 *			to handle sprites and graphics.
 */


#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#define MAX(a,b) (a>b?a:b)
#define MIN(a,b) (a<b?a:b)

void Init_Graphics(
	char *windowName,
    int viewWidth,
    int viewHeight,
    int renderWidth,
    int renderHeight,
    float bgcolor[4],
    int fullscreen);

void g_graphics_render_surface_to_screen(SDL_Surface *surface,SDL_Rect srcRect,int x,int y);

void ResetBuffer();
void NextFrame();
void InitMouse();
void DrawMouse();
SDL_Renderer *get_renderer();

#endif
