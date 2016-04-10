#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "sprite.h"

/** @file	level.h
 *	@brief	level system, handles initializing, loading, and closing levels.
 */

/** 
 * @struct	Level struct
 * @brief simple level struct that is used to store the background sprite and the end of the level 
 */
typedef struct
{
	int loaded;			/**< the flag to know if the level has been loaded */
	char *file;			/**< filepath for the level file */
	Sprite *background; /**< background sprite */
	Uint32 end;			/**< the x point the player needs to reach to make it to the next level */
	Uint8 level_number; /**< the level number of the current level*/

}Level;

/** 
 *  @brief the code that parses the level file and creates the background sprite along with the player, enemies, and power_ups that appear in the level
 *  @param level_number	 the level number
 */
void level_load(Uint8 level_number);

/** @brief frees the level's background if it is loaded */
void level_close();

/** @brief allocates memory for the global level struct and sets the entity_load_array function pointers to the respective load functions */
void level_initialize_system();

/** @brief getter for the level so other files can use it's data members */
Level *level_get();

#endif
