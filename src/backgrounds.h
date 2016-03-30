#ifndef __BACKGROUNDS_H__
#define __BACKGROUNDS_H__

#include "sprite.h"
#include "simple_logger.h"

/** @brief the struct for background layers so that they can be drawn infinitely at a unique speed */
typedef struct Background_s
{
	int			alive;
	Sprite		*sprite;

	Vect2d		mainPosition, chaserPosition;
	int			frame, totalFrames;
	Vect2d		velocity;
	Uint32		nextThink, thinkRate;

	void (*draw)	(Sprite *sprite, int frame, Vect2d drawPosition);
	void (*update)	(struct Background_s *self);
	void (*free)	(struct Background_s **self);
}Background;

/**
 * @brief basic free function for a background, also removes the pointer to the background so its no longer in the backgroundList
 * @param [in,out] background		double pointer to the background
 */
void background_free(Background **background);

/**
 * @brief	closes the backgroundList, freeing all backgrounds, and resets the backgroundMax to be 0
 */
void background_close_system();

/**
 * @brief initializes the backgroundList so it can be used to load layers of the background
 * @param maxBackground	the maximum number of backgrounds that the list will allow, exceeding this number will cause the program to close
 */
void background_initialize_system(int maxBackground);

/**
 * @brief	returns the first availabe backround in the backgroundList and sets it to be alive
 * @return	if non-null, the first background that is available in the backgroundList
 */
Background *background_new();


/**
 * @brief loops through all backgrounds, and draws their sprites twice once in the main position and once in the chaser position
 */
void background_draw_all();

/**
 * @brief	loops through all backgrounds performing their update functions
 */
void background_update_all();

/**
 * @brief adds a background into the backgroundList with the provided info
 * @param background_file_path filepath to find the image that will become the backgrounds sprite
 * @param velocityFactor	how fast the background should scroll in terms of the camera, needs to be negated so it moves opposite the camera
 * @param width				the width of a frame of the background
 * @param height			the height of a frame of the background
 * @param fpl				the frames per line for the background's sprite
 */
Background *background_load(char background_file_path[128], float velocityFactor, int width, int height, int fpl, int frames);

/**
 * @brief	updates the background's main and chaser positions according to the background's velocity
 *			when the chaser is entirely on the screen it becomes the main and the chaser is moved back past the new main
 * @param	[in,out] background		the background that is being updated
 */
void background_update(Background *background);

#endif