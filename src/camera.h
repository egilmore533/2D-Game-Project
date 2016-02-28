#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <SDL.h>
#include "vector.h"

/**
 * @brief	getter for the game's camera.
 * @return	A SDL_Rect, that is the game's camera bounds.
 */
SDL_Rect camera_get_active();

/**
 * @brief	getter for the camera's position.
 * @return	A Vect2d of the x and y coordinates of the camera.
 */
Vect2d camera_get_position();

/**
 * @brief	setter for the camera's position.
 * @param	pos - vect2d of the camera's x and y coordinates.
 */
void camera_set_position(Vect2d pos);

/**
 * @brief	setter for the camera's size.
 * @param	size - vect2d of the camera's width and height.
 */
void camera_set_size(Vect2d size);

/**
 * @brief	getter for the camera's size.
 * @return	A Vect2d of teh camera's width and height.
 */
Vect2d camera_get_size();


#endif