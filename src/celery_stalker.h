#ifndef __CELERY_STALKER_H__
#define __CELERY_STALKER_H__

#include "entity.h"

/** 
 *  @brief load code for a celery_stalker enemy entity, the cleery stalker will appear on screen for a brief time then bolt towards where the player was when it started moving
 *  @param celery_stalker	the entity that will become a celery_stalker
 *  @param id				the celery_stalker's id
 *  @param target			the id of the celery_stalker's target, usually whatever the player's is
 *  @param x					the x position of the celery_stalker
 *  @param y					the y position of the celery_stalker
 */
void celery_stalker_load(Entity *celery_stalker, int id, int target, float x, float y);

/** 
 *  @brief waits for the specified number of ticks, then targets the player by setting the direction towards the plus
 *  @param celery_stalker	the entity that is assumed to be a celery_stalker
 */
void celery_stalker_think_start(Entity *celery_stalker);

/** 
 *  @brief multiplies the velocity by direction and stores it in velocity, needs to check if celery_stalker is touching the camera and delete it otherwise
 *  @param celery_stalker	the entity that is assumed to be a celery_stalker
 */
void celery_stalker_think_moving(Entity *celery_stalker);

/** 
 *  @brief adds the velocity result to position, then resets the velocity to normal values that way you can run think again
 *  @param celery_stalker	the entity that is assumed to be a celery_stalker
 */
void celery_stalker_update(Entity *celery_stalker);

/** 
 *  @brief frees the celery_stalker's function pointers then runs the entity_free function, called when the celery_stalker dies, kills the player, or leaves the camera's bounds
 *  @param celery_stalker	the entity that is assumed to be a celery_stalker
 */
void celerly_stalker_free(Entity *celery_stalker);

/** 
 *  @brief checks if the celery_stalker touches the camera, the player, or the player's attacks performs the appropriate actions for each,
 *			if the celery_stalker hasn't touched the camera yet it needs to begin thinking, player needs to get hurt, or the celery_stalker needs to get hurt
 *  @param celery_stalker	the entity that is assumed to be a celery_stalker
 *  @param other 			the entity that collided with the celery_stalker
 */
void celerly_stalker_touch(Entity *celery_stalker, Entity *other);


#endif