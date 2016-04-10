#ifndef __PROFESSOR_SLICE_H__
#define __PROFESSOR_SLICE_H__

#include "entity.h"

/** @file	professor_slice.h
 *	@brief	Professor Slice enemy handling
 */

/** 
 *  @brief  loads a professor_slice entity, professor_slice will try to run away from the player (on the y axis, and will remain inside the camera's bounds) and will throw bread crumb bombs on the screen, which will move a random distance towards the player
 *  @param	professor_slice	the entity that will become a professor_slice
 *  @param	id				the professor_slice's id
 *  @param	target			the professor_slice's target's id, used to get a pointer to the target, usually the player
 *  @param	x				the x coordinate of the professor_slice
 *  @param	y				the y coordinate of the professor_slice
 */
void professor_slice_load(Entity *professor_slice, int id, int target, float x, float y);

/** 
 *  @brief  fires projectiles according at the think rate and sets the professor_slice's direction and velocity to be away from the player, kills professor_slice if not touching the camera
 *  @param	professor_slice	the professor_slice
 */
void professor_slice_think(Entity *professor_slice);

/**
 *  @brief	professor_slice will be stickied until the nextThink, then will reset the think function back to normal
 *  @param	professor_slice	the professor_slice
 */
void professor_slice_stickied_think(Entity *professor_slice);

/** 
 *  @brief	adds professor_slice's velocity to its position 
 *  @param	professor_slice the professor_slice
 */
void professor_slice_update(Entity *professor_slice);

/** 
 *  @brief  frees professor_slice's function pointers and uses entity_free to handle the rest of its freeing
 *			 frees when professor_slice leaves the camera, touches the player, or touches the player's weapons
 *  @param	professor_slice	the professor_slice
 */
void professor_slice_free(Entity *professor_slice);

/** 
 *  @brief  checks if the professor_slice is touching the camera (and doesn't have a think function set), or the player and acts according
 *  @param	professor_slice	the professor_slice
 *  @param	other		    the entity professor_slice touched
 */
void professor_slice_touch(Entity *professor_slice, Entity *other);


#endif