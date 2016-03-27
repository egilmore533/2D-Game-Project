#include "clarence.h"
#include "simple_logger.h"
#include "weapon.h"
#include "camera.h"
#include "files.h"
#include "particle.h"

/** @brief	A macro that defines the factor that all clarences will fall at. */
#define MOVEMENT_SPEED_X	0
#define MOVEMENT_SPEED_Y	20


void clarence_load(Entity *clarence, int id, int target, float x, float y)
{
	Vect2d pos, vel, dir;

	pos = vect2d_new(x, y);
	vel = vect2d_new(0, 0);
	dir = vect2d_new(0,0);
	clarence = entity_new();
	clarence->draw = &sprite_draw;
	clarence->id = id;
	clarence->target = entity_get_by_id(target);
	clarence->free = &clarence_free;
	clarence->touch = &clarence_touch;
	clarence->update = &clarence_update;
	clarence = entity_load(clarence, CLARENCE_SPRITE, 128, 128, 16);
	clarence->direction = dir;
	clarence->velocity = vel;
	clarence->position = pos;
	clarence->state = NORMAL_STATE;
	clarence->health = 1000000;
}

void clarence_think_start(Entity *clarence)
{
	Vect2d dir = vect2d_new(0, 0);
	Vect2d vel = vect2d_new(MOVEMENT_SPEED_X, MOVEMENT_SPEED_Y);

	if(!clarence->target)
	{
		slog("no clarence target");
		return;
	}
	if(clarence->target->position.x + clarence->target->sprite->frameSize.x * 0.5 >= clarence->position.x)
	{
		dir = vect2d_new(0, 1);
		clarence->think = &clarence_think_moving;
		clarence->direction = dir;
		clarence->velocity = vel;
		vect2d_mutiply(clarence->velocity, clarence->direction, clarence->velocity);
		clarence->health = 1;
	}
	else
	{
		clarence->direction = dir;
		vect2d_mutiply(clarence->velocity, clarence->direction, clarence->velocity);
	}
}

void clarence_think_moving(Entity *clarence)
{
	camera_free_entity_outside_bounds(clarence);
}

void clarence_update(Entity *clarence)
{
	if(clarence->health <= 0)
	{
		clarence->free(clarence);
	}
	vect2d_add(clarence->position, clarence->velocity, clarence->position);
	entity_intersect_all(clarence);
	if(clarence->health <= 0)
	{
		particle_bundle_load(clarence, 40);
		clarence->free(clarence);
	}
}

void clarence_touch(Entity *clarence, Entity *other)
{
	if(!clarence->target)
	{
		slog("no clarence target");
		return;
	}
	if(!clarence->think)
	{
		if(entity_intersect(clarence, camera_get()))
		{
			clarence->think = &clarence_think_start;
		}
	}
	if(other == clarence->target)
	{
		other->health--;
		clarence->free(clarence);
	}
}

void clarence_free(Entity *clarence)
{
	clarence->update = NULL;
	clarence->touch = NULL;
	clarence->draw = NULL;
	clarence->think = NULL;
	entity_free(&clarence);
}
