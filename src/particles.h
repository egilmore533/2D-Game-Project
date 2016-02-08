#ifndef _PARTICLES_
#define _PARTICLES_

#include "graphics.h"

#define TOTAL_PARTICLES  20;

typedef struct Particles
{
	int mPosX, mPosY;;				//Offsets X and Y
	int mFrame;						//Current frame of Animation
	LTexture *mTexture;				//Type of particle

}Particle;

void loadMedia(LTexture *red, LTexture *green, LTexture *blue);
void particle(Particle *particle, int x, int y);
void renderParticle(Particle *particle, SDL_Renderer *gRenderer);
bool isDeadParticle(Particle *particle);
void freeParticle(Particle *particle);


# endif
