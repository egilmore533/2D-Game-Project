#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "sprite.h"
#include "entity.h"


/** @brief	Defines the particles to be a sprite with a position, frame number, and usage flag. */
typedef struct Particles
{
	Vect2d position;				/**< the position of the particle */
	int inUse;						/**< the usage flag */
	int frame;						/**< frame number of teh particle */
	Sprite *sprite;					/**< the particle's sprite */

}Particle;

/**
 * @brief	free's the particle's sprite and then frees the pointer to the particle.
 * @param [in,out]	particle	If non-null, the particle.
 */
void particle_free(Particle **particle);


/** @brief	goes through entire particle list freeing every particle and then freeing the particleList pointer. */
void particle_close_system();

/**
 * @brief	initializes the particleList by allocating memory for a given number of particles
 * @param	maxParticle	The maximum number of particles for the system and how much space to allocate for the system.
 */
void particle_initialize_system(int maxParticle);

/**
 * @brief	allocates memory for a particle creates a particle in the first free space in particleList.
 * @return	null if it fails, else a Particle pointer.
 */
Particle *particle_new();

/**
 * @brief	randomly generates a particle in a position near the generator.
 * @param [in,out]	particle 	If non-null, the particle that needs to be generated.
 * @param [in,out]	generator	If non-null, the source that the particle is coming from.
 * @param	offsets			 	offsets defined by each generator as needed to make the particles look visually correct.
 * @return	null if it fails, else a Particle*.
 */

Particle *particle_load(Particle *particle, Entity *generator, Vect2d offsets);

/**
 * @brief	checks if the particle has reached it's last frame
 * @param [in,out]	particle	If non-null, the particle to check.
 * @return	An int.
 */
int particle_dead(Particle *particle);


/** @brief	checks every partile in particleList with particle_dead. */
void particle_check_all_dead();


/** @brief	draws every particle in particleList that is in use nad iterates goes to the next frame. */
void particle_draw_all();

#endif
