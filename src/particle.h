#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include "sprite.h"
#include "entity.h"

/** @file	particle.h
 *	@brief	Particle System, handles randomly loading particles and killing them after cycling through their animation
 */


/**
 * @struct	Particle structure
 * @brief	Defines the particles to be a sprite with a position, frame number, and usage flag. 
 */
typedef struct Particle_s
{
	Vect2d position;					/**< the position of the particle */
	Vect2d velocity;					/**< the velocity of the particle (if needed) */
	int inUse;							/**< the usage flag */
	int frame;							/**< frame number of the particle, dies after the frame excceds 30 */
	Sprite *sprite;						/**< the particle's sprite */
	void (*think) (Particle_s *self);	/**< the think function, if needed of the particle*/

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
 * @brief loads a number of randomly created particles using a generator to give it a position and randomly changing it slightly based on frameSize of the generator
 * @param [in,out]	generator	the entity that will be the basis for this particle's position generation
 * @param numParticles			the number of particles that will be created
 */
void particle_bundle_load(Entity *generator, int numParticles);

void particle_think(Particle *particle);

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

/** @brief checks all particles and makes them think if they have a think function */
void particle_think_all();

/**
 * @brief generates a particle randomly based on its generators position and returns it if further use is required, used for broad particle effects where position is less important
 * @param [in,out] generator		the particle's, generator
 * @return null if it fails, else a pointer to a fully loaded particle.
 */
Particle *particle_assumed_position_load(Entity *generator);

/**
 * @brief generates a particle in a more precise location and returns it if further use is required, used for trail effects
 * @param [in,out] generator		the particle's, generator
 * @param offsets					the offset that will be used to position the particle slightly more accurately
 * @return null if it fails, else a pointer to a fully loaded particle with a precise location.
 */
Particle *particle_exact_position_load(Entity *generator, Vect2d offsets);

#endif
