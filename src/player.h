#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "entity.h"


/** 
 *  @brief	loads the player entity which is the only entity that takes input 
 *  @param  player	the entity that will become the player
 *  @param  id		the player's id, very important for the enemies and power_ups
 *  @param  target	the player's target, not important because the player is only concerned with its owner (the camera)
 *  @param  x		the x coordinate of the player
 *  @param  y		the y coordinate of the player
 */
void player_load(Entity *player, int id, int target, float x, float y);

/**
 * @brief	fires by clicking, holding click for a certain amount of time will result in a charged attack, press space to use a bomb to clear the screen of enemies
 * @param [in,out]	player	If non-null, the player.
 */
void player_think(Entity *player);

/**
 * @brief	sets the player's velocity according to what wasd keys are pressed, then moves the player accordingly, but keeps the player inside the camera's bounds.
 *			  also activates/deactivates the player's shield sprite, and handles the player being damaged as well as dying
 * @param [in,out]	player	the player entity.
 */
void player_update(Entity *player);

/** 
 *  @brief	frees the player's function pointers and then uses entity_free to handle the remaining freeing
 *  @param [in,out]	player	the player entity. 
 */
void player_free(Entity *player);

void player_add_life();

#endif 