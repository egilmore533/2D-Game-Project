#include "celery_stalker.h"
#include "simple_logger.h"

/** @brief	A macro that defines the factor that all celery stalker will be moving by. */
#define MOVEMENT_SPEED	15

void celery_stalker_load(Entity *celery_stalker, int id, int target, float x, float y)
{
	Vect2d pos, vel, dir;

	pos = vect2d_new(x, y);
	vel = vect2d_new(MOVEMENT_SPEED, MOVEMENT_SPEED);
	dir = vect2d_new(0,0);
	celery_stalker = entity_new();
	celery_stalker->draw = &sprite_draw;
	celery_stalker->id = id;
	celery_stalker->target = entity_get_by_id(target);

	celery_stalker->update = &celery_stalker_update;
	celery_stalker->free = &entity_free;
	celery_stalker->touch = &celerly_stalker_touch;
	celery_stalker = entity_load(celery_stalker, "images/celery_stalker.png", 128, 128, 1, pos, vel);
	celery_stalker->direction = dir;
}

void celery_stalker_think_start(Entity *celery_stalker)
{
	vect2d_subtract(celery_stalker->target->position, celery_stalker->position, celery_stalker->direction);
	vect2d_normalize(&celery_stalker->direction);
	vect2d_mutiply(celery_stalker->velocity, celery_stalker->direction, celery_stalker->velocity);

	celery_stalker->think = &celery_stalker_think_moving;
}

void celery_stalker_think_moving(Entity *celery_stalker)
{
	vect2d_mutiply(celery_stalker->velocity, celery_stalker->direction, celery_stalker->velocity);
	return;
}

void celery_stalker_update(Entity *celery_stalker)
{
	vect2d_add(celery_stalker->position, celery_stalker->velocity, celery_stalker->position);
	vect2d_set(celery_stalker->velocity, MOVEMENT_SPEED, MOVEMENT_SPEED);
}

void celerly_stalker_touch(Entity *celery_stalker, Entity *other)
{
	if(!celery_stalker->think)
	{
		if(other == entity_get_by_id(1))
		{
			celery_stalker->think = &celery_stalker_think_start;
		}
	}
	else if(other->owner == celery_stalker->target)
	{
		celery_stalker->free;
	}
}
