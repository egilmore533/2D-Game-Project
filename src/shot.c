#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "shot.h"

void allocShot(Shot *shot)
{
	int i;
	shot->mTexture = (LTexture *)malloc(sizeof(LTexture *));
	for(i = 0; i < 20 - 1; i++)
	{
		allocParticle(shot->particles[i]);
	}
}

void addShot(Shot *shot)
{
	int i;
	shot->mPosX = 0;
	shot->mPosY = 0;

	shot->mVelX = 0;
	shot->mVelY = 0;

	for(i =0; i < 20 - 1; i++)
	{
		addParticle(shot->particles[i], shot->mPosX, shot->mPosY);
	}
}

void removeShot(Shot *shot)
{
	int i;
	for(i = 0; i < 20 - 1; i++)
	{
		freeParticle(shot->particles[i]);
	}
	freeLTexture(shot->mTexture);
}

void renderShot(Shot *shot, SDL_Renderer *gRenderer)
{
	loadFromFile(shot->mTexture, "images/shot.png");
	renderLTexture(shot->mTexture, shot->mPosX, shot->mPosY);

	renderParticles(shot, gRenderer);
}

void renderParticles(Shot *shot, SDL_Renderer *gRenderer)
{
	int i;
	for(i = 0; i < 20 - 1; i++)
	{
		if(isDeadParticle(shot->particles[i]))
		{
			freeParticle(shot->particles[i]);
			addParticle(shot->particles[i], shot->mPosX, shot->mPosY); 
		}
	}

	for(i = 0; i < 20 - 1; i++)
	{
		renderParticle(shot->particles[i]);//this needs to be moved now that I moved Particles stuff into graphics
	}
}

