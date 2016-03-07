#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "entity.h"
#include "simple_logger.h"

/**
 * @brief	loads the bullet by allocating memory and setting its position and velocity to make 
 * 			it visually consistent with Pep's sprite, also sets the bullet's owner.
 * @param [in,out]	entity	the bullet entity.
 */
void weapon_fire(Entity *entity);

/**
 * @brief	think creates a particle and check's if the bullet is out of the camera's bounds, if it is free it.
 * @param [in,out]	spice	the bullet.
 */
void weapon_think_particle(Entity *spice);

void weapon_think(Entity *spice);

/**
 * @brief	frees the bullet's data members.
 * @param [in,out]	spice	the bullet entity.
 */
void weapon_free(Entity *spice);

/**
 * @brief	update the bullet's position.
 * @param [in,out]	spice	If non-null, the spice.
 */
void weapon_update(Entity *spice);

/**
 * @brief	collision behavior.
 * @param [in,out]	spice	the bullet.
 * @param [in,out]	other	whats touching the bullet.
 */
void weapon_touch(Entity *spice, Entity *other);

#endif
