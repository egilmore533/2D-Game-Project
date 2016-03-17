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

/** @brief example macro to return the largest of two values.
 * can be read as: if a greater than b then a, else b
 */
#define MAX(a,b) (a>b?a:b)

/** @brief example macro to return the smallest of two values.
 * can be read as: if a less than b then a, else b
 */
#define MIN(a,b) (a<b?a:b)

/**
 * @brief	initializes the main window and the main renderer.
 * @param [in,out]	windowName	If non-null, name of the window, will be displayed at the top of the window.
 * @param	viewWidth		  	Width of the view.
 * @param	viewHeight		  	Height of the view.
 * @param	renderWidth		  	Width of the render.
 * @param	renderHeight	  	Height of the render.
 * @param	bgcolor			  	The bgcolor.
 * @param	fullscreen		  	flag to use fullscreen or not.
 */
void graphics_initialize(char *windowName, int viewWidth, int viewHeight, int renderWidth, int renderHeight, int fullscreen);

/**
 * @brief	render SDL surface to screen.
 * @param [in,out]	surface	If non-null, the surface.
 * @param	srcRect		   	Source rectangle.
 * @param	x			   	The x coordinate.
 * @param	y			   	The y coordinate.
 */
void graphics_render_surface_to_screen(SDL_Surface *surface,SDL_Rect srcRect,int x,int y);


/** @brief	delay's frame rate so the screen and code are synched up properly */
void graphics_frame_delay();


/** @brief	goes to the next frame then holds for a frame delay. */
void graphics_next_frame();

/** @brief closes the window and the renderer at exit */
void g_graphics_close();

/**
 * @brief	getter for the game's renderer so the rest of the code can use it.
 * @return	a SDL_Renderer* used for all the game's rendering.
 */
SDL_Renderer *graphics_get_renderer();

#endif
