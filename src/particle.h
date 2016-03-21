#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "sprite.h"
#include "entity.h"


/** @brief	Defines the particles to be a sprite with a position, frame number, and usage flag. */
typedef struct Particles
{
	Vect2d position;				/**< the position of the particle */
	int inUse;						/**< the usage flag */
	int frame;						/**< frame number of the particle, dies after the frame excceds 30 */
	Sprite *sprite;					/**< the particle's sprite */

}Particle;

/**
 * @brief	frees the particle's sprite and then frees the pointer to the particle.
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
 * @brief	creates a particle in the first free space in particleList, ends execution if there isn't room for another particle.
 * @return	null if it fails, else a pointer to the first available particle in the particle list.
 */
Particle *particle_new();

/**
 * @brief	generates a particle in a random position near the generator with a random frame number and a random particle sprite.
 * @param [in,out]	particle 	If non-null, the particle that needs to be generated.
 * @param [in,out]	generator	If non-null, the source that the particle is coming from.
 * @param	offsets			 	offsets defined by each generator as needed to make the particles look visually correct.
 * @return	null if it fails, else a Particle*.
 */

Particle *particle_load(Particle *particle, Entity *generator, Vect2d offsets);

/**
 * @brief	checks if a particle has reached it's last frame
 * @param [in,out]	particle	If non-null, the particle to check.
 * @return	true if the particle is at or above its last frame, else false.
 */
int particle_dead(Particle *particle);


/** @brief	checks every particle in particleList with particle_dead. */
void particle_check_all_dead();


/** @brief	draws every particle to the screen using sprite draw, this needs to be used because particles aren't entities and camera won't draw them */
void particle_draw_all();

#endif
