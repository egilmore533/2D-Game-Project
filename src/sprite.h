#ifndef _SPRITE_H__
#define _SPRITE_H__

#include "SDL.h"
#include "SDL_image.h"

/**
* @brief Sprite structure used to hold texture, filename, frame dimensions, total image dimensions and the number of frames
*/
typedef struct Sprite_t
{
	SDL_Texture *image;		//means we loaded an image from a disk, have a way to display it, have a texture of appropriate size
	int imageW;
	int imageH;
	int framesPerLine;
	int frameW;
	int frameH;
	int refCount; 				//memset the array to all be 0 when you load a rocket refCount++ 
	char filename[128];

}Sprite;

/**
 * @brief	removes one reference from spriteList, and frees the sprite from spriteList if the refCount is 0
 * @param [in,out]	sprite that is no longer being referenced
 */
void sprite_free(Sprite *sprite);


/** @brief	closes the sprite system by freeing the entire sprite list and setting the number of sprites in the list to 0*/
void sprite_close_system();


/** @brief	initializes the sprite system by allocating memory for the sprite list and setting each sprite's image to NULL */
void sprite_initialize_system();

/**
 * @brief	loads a given filename to be a sprite, given an already loaded sprite it will add to the refCount of that sprite
 * 			 and reuse the Sprite, ends execution if the sprite limit has been reached
 * @param	file				The file to be used as a sprite.
 * @param	frameW				Width of each sprite in the image.
 * @param	frameH				Height of each sprite in the image.
 * @param [in,out]	renderer	If non-null, the renderer that the sprite will be rendered to.
 * @return	null if it fails, else a Sprite*.
 */
Sprite *sprite_load(char file[], int frameW, int frameH, SDL_Renderer *renderer);

/**
 * @brief	draws the sprite to the given position on the renderer.
 * @param [in,out]	sprite  	If non-null, the sprite from the spriteList that will be rendered.
 * @param	frame				The frame that the sprite is currently on.
 * @param [in,out]	renderer	If non-null, the renderer that the sprite will be rendered to.
 * @param	drawx				The x coordinate that the sprite will be rendered to.
 * @param	drawy				The y coordinate that the sprite will be rendered to.
 */
void sprite_draw(Sprite *sprite, int frame, SDL_Renderer *renderer, int drawx, int drawy);


#endif
