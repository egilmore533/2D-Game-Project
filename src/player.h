#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "entity.h"

Entity *player_load();
void player_think(Entity *player);
void player_update();

#endif 