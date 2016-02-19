#include "sprite.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "simple_logger.h"

Sprite *spriteList = NULL;
int spriteNum;
int spriteMax = 0;


void sprite_free(Sprite **sprite)
{
	Sprite *target;
	if(!sprite)
	{
		return;
	}
	if(!*sprite)
	{
		return;
	}
	target = *sprite;

	target->refCount--;
	if(target->refCount == 0)
	{
		strcpy(target->filename,"\0");
		
		/* anal */
		if(target->image != NULL)
		{
			SDL_DestroyTexture(target->image); 
			memset(target,0,sizeof(Sprite));
		}
	}
	*sprite = NULL;
}

void sprite_close_system()
{
	int i;
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
		printf("Max sprite == 0\n");
		return;
	}
	spriteList = (Sprite *)malloc(sizeof(Sprite) * maxSprite);
	memset(spriteList, 0, sizeof(Sprite) * maxSprite);
	spriteNum = 0;
	for(i = 0; i < maxSprite; ++i)
	{
		spriteList[i].image = NULL;
	}
	spriteMax = maxSprite;
	atexit(sprite_close_system);
}

Sprite *sprite_load(char file[], int frameW, int frameH, SDL_Renderer *renderer)
{
	int i;
	SDL_Surface *tempSurface;
	SDL_Texture *tempTexture;
	/*first search to see if the requested sprite image is alreday loaded*/
	for(i = 0; i < spriteNum; ++i)
	{
		if(strncmp(file, spriteList[i].filename, 128) ==0)
		{
			spriteList[i].refCount++;
			return &spriteList[i];
		}
	}
	/*makesure we have the room for a new sprite*/
	if(spriteNum + 1 >= spriteMax)
	{
		fprintf(stderr, "Maximum Sprites Reached.\n");
		exit(1);
	}
	/*if its not already in memory, then load it.*/
	spriteNum++;
	/*
	for(i = 0; i <= spriteNum; i++)
	{
		if(!spriteList[i].refCount)
			break;
	}
	*/
	tempSurface = IMG_Load(file);
	if(tempSurface == NULL)
	{
		fprintf(stderr,"unable to load sprite as a surface: %s\n",SDL_GetError());
		exit(0);
	}
	else
	{
		/*sets a transparent color for blitting.*/
		SDL_SetColorKey(tempSurface, SDL_TRUE , SDL_MapRGB(tempSurface->format, 255,255,255));
	
		tempTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
		if(tempTexture == NULL)
		{
			fprintf(stderr,"unable to load sprite as a Texture: %s\n",SDL_GetError());
			exit(0);
		}
	}
	
	spriteList[i].image = tempTexture;
	/*then copy the given information to the sprite*/
	strncpy(spriteList[i].filename,file,128);
	
	/*now sprites don't have to be 16 frames per line, but most will be.*/
	spriteList[i].framesPerLine = 16;
	spriteList[i].frameW = frameW;
	spriteList[i].frameH = frameH;
	spriteList[i].refCount++;
	SDL_FreeSurface(tempSurface);
	return &spriteList[i];
}


void sprite_draw(Sprite *sprite, int frame, SDL_Renderer *renderer, int drawx, int drawy)
{
	SDL_Rect source, destination;
	source.x = frame % sprite->framesPerLine * sprite->frameW;
	source.y = frame / sprite->framesPerLine * sprite->frameH;
	source.w = sprite->frameW;
	source.h = sprite->frameH;
	
	destination.x = drawx;
	destination.y = drawy;
	destination.w = sprite->frameW;
	destination.h = sprite->frameH;
	SDL_RenderCopy(renderer, sprite->image, &source, &destination);
}

