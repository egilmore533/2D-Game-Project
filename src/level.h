#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "sprite.h"

/** @brief the maximum length of level name */
#define LEVEL_NAME_LENGTH	80

/** @brief simple level struct that has a loaded flag, file path, background sprite, and bounds for the level */
typedef struct
{
	int loaded;			/**< the flag to know if the level has been loaded */
	char *file;			/**< filepath for the level file */
	Sprite *background; /**< background sprite */
	Uint32 end;			/**< the x point the player needs to reach to make it to the next level */
	Uint8 level_number;

}Level;

/** 
 *  @brief the code that parses the level file and creates the background sprite along with the player, enemies, and power_ups for the level
 *  @param level_number	 the level number
 */
void level_load(Uint8 level_number);

/** @brief frees the level's background if it is loaded */
void level_close();

/** @brief allocates memory for the global level struct and sets the entity_load_array function pointers to the respective load functions */
void level_initialize_system();

/** @brief getter for the level so other files can use it */
Level *level_get();

#endif
