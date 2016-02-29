#ifndef __MOUSE_H__
#define __MOUSE_H__

#include "entity.h"
#include "simple_logger.h"


/** @brief	initializes the mouse by loading the sprite, disabling the real cursor, and setting the draw, think, touch, and update. */
void mouse_initialize();

/**
 * @brief	the mouse entity's click behavior.
 * @param [in,out]	mouse	If non-null, the mouse.
 */
void mouse_think(Entity *mouse);

/**
 * @brief	update's the mouse's position on the screen, using SDL's get mouse state.
 * @param [in,out]	mouse	If non-null, the mouse.
 */
void mouse_update(Entity *mouse);

/**
 * @brief	does nothing for now.
 * @param [in,out]	self 	If non-null, the class instance that this method operates on.
 * @param [in,out]	other	If non-null, the other.
 */
void mouse_touch(Entity *self, Entity *other);

#endif