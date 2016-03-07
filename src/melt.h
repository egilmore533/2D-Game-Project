#ifndef __MELT_H__
#define __MELT_H__

#include "entity.h"

void melt_load(Entity *melt, int id, int target, float x, float y);

void melt_think(Entity *melt);

void melt_update(Entity *melt);

void melt_free(Entity *melt);

void melt_touch(Entity *melt, Entity *other);


#endif
