#include "particle.h"
#include "simple_logger.h"
#include "camera.h"
#include "files.h"
#include <stdlib.h>

static Particle *particleList = NULL;	/**< the list of active particles */
static int particleMax;					/**< the maximum number of particles allowed for the game */
static int particleNum;					/**< the number of particles currently running */
static Sprite *red_particle;			/**< statically stored sprite for particles, if I want different particle's I will have to store their sprite's similarly and randomly select which sprite to use */
static Sprite *green_particle;
static Sprite *blue_particle;

void particle_free(Particle **particle)
{
	Particle *self;
	if(!particle)
	{
		slog("particle isn't pointing to anything");
		return;
	}
	else if(!*particle) 
	{
		slog("particle pointer isn't pointing to anything");
		return;
	}
	self = *particle;
	self->inUse--;
	particleNum--;
	// do not free sprite because each particle is using the same sprites
	memset(self, 0, sizeof (Particle));
}

void particle_close_system()
{
	int i;
	Particle *particle;
	if(!particleList)
	{
		slog("particleList not initialized");
		return;
	}
	for(i = 0; i < particleMax; ++i)
	{
		particle = &particleList[i];
		particle_free(&particle);
	}
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
	red_particle = sprite_load(SPICE_PARTICLE_1_SPRITE, 32, 32, 16);
	green_particle = sprite_load(SPICE_PARTICLE_2_SPRITE, 32, 32, 16);
	blue_particle = sprite_load(SPICE_PARTICLE_3_SPRITE, 32, 32, 16);
	atexit(particle_close_system);
}

Particle *particle_new()
{
	int i;
	if(!particleList)
	{
		slog("particleList not yet initialized");
		return NULL;
	}
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


Particle *particle_exact_position_load(Entity *generator, Vect2d offsets)
{
	Particle *particle;
	if(!generator)
	{
		slog("generator doesn't point to anything");
		return NULL;
	}
	particle = particle_new();
	particle->position.x = (generator->position.x - 5 + ( rand() % 25)) + offsets.x;
	particle->position.y = (generator->position.y - 5 + ( rand() % 25)) + offsets.y;
	particle->frame = (rand() % 30); // make this number higher to make it appear slightly more random, and better looking overall, still need to slow down the generation in the think functions

	switch( rand() % 3 )
	{
		case 1:
			particle->sprite = red_particle; // this should be what it always is for pep's spice but why not do something dumb for no reason
			break;
		case 2:
			particle->sprite = green_particle;
			break;
		case 0:
			particle->sprite = blue_particle;
			break;
	}

	return particle;
}

Particle *particle_assumed_position_load(Entity *generator)
{
	Particle *particle;
	particle = particle_new();
	particle->position.x = (generator->position.x + (rand() % (int) (generator->sprite->frameSize.x)));
	particle->position.y = (generator->position.y + (rand() % (int) (generator->sprite->frameSize.y)));
	particle->frame = (rand() % 30);

	switch( rand() % 3 )
	{
		case 1:
			particle->sprite = red_particle; // this should be what it always is for pep's spice but why not do something dumb for no reason
			break;
		case 2:
			particle->sprite = green_particle;
			break;
		case 0:
			particle->sprite = blue_particle;
			break;
	}
	return particle;
}

void particle_bundle_load(Entity *generator, int numParticles)
{
	Particle *particle;
	int i;
	for(i = 0; i < numParticles; i++)
	{
		particle = particle_assumed_position_load(generator);
	}
	return;
}

int particle_dead(Particle *particle)
{
	if(!particle)
	{
		slog("particle doesn't point to anything");
		return NULL;
	}
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
	if(!particleList)
	{
		slog("particleList not yet initialized");
		return;
	}
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
	if(!particleList)
	{
		slog("particleList not yet initialized");
		return;
	}
	for(i = 0; i < particleMax; i++)
	{
		if(!particleList[i].inUse)
		{
			continue;
		}
		sprite_draw(particleList[i].sprite, particleList[i].frame, particleList[i].position);
		particleList[i].frame++; //no update so handle frame changes here
	}
}
