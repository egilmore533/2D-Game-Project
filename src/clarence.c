#include "clarence.h"
#include "simple_logger.h"
#include "weapon.h"

/** @brief	A macro that defines the factor that all clarences will fall at. */
#define MOVEMENT_SPEED	15


void clarence_load(Entity *clarence, int id, int target, float x, float y)
{
	Vect2d pos, vel, dir;

	pos = vect2d_new(x, y);
	vel = vect2d_new(MOVEMENT_SPEED, MOVEMENT_SPEED);
	dir = vect2d_new(0,0);
	clarence = entity_new();
	clarence->draw = &sprite_draw;
	clarence->id = id;
	clarence->target = entity_get_by_id(target);
	clarence->think = &clarence_think_start;
	clarence->free = &clarence_free;
	clarence->touch = &clarence_touch;
	clarence->direction = dir;
	clarence = entity_load(clarence, "images/clarence.png", 128, 128, 16, pos, vel);
}

void clarence_think_start(Entity *clarence)
{
	Vect2d dir = vect2d_new(0, 1);
	if(clarence->target->position.x >= clarence->position.x)
	{
		clarence->think = &clarence_think_moving;
		clarence->update = &clarence_update;
		clarence->direction = dir;
	}
}

void clarence_think_moving(Entity *clarence)
{
	vect2d_mutiply(clarence->velocity, clarence->direction, clarence->velocity);
}

void clarence_update(Entity *clarence)
{
	vect2d_add(clarence->position, clarence->velocity, clarence->position);
	vect2d_set(clarence->velocity, MOVEMENT_SPEED, MOVEMENT_SPEED);
}

void clarence_touch(Entity *clarence, Entity *other)
{
	if(other == clarence->target)
	{
		slog("Player Dead");
	}
	if(other->owner == clarence->target)
	{
		other->free(other);
		clarence->free(clarence);
	}
}

void clarence_free(Entity *clarence)
{
	if(!clarence)
	{
		slog("spice doesn't point to anything");
		return;
	}
	clarence->update = NULL;
	clarence->touch = NULL;
	clarence->draw = NULL;
	clarence->think = NULL;
	entity_free(&clarence);
}
