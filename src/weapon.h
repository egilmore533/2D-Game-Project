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

/**
 *  @brief	fires mutiple shots, based on how many spread_shot pickups the player has collected, the bullets velocity is determined based upon trig
 *				the bullets velocity is based on a triangle whose r value is equal to the total velocity so each bullet will travel the same speed
 *  @param [in,out]	player	If non-null, the player.
 */
void weapon_pep_spread_fire(Entity *player);

/**
 *	@brief	if other is an enemy deplete its health, if its a power_up nothing will happen to it, but enemies will die
 *				if bullet is in GOO_STATE then make the other entity in a stickied state
 *  @param [in,out]	player	If non-null, the player.
 *  @param [in,out]	other	If non-null, the entity player touched.
 */
void weapon_pep_spread_touch(Entity *spread, Entity *other);


/**
 * @brief	loads the bullet to pep's position with offsets specific for pep, fires one powered up shot
 * @param [in,out]	player	If non-null, the player.
 */
void weapon_pep_charge_fire(Entity *player);

/**
 * @brief	think that creates a particle for pep's spicey shots and test's if the shot is out of the camera's bounds, deletes if so.
 * @param [in,out]	spice	the bullet.
 */
void weapon_pep_think(Entity *spice);

/**
 * @brief	if charge shot touches an enemy then remove five health and keep going.
 * @param [in,out]	spice	the bullet.
 * @param [in,out]	other	whats touching the bullet.
 */
void weapon_pep_charge_touch(Entity *spice, Entity *other);

/**
 * @brief	creates an explosion on the screen, it clears the screen of all enemies, moves at the camera's velocity and takes up the whole screen and then frees itself.
 * @param [in,out]	player	If non-null, the player.
 */
void weapon_pep_bomb(Entity *player);

/**
 * @brief	frees the bomb after a moment
 * @param [in,out]	bomb	If non-null, the bomb.
 */
void weapon_pep_bomb_think(Entity *bomb);

/**
 * @brief does massive damage to all enemies on the screen, enough to kill clarence even in his "invulnerable state"
 * @param [in,out]	bomb	If non-null, the bomb.
 * @param [in,out]	other	whats touching the bomb.
 */
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
