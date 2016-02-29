#include "particle.h"
#include "simple_logger.h"
#include <stdlib.h>

static Particle *particleList = NULL;
static int particleMax;
static int particleNum;
static Sprite *red_particle;

void particle_free(Particle **particle)
{
	Particle *self;
	if(!particle)
	{
		return;
	}
	if(!*particle) 
	{
		return;
	}
	self = *particle;
	self->inUse--;
	particleNum--;

	*particle = NULL;
}

void particle_close_system()
{
	int i;
	Particle *particle;
	if(!particleList)
	{
		slog("entityList not initialized");
		return;
	}
	for(i = 0; i < particleMax; ++i)
	{
		particle = &particleList[i];
		particle_free(&particle);
	}
	free(particleList);
	particleList = NULL;
}

void particle_initialize_system(int maxParticle)
{
	int i;
	if(maxParticle == 0)
	{
		slog("maxParticle == 0");
		return;
	}
	particleList = (Particle *) malloc (sizeof (Particle) * maxParticle);
	if(!particleList)
	{
		slog("failed to initialize particleList");
		return;
	}
	memset(particleList, 0, sizeof (Particle) * maxParticle);
	for(i = 0; i < maxParticle; ++i)
	{
		particleList[i].sprite = NULL;
	}
	particleMax = maxParticle;
	red_particle = sprite_load("images/redSpark.png", 32, 32, 16);
	atexit(particle_close_system);
}

Particle *particle_new()
{
	int i;
	/*makesure we have the room for a new sprite*/
	if(particleNum + 1 > particleMax)
	{
		slog("Maximum Particle's Reached.");
		exit(1);
	}
	for(i = 0; i < particleMax; i++)
	{
		if(particleList[i].inUse)
		{
			continue;
		}
		memset(&particleList[i],0,sizeof(Particle));
		particleList[i].inUse = 1;
		particleNum++;
		return &particleList[i];
	}
	return NULL;
}

Particle *particle_load(Particle *particle, Entity *generator)
{
	particle->position.x = generator->position.x - 5 + ( rand() % 25);
	particle->position.y = generator->position.y - 5 + ( rand() % 25);
	particle->sprite = red_particle; // only supports particles for pep's spice
	particle->frame = (rand() % 5);
	return particle;
}

int particle_dead(Particle *particle)
{
	if(particle->frame >= 30)
	{
		return 1;
	}
	return 0;
}

void particle_check_all_dead()
{
	int i;
	Particle *particle; // stores address of the entlist address for freeing
	for(i = 0; i < particleMax; i++)
	{
		if(!particleList[i].inUse)
		{
			continue;
		}
		if(particle_dead(&particleList[i]))
		{
			particle = &particleList[i];
			particle_free(&particle);
		}
	}
}

void particle_draw_all()
{
	int i;
	for(i = 0; i < particleMax; i++)
	{
		if(!particleList[i].inUse)
		{
			continue;
		}
		sprite_draw(particleList[i].sprite, particleList[i].frame, particleList[i].position);
		particleList[i].frame++;
	}
}
