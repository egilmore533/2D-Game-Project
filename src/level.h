#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "vector.h"
#include "sprite.h"
#include <string.h> // for file reading and writing
#include <stdio.h> //for file reading and writing

typedef struct
{
	char		name[128];			/**< level name*/
	Sprite		*background;		/**< static background image*/
	Vect2d		levelSize;			/**< exact level width and height*/
	//will need a mechanism for setting enemy positons and types statically

}Level;

/**
 * @brief	load a level from a given file
 * @param [in,out]	file	the file to load background from
 * @return	A Level.
 */
Level level_load(char *file);

/**
 * @brief			draws the portion of the background sprite that the camera can see. 
 * 					if this was tile based it would draw the tiles that fit that portion of the screen.
 * @param [in,out]	level	pointer to a file that should be drawn to the screen, 
 */
void level_draw(Level *level);

/**
 * @brief	frees the level from memory and sets the level pointer to null so no one can refer to it.
 * @param [in,out]	level	double pointer to the level.
 */
void level_free(Level **level);

#endif