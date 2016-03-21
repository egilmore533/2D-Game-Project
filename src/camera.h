#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <SDL.h>
#include "vector.h"
#include "entity.h"

/**
 * @brief	initializes the camera entity with given information, needs to be initialized after
 * 			all the systems are started, but before the level is loaded.
 * @param	position  	The x and y coordinates of the camera.
 * @param	dimensions	The width and height of the camera.
 * @param	id		  	The camera entity's identifier.
 */
void camera_initialize(Vect2d position, Vect2d dimensions, int id);

/**
 * @brief	moves the camera, performs the intersect all to check what entities are inside the camera's bounds, then camera_touch will draw them, be sure to remove camera_touch after runnign intersect all that way nothing is drawn twice.
 * @param [in,out]	self	If non-null, the camera entity.
 */
void camera_update(Entity *self);

/**
 * @brief	draws the entity that is touching the camera
 * @param [in,out]	self 	If non-null, the camera.
 * @param [in,out]	other	If non-null, entity to draw.
 */
void camera_touch(Entity *self, Entity *other);

/**
 * @brief	getter for the camera entity so other files can use the camera.
 * @return	null if it fails, else an Entity*.
 */
Entity *camera_get();

/** 
 *  @brief	runs the entities free function if they are out of the camera's bounds
 *  @param ent	the entity in question
 */
void camera_free_entity_outside_bounds(Entity *ent);

/** 
 *  @brief	stops the camera from moving, used when there is a game over
 */
void camera_stop();

#endif