#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "sprite.h"

#define LEVEL_NAME_LENGTH	80
#define MAX_ENTITIES		50 //limit on enemies that can appear in a scripted level

typedef struct
{
	int loaded;
	char *file;
	Sprite *background;
	SDL_Rect bounds;
	int entityCount; //number of entities that will appear in this level
}Level;

void level_load(char filename[LEVEL_NAME_LENGTH]);

void level_close();

void level_initialize_system();

Level *level_get();

#endif
