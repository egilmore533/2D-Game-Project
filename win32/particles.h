#ifndef _PARTICLES_
# define _PARTICLES_


#define TOTAL_PARTICLES  20;

typedef struct Particles
{
	int mPosX, mPosY;				//Offsets X and Y

	int mFrame;						//Current frame of Animation

	//LTexture *mTexture;				//Type of particle

}Particle;

void particle(Particle *particle, int x, int y);
void renderParticle(Particle *particle);
bool isDeadParticle(Particle *particle);


# endif
