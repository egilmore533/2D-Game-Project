#ifndef _SHOT_
#define _SHOT_

#include "SDL_events.h"
#include "graphics.h"
#include <stdlib.h>

typedef struct Shot
{
	static const int SHOT_WIDTH = 20;
	static const int SHOT_HEIGHT = 20;					//dimesions of Shot
	static const int DOT_VEL = 10;						//max axis velocity of Shot
	
	Particle *particles[20];// = (Particle *) malloc(20 * sizeof Particle *);							//the particles (I need to figure out how to get it to be TOTAL_PARTICLES instead of 20)

	int mPosX, mPosY;									//X and Y offsets of Shot
	int mVelX, mVelY;									//Velocity of Shot

	LTexture *mTexture;									//Type of shot

}Shot;

void allocShot(Shot *shot);
void addParticles(Shot *shot);
void addShot(Shot *shot);
void removeShot(Shot *shot);
void handleEventShot(Shot *shot, SDL_Event& e);
void moveShot(Shot *shot);
void renderShot(Shot *shot);
void renderParticles(Shot *shot, SDL_Renderer *gRenderer);

# endif
