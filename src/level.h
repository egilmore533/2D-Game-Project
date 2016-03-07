#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "sprite.h"

#define LEVEL_NAME_LENGTH	80

typedef struct
{
	int loaded;
	char file[LEVEL_NAME_LENGTH];
	Sprite *background;
	SDL_Rect bounds;
}Level;

void level_load(char *filename);

void level_close();

void level_initialize_system();

#endif
