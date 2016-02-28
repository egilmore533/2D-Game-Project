#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "entity.h"
#include "simple_logger.h"
#include "particles.h"

/**
 * @brief	loads the bullet by allocating memory and setting its position and velocity to make 
 * 			it visually consistent with Pep's sprite.
 * @param [in,out]	entity	the bullet entity.
 */
void weapon_fire(Entity *entity);

/**
 * @brief	the bullet's think function.
 * @param [in,out]	spice	If non-null, the spice.
 */
void weapon_think(Entity *spice);

#endif
