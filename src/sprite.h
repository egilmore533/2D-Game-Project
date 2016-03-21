#ifndef _SPRITE_H__
#define _SPRITE_H__

#include "SDL_image.h"
#include "vector.h"

/**
 * @brief	Sprite structure used to hold entire texture, filename, frame dimensions, texture
 * 			dimensions and the number of frames per line, and a reference count.
 */
typedef struct Sprite_t
{
	SDL_Texture *image;			/**< texture */
	Vect2d imageSize;			/**< x and y image dimensions */
	Vect2d frameSize;			/**< x and y dimensions of each frame */
	int framesPerLine;			/**< frames per line of the image */
	int refCount; 				/**< number of times this sprite has been referenced */
	char filename[128];			/**< filename for the image used to make the sprites */

}Sprite;

/**
 * @brief	removes one reference from spriteList, if the
 * 			refCount is 0 frees the sprite from spriteList and frees the sprite pointer.
 * @param [in,out]	sprite	double pointer to the sprite.
 */
void sprite_free(Sprite **sprite);


/** @brief	closes the sprite system by freeing the entire sprite list and setting the number of sprites in the list to 0*/
void sprite_close_system();


/** 
 *  @brief	initializes the sprite system by allocating memory for the sprite list and setting each sprite's image to NULL 
 *	@param maxSprite	the maximum number of sprite allowed in the game at a time
 */
void sprite_initialize_system(int maxSprite);

/**
 * @brief	loads a given file to be a sprite, unless already loaded which it will then raise the reference count and
 * 			 and reuse the Sprite, ends execution if the sprite limit has been reached, uses the first available slot in the spriteList.
 * @param	file  	The filepath to be used to load a sprite.
 * @param	frameW	Width of each sprite in the image.
 * @param	frameH	Height of each sprite in the image.
 * @param	fpl   	number of frames per line 
 * @return	null if it fails, else a Sprite pointer.
 */
Sprite *sprite_load(char file[], int frameW, int frameH, int fpl);

/**
 * @brief	draws a sprite to the renderer, finding its relative position to the camera, and the specific frame to draw on its texture
 * @param [in,out]	sprite  	If non-null, the sprite from the spriteList that will be rendered.
 * @param	frame				The frame that the sprite is currently on.
 * @param	drawPos				The x and y coordinates that the sprite will be rendered to.
 */
void sprite_draw(Sprite *sprite, int frame, Vect2d drawPos);


#endif
