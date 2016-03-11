#ifndef __PROFESSOR_SLICE_H__
#define __PROFESSOR_SLICE_H__

#include "entity.h"

void professor_slice_load(Entity *professor_slice, int id, int target, float x, float y);

void professor_slice_think(Entity *professor_slice);

void professor_slice_update(Entity *professor_slice);

void professor_slice_free(Entity *professor_slice);

void professor_slice_touch(Entity *professor_slice, Entity *other);


#endif