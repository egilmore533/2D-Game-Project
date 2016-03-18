#ifndef __MOUSE_H__
#define __MOUSE_H__

#include "entity.h"
#include "simple_logger.h"


/** @brief	initializes the mouse (which is an entity) by loading the sprite, disabling the real cursor, and setting the draw, think, touch, and update. All of which do nothing for now (except update) */
void mouse_initialize();

/**
 * @brief	does nothing, but is where the click behaviour would be handled.
 * @param [in,out]	mouse	If non-null, the mouse.
 */
void mouse_think(Entity *mouse);

/**
 * @brief	update's the mouse's position on the screen, using SDL's get mouse state.
 * @param [in,out]	mouse	If non-null, the mouse.
 */
void mouse_update(Entity *mouse);

/**
 * @brief	does nothing for now because I'm not using the mouse yet.
 * @param [in,out]	self 	If non-null, the class instance that this method operates on.
 * @param [in,out]	other	If non-null, the other.
 */
void mouse_touch(Entity *self, Entity *other);

#endif