#include "sprite.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "simple_logger.h"
#include "graphics.h"
#include "camera.h"

static Sprite *spriteList = NULL;
static int spriteNum;
static int spriteMax = 0;


void sprite_free(Sprite **sprite)
{
	Sprite *target;
	if(!sprite)
	{
		return;
	}
	else if(!*sprite)
	{
		return;
	}
	target = *sprite;

	target->refCount--;
	if(target->refCount == 0)
	{
		strcpy(target->filename,"\0");
		
		if(target->image != NULL)
		{
			SDL_DestroyTexture(target->image); 
			memset(target,0,sizeof(Sprite));
		}
		spriteNum--;
	}
	*sprite = NULL;
}

void sprite_close_system()
{
	int i;
	if(!spriteList)
	{
		slog("spriteList not initialized");
		return;
	}
	for(i = 0; i < spriteMax; ++i)
	{
		if(spriteList[i].image != 0)
		{
			SDL_DestroyTexture(spriteList[i].image);
		}
	}
	free(spriteList);
	spriteList = NULL;
	spriteNum = 0;
	spriteMax = 0;
}

void sprite_initialize_system(int maxSprite)
{
	int i;
	if(maxSprite == 0)
	{
		slog("Max sprite == 0");
		return;
	}
	spriteList = (Sprite *)malloc(sizeof(Sprite) * maxSprite);
	if(!spriteList)
	{
		slog("spriteList failed to initialize");
		return;
	}
	memset(spriteList, 0, sizeof(Sprite) * maxSprite);
	spriteNum = 0;
	for(i = 0; i < maxSprite; ++i)
	{
		spriteList[i].image = NULL;
	}
	spriteMax = maxSprite;
	atexit(sprite_close_system);
}

Sprite *sprite_load(char file[], int frameW, int frameH, int fpl)
{
	int i;
	SDL_Surface *tempSurface;
	SDL_Texture *tempTexture;
	Sprite *sprite = NULL;
	SDL_Renderer *renderer = graphics_get_renderer();

	if(!spriteList)
	{
		slog("spriteList uninitialized");
		return NULL;
	}
	/*first search to see if the requested sprite image is alreday loaded*/
	for(i = 0; i < spriteMax; i++)
	{
		if(spriteList[i].refCount == 0)
		{
			if(sprite == NULL)
				sprite = &spriteList[i];
			continue;
		}
		if(strncmp(file, spriteList[i].filename, 128) ==0)
		{
			spriteList[i].refCount++;
			return &spriteList[i];
		}
	}
	/*makesure we have the room for a new sprite*/
	if(spriteNum + 1 > spriteMax)
	{
		slog("Maximum Sprites Reached.");
		exit(1);
	}

	/*if its not already in memory, then load it.*/
	spriteNum++;
	tempSurface = IMG_Load(file);

	if(tempSurface == NULL)
	{
		slog("unable to load sprite as a surface");
		while(true) {}
		exit(0);
	}
	else
	{
		/*sets a transparent color for blitting.*/
		SDL_SetColorKey(tempSurface, SDL_TRUE , SDL_MapRGB(tempSurface->format, 255,255,255));
	
		tempTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
		if(tempTexture == NULL)
		{
			slog("unable to load sprite as a Texture");
			exit(0);
		}
	}
	
	sprite->image = tempTexture;
	/*then copy the given information to the sprite*/
	strncpy(spriteList[i].filename,file,128);
	
	/*now sprites don't have to be 16 frames per line, but most will be.*/
	sprite->framesPerLine = fpl;
	sprite->frameSize.x = frameW;
	sprite->frameSize.y = frameH;
	sprite->refCount++;
	SDL_FreeSurface(tempSurface);
	return sprite;
}


void sprite_draw(Sprite *sprite, int frame, Vect2d drawPos)
{
	Vect2d positionRelative;
	Entity *cam;
	SDL_Rect source, destination;
	SDL_Renderer *renderer = graphics_get_renderer();
	cam = camera_get();
	vect2d_subtract(drawPos, cam->position, positionRelative); 
	if(!sprite)
	{
		slog("sprite doesn't point to anything");
		return;
	}
	source.x = frame % sprite->framesPerLine * sprite->frameSize.x;
	source.y = frame / sprite->framesPerLine * sprite->frameSize.y;
	source.w = sprite->frameSize.x;
	source.h = sprite->frameSize.y;
	
	destination.x = positionRelative.x;
	destination.y = positionRelative.y;
	destination.w = sprite->frameSize.x;
	destination.h = sprite->frameSize.y;
	SDL_RenderCopy(renderer, sprite->image, &source, &destination);
}

