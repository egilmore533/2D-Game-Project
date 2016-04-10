#ifndef __MELT_H__
#define __MELT_H__

#include "entity.h"

/** @file	melt.h
 *	@brief	Melt enemy handling
 */

/** 
 *  @brief  loads a melt entity, melt will slowly move towards the player firing projectiles periodically
 *  @param	melt	the entity that will become a melt
 *  @param	id		the melt's id
 *  @param	target	the melt's target's id, used to get a pointer to the target, usually the player
 *  @param	x		the x coordinate of the melt
 *  @param	y		the y coordinate of the melt
 */
void melt_load(Entity *melt, int id, int target, float x, float y);

/** 
 *  @brief  fires projectiles according to the think rate and sets the melt's direction and velocity to be towards the player
 *  @param	melt	the melt
 */
void melt_think(Entity *melt);

/** 
 *  @brief	adds melt's velocity to its position, kills melt if not touching the camera
 *  @param	melt	the melt
 */
void melt_update(Entity *melt);

/** 
 *  @brief  frees melt's function pointers and uses entity_free to handle the rest of its freeing
 *			 frees when melt leaves the camera, touches the player, or touches the player's weapons
 *  @param	melt	the melt
 */
void melt_free(Entity *melt);

/** 
 *  @brief  checks if the melt is touching the player, or the camera and acts according
 *  @param	melt	the melt
 *  @param	other	the entity melt touched
 */
void melt_touch(Entity *melt, Entity *other);


#endif
