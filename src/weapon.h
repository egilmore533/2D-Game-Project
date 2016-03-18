#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "entity.h"
#include "simple_logger.h"

/**
 * @brief	sets up the weapon for use by the entity specific weapon function.
 * @param [in,out]	owner	the weapon's owner entity.
 * @return	null if it fails, else a loaded weapon.
 */

Entity *weapon_fire(Entity *owner);

/**
 * @brief	basic think that checks if the weapon is out of the camera's bounds and then free's it if outside.
 * @param [in,out]	shot	If non-null, the shot.
 */
void weapon_think(Entity *shot);

/**
 * @brief	frees the weapon's data members.
 * @param [in,out]	shot	the shot entity.
 */
void weapon_free(Entity *shot);

/**
 * @brief	update the weapon's position by adding the velocity to the position.
 * @param [in,out]	shot	If non-null, the shot.
 */
void weapon_update(Entity *shot);


/*
Player specific weapon code
*/

void weapon_pep_spread_fire(Entity *player);
void weapon_pep_spread_touch(Entity *spread, Entity *other);


/**
 * @brief	loads the bullet to pep's position with offsets specific for pep, loads the sprite, and sets its think and touch to pep's specific weapon think and weapon touch.
 * @param [in,out]	player	If non-null, the player.
 */
void weapon_pep_charge_fire(Entity *player);

/**
 * @brief	think that creates a particle for pep's spice shot and test's if the shot is out of the camera's bounds, deletes if so.
 * @param [in,out]	spice	the bullet.
 */
void weapon_pep_think(Entity *spice);

/**
 * @brief	collision behavior for pep's bullet with other ents.
 * @param [in,out]	spice	the bullet.
 * @param [in,out]	other	whats touching the bullet.
 */
void weapon_pep_charge_touch(Entity *spice, Entity *other);

void weapon_pep_bomb(Entity *player);
void weapon_pep_bomb_think(Entity *bomb);
void weapon_pep_bomb_touch(Entity *bomb, Entity *other);


 /*
 melt firing section
  */

/**
 * @brief	melt's firing function, its a simple bullet that travels across the screen at a steady velocity
 * @param [in,out]	melt	If non-null, the melt that fired.
 */
void weapon_melt_fire(Entity *melt);

/**
 * @brief  checks if the thing the cream touched is the cream's target (the player) and hurts the target if so and frees itself
 * @param  cream			the cream
 * @param  other			what the cream collided with
 */
void weapon_melt_touch(Entity *cream, Entity *other);


 /*
 professor slice firing section
  */

/**
 * @brief	professor_slice's firing function, a bomb that is thrown, then as it moves it slows down at a random rate
 * @param [in,out]	professor_slice	If non-null, the professor_slice that fired.
 */
void weapon_professor_slice_fire(Entity *professor_slice);

/**
 * @brief  checks if the thing the bread touched is the bread's target (the player) and hurts the target if so and frees itself
 * @param  bread			the bread
 * @param  other			what the bread collided with
 */
void weapon_professor_slice_touch(Entity *bread, Entity *other);

/**
 * @brief slows the breads velocity, according to the think rate, until it stops
 * @param [in, out] bread			the bread
 */
void weapon_professor_slice_think(Entity *bread);

#endif
