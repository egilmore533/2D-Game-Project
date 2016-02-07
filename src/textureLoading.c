#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "textureLoading.h"
#include "SDL_Image.h"
#include "SDL.h"

bool loadFromFile(LTexture *texture, char *path, SDL_Renderer* gRenderer)
{
	//freeLTexture(texture);
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(path);
	if(loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if(newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
		}
		else
		{
			texture->mWidth = loadedSurface->w;
			texture->mHeight = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}

	texture->mTexture = newTexture;
	return texture->mTexture != NULL;
}

//basic deallocator for LTextures
void freeLTexture(LTexture *texture)
{
	//free texture if it exists
	if(texture->mTexture != NULL)
	{
		SDL_DestroyTexture( texture->mTexture );
        texture->mTexture = NULL;
        texture->mWidth = 0;
        texture->mHeight = 0;
	}
}

void renderLTexture(LTexture *texture, int x, int y, SDL_Renderer *gRenderer)
{
	//Set rendering space and render to screen
    SDL_Rect renderQuad = {x, y, texture->mWidth, texture->mHeight};
    SDL_RenderCopy(gRenderer, texture->mTexture, NULL, &renderQuad);
}

int getWidth(LTexture *texture)
{
	return texture->mWidth;
}

int getHeight(LTexture *texture)
{
	return texture->mHeight;
}


