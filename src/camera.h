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
 * @brief	moves the camera's position on the screen, runs according to think rate.
 * @param [in,out]	camera	If non-null, the camera.
 */
void camera_think(Entity *camera);

/**
 * @brief	performs the intersect all to check what entities are inside the camera's bounds, then it will draw them reative to the camera.
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

#endif