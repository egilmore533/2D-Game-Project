#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "entity.h"
#include "simple_logger.h"

/**
 * @brief	sets up the bullet for use by the entity specific weapon function.
 * @param [in,out]	owner	the bullet entity.
 * @return	null if it fails, else a loaded bullet.
 */

Entity *weapon_fire(Entity *owner);

/**
 * @brief	basic think that checks if the bullet is out of the camera's bounds and then free's it if outside.
 * @param [in,out]	spice	If non-null, the spice.
 */
void weapon_think(Entity *shot);

/**
 * @brief	frees the bullet's data members.
 * @param [in,out]	spice	the bullet entity.
 */
void weapon_free(Entity *shot);

/**
 * @brief	update the bullet's position.
 * @param [in,out]	spice	If non-null, the spice.
 */
void weapon_update(Entity *shot);


/*
Player specific weapon code
*/

/**
 * @brief	loads the bullet to pep's position with offsets specific for pep, loads the sprite, and sets its think and touch to pep's specific weapon think and weapon touch.
 * @param [in,out]	player	If non-null, the player.
 */
void weapon_pep_fire(Entity *player);

/**
 * @brief	think that creates a particle for pep's spice shot and test's if the shot is out of the camera's bounds, deletes if so.
 * @param [in,out]	spice	the bullet.
 */
void weapon_pep_think_particle(Entity *spice);

/**
 * @brief	collision behavior for pep's bullet with other ents.
 * @param [in,out]	spice	the bullet.
 * @param [in,out]	other	whats touching the bullet.
 */
void weapon_pep_touch(Entity *spice, Entity *other);

void weapon_pep_bomb(Entity *player);
void weapon_pep_bomb_think(Entity *bomb);


 /*
 melt firing section
  */

/**
 * @brief	Weapon melt fire.
 * @param [in,out]	entity	If non-null, the entity.
 */
void weapon_melt_fire(Entity *melt);
void weapon_melt_think_particle(Entity *cream);
void weapon_melt_think(Entity *cream);
void weapon_melt_update(Entity *cream);
void weapon_melt_touch(Entity *cream, Entity *other);


 /*
 professor slice firing section
  */

void weapon_professor_slice_fire(Entity *professor_slice);
void weapon_professor_slice_think_particle(Entity *bread);
void weapon_professor_slice_think(Entity *bread);
void weapon_professor_slice_update(Entity *bread);
void weapon_professor_slice_touch(Entity *bread, Entity *other);

#endif
