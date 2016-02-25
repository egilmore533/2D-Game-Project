#ifndef _SPRITE_H__
#define _SPRITE_H__

#include "SDL.h"
#include "SDL_image.h"
#include "vector.h"

/**
 * @brief	Sprite structure used to hold texture, filename, frame dimensions, image
 * 			dimensions and the number of frames per line, and a reference count.
 */
typedef struct Sprite_t
{
	SDL_Texture *image;			/**< actual texture*/
	Vect2d imageSize;			/**< x and y image dimensions*/
	Vect2d frameSize;			/**< x and y frame dimensions*/
	int framesPerLine;			/**< frames per line of the image*/
	int refCount; 				/**< number of times this sprite has been referenced*/
	char filename[128];			/**< filename for this sprite*/

}Sprite;

/**
 * @brief	removes one reference from spriteList, and frees the sprite from spriteList if the
 * 			refCount is 0. also frees the pointer to the sprite (thats why pointer to a pointer)
 * @param [in,out]	sprite	that is no longer being referenced.
 */

void sprite_free(Sprite **sprite);


/** @brief	closes the sprite system by freeing the entire sprite list and setting the number of sprites in the list to 0*/
void sprite_close_system();


/** @brief	initializes the sprite system by allocating memory for the sprite list and setting each sprite's image to NULL */
void sprite_initialize_system(int maxSprite);

/**
 * @brief	loads a given filename to be a sprite, given an already loaded sprite it will add to
 * 			the refCount of that sprite
 * 			 and reuse the Sprite, ends execution if the sprite limit has been reached.
 * @param	file  	The file to be used as a sprite.
 * @param	frameW	Width of each sprite in the image.
 * @param	frameH	Height of each sprite in the image.
 * @param	fpl   	number of frames per line (usually 16)
 * @return	null if it fails, else a Sprite*.
 */
Sprite *sprite_load(char file[], int frameW, int frameH, int fpl);

/**
 * @brief	draws the sprite to the given position on the renderer.
 * @param [in,out]	sprite  	If non-null, the sprite from the spriteList that will be rendered.
 * @param	frame				The frame that the sprite is currently on.
 * @param [in,out]	renderer	If non-null, the renderer that the sprite will be rendered to.
 * @param	drawx				The x coordinate that the sprite will be rendered to.
 * @param	drawy				The y coordinate that the sprite will be rendered to.
 */
void sprite_draw(Sprite *sprite, int frame, Vect2d drawPos);


#endif
