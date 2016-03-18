#ifndef __POWER_UPS_H__
#define __POWER_UPS_H__

#include "entity.h"

/** 
 *  @brief  the basic power_up entity set up that is used by all power_ups/pick ups
 *  @param 	id			the id of the power_up entity that is being created
 *  @param  targetID 	the power_up's target's id, used to get a pointer to the 
 *  @param 	x 			the x coordinate of the power_up
 *  @param  y			the y coordinate of the power_up
 */
Entity *power_up_spawn(int id, int targetID, float x, float y);

/** 
 *  @brief  basic movement for each power_up, moves straight across the screen towards the player
 *  @param  power_up  	the power_up entity
 */
void power_up_update(Entity *power_up);

/** 
 *  @brief  frees the power_up's function pointers then uses entity_free to handle the rest of the freeing
 *  @param  power_up  	the power_up entity
 */
void power_up_free(Entity *power_up);

/*
Double Tap code
*/

/**
 *  @brief  loads a double_tap entity, which when the player picks it up will double the fire rate of the player
 *  @param  double_tap  the entity to become a double_tap
 *  @param  id		  	the id of the double_tap 
 *  @param  targetID  	the double_tap's target's id number
 *  @param  x		  	the x coordinate of the double_tap entity
 *  @param  y		  	the y coordinate of the double_tap entity
 */
void power_up_double_tap(Entity *double_tap, int id, int targetID, float x, float y);

/**
 *  @brief  checks if the thing the double_tap is touching is its target (the player) and acts accordingly
 *  @param  double_tap  the double_tap entity
 *  @param  other		the thing double_tap is touching
 */
void power_up_double_tap_touch(Entity *double_tap, Entity *other);

/*
Heat Shield Code
*/

/**
 *  @brief  loads a heat_shield entity, which when the player picks it up will give the player a shield that takes an extra hit
 *  @param  heat_shield the entity to become a heat_shield
 *  @param  id		  	the id of the heat_shield 
 *  @param  targetID  	the heat_shield's target's id number (should be the player)
 *  @param  x		  	the x coordinate of the heat_shield entity
 *  @param  y		  	the y coordinate of the heat_shield entity
 */
void power_up_heat_shield(Entity *heat_shield, int id, int targetID, float x, float y);

/**
 *  @brief  checks if the thing the heat_shield is touching is its target (the player) and acts accordingly
 *  @param  heat_shield the heat_shield entity
 *  @param  other		the thing heat_shield is touching
 */
void power_up_heat_shield_touch(Entity *heat_shield, Entity *other);

/*
Bomb pickup code
*/

/**
 *  @brief  loads a bomb pick up entity, which when the player picks it up will give the player an extra bomb
 *  @param  bomb  		the entity to become a bomb pick up
 *  @param  id		  	the id of the bomb 
 *  @param  targetID  	the bomb's target's id number (should be the player)
 *  @param  x		  	the x coordinate of the bomb entity
 *  @param  y		  	the y coordinate of the bomb entity
 */
void power_up_bomb(Entity *bomb, int id, int targetID, float x, float y);

/**
 *  @brief  checks if the thing the bomb is touching is its target (the player) and acts accordingly
 *  @param  bomb 		the bomb entity
 *  @param  other		the thing bomb is touching
 */
void power_up_bomb_touch(Entity *bomb, Entity *other);

/*
Spread Code
*/

/**
 *  @brief  loads a spread pick up entity, which when the player picks it up will increase the number of bullets the player fires
 *  @param  spread  	the entity to become a spread pick up
 *  @param  id		  	the id of the spread 
 *  @param  targetID  	the spread's target's id number (should be the player)
 *  @param  x		  	the x coordinate of the spread entity
 *  @param  y		  	the y coordinate of the spread entity
 */
void power_up_spread_shot(Entity *spread, int id, int targetID, float x, float y);

/**
 *  @brief  checks if the thing the spread is touching is its target (the player) and acts accordingly
 *  @param  spread 		the spread entity
 *  @param  other		the thing spread is touching
 */
void power_up_spread_shot_touch(Entity *spread, Entity *other);


/*
Sticky Goo Code
*/

void power_up_sticky_shot(Entity *sticky_shot, int id, int targetID, float x, float y);
void power_up_sticky_shot_touch(Entity *sticky_shot, Entity *other);

/*
Extra Life Code
*/

void power_up_extra_life(Entity *extra_life, int id, int targetID, float x, float y);
void power_up_extra_life_touch(Entity *extra_life, Entity *other);

#endif
