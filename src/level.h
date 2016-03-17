#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "sprite.h"

/** @brief the maximum length of level name
 */
#define LEVEL_NAME_LENGTH	80
#define MAX_ENTITIES		50 //limit on enemies that can appear in a scripted level

/** @brief simple level struct that has a loaded flag, file path, background sprite, bounds for the level, and an entityCount
 */
typedef struct
{
	int loaded;
	char *file;
	Sprite *background;
	SDL_Rect bounds;
	int entityCount; //number of entities that will appear in this level
}Level;

/** @brief the code that parses the level file and creates the background sprite along with the player, enemies, and power_ups for the level
 * @param filename	 the file's path
 */
void level_load(char filename[LEVEL_NAME_LENGTH]);

/** @brief frees the level's background if it is loaded
 */
void level_close();

/** @brief allocates memory for the global level struct and sets the entity_load_array function pointers to the respective load functions
 */
void level_initialize_system();

/** @brief getter for the level so other files can use it
 */
Level *level_get();

#endif
