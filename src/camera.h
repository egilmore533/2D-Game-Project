#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <SDL.h>
#include "vector.h"
#include "entity.h"

/**
 * @brief	initializes the camera entity with given information, needs to be initialized after all the systems are started.
 * @param	position  	The x and y coordinates of the camera.
 * @param	dimensions	The width and height of the camera.
 */
void camera_initialize(Vect2d position, Vect2d dimensions);

/**
 * @brief	does nothing for now.
 * @param [in,out]	camera	If non-null, the camera.
 */
void camera_think(Entity *camera);

/**
 * @brief	does nothing for now.
 * @param [in,out]	self	If non-null, the class instance that this method operates on.
 */
void camera_update(Entity *self);

/**
 * @brief	when an entity is touching the camera's bounding box draw that entity.
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