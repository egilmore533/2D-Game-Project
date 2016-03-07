#ifndef __CELERY_STALKER_H__
#define __CELERY_STALKER_H__

#include "entity.h"

void celery_stalker_load(Entity *celery_stalker, int id, int target, float x, float y);

void celery_stalker_think_start(Entity *celery_stalker);

void celery_stalker_think_moving(Entity *celery_stalker);

void celery_stalker_update(Entity *celery_stalker);

void celerly_stalker_free(Entity *celery_stalker);

void celerly_stalker_touch(Entity *celery_stalker, Entity *other);


#endif