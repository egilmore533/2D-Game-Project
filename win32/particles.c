#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "particles.h"

void particle(Particle *particle, int x, int y)
{
	//set the offsets
	particle->mPosX = x - 5 + ( rand() % 25);
	particle->mPosY = y - 5 + ( rand() % 25);

	//initialize animation
	particle->mFrame = rand() % 5;

	switch( rand() % 3)
	{
		case 0: break;
		case 1: break;
		case 2: break;
	}
}
