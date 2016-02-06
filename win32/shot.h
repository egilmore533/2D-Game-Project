#ifndef _PARTICLES_
# define _PARTICLES_

#include <particles.h>

typedef struct Shot
{
	static const int SHOT_WIDTH, SHOT_HEIGHT;			//dimesions of Shot
	static const int DOT_VEL;							//max axis velocity of Shot
	
	Particle* particles [TOTAL_PARTICLES];				//the particles

	int mPosX, mPosY									//X and Y offsets of Shot
	int mVelX, mVelY;									//Velocity of Shot

}Shot;

void handleEventShot(Shot *shot, SDL_Event& e);
void moveShot(Shot *shot);
void renderShot(Shot *shot);
void renderParticles(Shot *shot);

# endif
