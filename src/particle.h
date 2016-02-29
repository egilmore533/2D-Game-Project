#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "sprite.h"
#include "entity.h"

typedef struct Particles
{
	Vect2d position;				//Offsets X and Y
	int inUse;
	int frame;
	Sprite *sprite;				//Type of particle

}Particle;

void particle_free(Particle **particle);
void particle_close_system();
void particle_initialize_system(int maxParticle);
Particle *particle_new();
Particle *particle_load(Particle *particle, Entity *generator);
int particle_dead(Particle *particle);
void particle_check_all_dead();
void particle_draw_all();

#endif
