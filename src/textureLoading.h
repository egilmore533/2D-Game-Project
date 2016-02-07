#ifndef _TEXTURE_LOADING_
#define _TEXTURE_LOADING_
#include <string.h>
#include "SDL_render.h"

typedef struct LTexture
{
	SDL_Texture *mTexture;			//the actual hardware texture
	
	int mWidth, mHeight;					//image dimesions
}LTexture;

void freeLTexture(LTexture *texture);
void renderLTexture(LTexture *texture, int x, int y, SDL_Renderer* gRenderer);
bool loadFromFile(LTexture *texture, char *path, SDL_Renderer* gRenderer);
int getWidth(LTexture *texture);
int getHeight(LTexture *texture);


#endif
