#ifndef __CLARENCE_H__
#define __CLARENCE_H__

#include "entity.h"

/** 
 *  @brief  loads the clarence enemy entity, clarence will spike down onto the player once clarence is over him
 *  @param 	clarence	the entity that will become a clarence
 *  @param	id			this clarence's id
 *	@param	target		clarence's targetID, used to get a pointer to the target, usually the player
 *  @param	x			the x position of this clarence
 *  @param  y			the y position of this clarence 
 */
void clarence_load(Entity *clarence, int id, int target, float x, float y);

/** 
 *  @brief  checks if clarence's target is directly below him, if so then sets the direction to be straight down and change to the other think
 *  @param	clarence	the clarence
 */
void clarence_think_start(Entity *clarence);

/** 
 *  @brief  multiplies the velocity by the direction
 *  @param	clarence	the clarence
 */
void clarence_think_moving(Entity *clarence);

/** 
 *  @brief  adds clarence's velocity to his position, then resets his velocity
 *  @param	clarence	the clarence 
 */
void clarence_update(Entity *clarence);

/** 
 *  @brief  frees clarence's function pointers, then uses entity_free to free the rest of him
 *           used when clarence leaves the camera's bounds, hits the player, or is hit by the player
 *  @param	clarence	the clarence
 */
void clarence_free(Entity *clarence);

/** 
 *  @brief  checks if the thing clarence is touching is the player or the player's weapon and acts accordingly
 *  @param	clarence	the clarence
 */
void clarence_touch(Entity *clarence, Entity *other);


#endif
