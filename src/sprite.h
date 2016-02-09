#ifndef _SPRITE_H__
#define _SPRITE_H__

#include "SDL.h"
#include "SDL_image.h"

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

void sprite_free(Sprite *sprite);
void sprite_close_system();
void sprite_initialize_system();
Sprite *sprite_load(char file[], int frameW, int frameH, SDL_Renderer *renderer);
void sprite_draw(Sprite *sprite, int frame, SDL_Renderer *renderer, int drawx, int drawy);


#endif
