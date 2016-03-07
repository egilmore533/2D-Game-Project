#ifndef __CLARENCE_H__
#define __CLARENCE_H__

#include "entity.h"

void clarence_load(Entity *clarence, int id, int target, float x, float y);

void clarence_think_start(Entity *clarence);

void clarence_think_moving(Entity *clarence);

void clarence_update(Entity *clarence);

void clarence_free(Entity *clarence);

void clarence_touch(Entity *clarence, Entity *other);


#endif
