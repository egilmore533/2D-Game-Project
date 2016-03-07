#ifndef __MILK_TANK_H__
#define __MILK_TANK_H__

#include "entity.h"

/**
 * @brief	load's a milk tank by allocating memory for it then, 
 * 			giving it a touch, think, update, sprite, position, velocity.
 * @param [in,out]	milk_tank	pointer to the milk tank that needs to be created.
 */
void milk_tank_load(Entity *milk_tank, int id, int target, float x, float y);

/**
 * @brief	how the milk tank will behave in game, it will chase the player and just try to touch him.
 * @param [in,out]	milk_tank the milk tank that will be thinking.
 */
void milk_tank_think(Entity *milk_tank);

/**
 * @brief	Milk tank update moves the entity and resets the velocity to the defined movement speed.
 * @param [in,out]	milk_tank	If non-null, the milk tank entity.
 */
void milk_tank_update(Entity *milk_tank);

/**
 * @brief	frees the milk tank's entity data.
 * @param [in,out]	milk_tank	If non-null, the milk tank.
 */

void milk_tank_free(Entity *milk_tank);

/**
 * @brief	what happens when the milk_tank hits the target, now only slogs.
 * @param [in,out]	milk_tank	the milk tank.
 * @param [in,out]	other	 	the other.
 */
void milk_tank_touch(Entity *milk_tank, Entity *other);

#endif 