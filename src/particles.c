#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "particles.h"
#include "textureLoading.h"

//Scene textures
static LTexture *gRedTexture;
static LTexture *gGreenTexture;
static LTexture *gBlueTexture;

void loadMedia(LTexture *red, LTexture *green, LTexture *blue)
{
	gRedTexture = red;
	gGreenTexture = green;
	gBlueTexture = blue;
}

//used to construct a particle
void particle(Particle *particle, int x, int y)
{
	//set the offsets
	particle->mPosX = x - 5 + ( rand() % 25);
	particle->mPosY = y - 5 + ( rand() % 25);

	//initialize animation
	particle->mFrame = rand() % 5;

	//set type of particle
	switch( rand() % 3)
	{
		case 0: particle->mTexture = gRedTexture; break;
		case 1: particle->mTexture = gGreenTexture; break;
		case 2: particle->mTexture = gBlueTexture; break;
	}
}

void renderParticle(Particle *particle, SDL_Renderer *gRenderer)
{
	//show image
	renderLTexture(particle->mTexture, particle->mPosX, particle->mPosY);
	
	//renderLTexture(gShimmerTexture, particle->mPosX, particle->mPosY);

	//show shimmer
	if(particle->mFrame % 2 == 0)
	{
		
	}

	particle->mFrame++;
}

//after the particle has rendered for its max frames mark it as dead
bool isDeadParticle(Particle *particle)
{
	return particle->mFrame > 10;
}

void freeParticle(Particle *particle)
{
	freeLTexture(particle->mTexture);
}
