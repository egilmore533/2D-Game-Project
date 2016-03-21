#ifndef __MILK_TANK_H__
#define __MILK_TANK_H__

#include "entity.h"

/** 
 *  @brief	loads a milk_tank entity, milk_tank will move towards the player slowly trying to hit the player, it takes has 5 health
 *  @param [in,out]	milk_tank	pointer to the milk tank that needs to be created.
 */
void milk_tank_load(Entity *milk_tank, int id, int target, float x, float y);

/**
 * @brief	calculates the magnitude of the separation between milk_tank and player, then normalizes that magnitude to get the direction 
 *			milk_tank should move to go straight towards the player, then multiplies that direction by the defined velocity
 * @param [in,out]	milk_tank the milk tank that will be thinking.
 */
void milk_tank_think(Entity *milk_tank);

/**
 *  @brief	 milk_tank will be stickied until the nextThink, then will reset the think function and its think rate back to normal
 *  @param	 milk_tank	the  milk_tank
 */
void  milk_tank_stickied_think(Entity * milk_tank);

/**
 * @brief	adds milk_tank's velocity to its position, and kills milk_tank if has no more health
 * @param [in,out]	milk_tank	If non-null, the milk tank entity.
 */
void milk_tank_update(Entity *milk_tank);

/**
 * @brief	frees the milk tank's function pointers and uses entity_free to handle the rest of the freeing
 * @param [in,out]	milk_tank	If non-null, the milk tank.
 */
void milk_tank_free(Entity *milk_tank);

/**
 * @brief	what happens when the milk_tank touches the player or camera
 * @param [in,out]	milk_tank	the milk tank.
 * @param [in,out]	other	 	the other.
 */
void milk_tank_touch(Entity *milk_tank, Entity *other);

#endif 