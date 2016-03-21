#include "celery_stalker.h"
#include "simple_logger.h"
#include "camera.h"
#include "files.h"

/** @brief	A macro that defines the factor that all celery stalker will be moving by. */
#define MOVEMENT_SPEED_X	20
#define MOVEMENT_SPEED_Y	20

void celery_stalker_load(Entity *celery_stalker, int id, int target, float x, float y)
{
	Vect2d pos, vel, dir;

	pos = vect2d_new(x, y);
	vel = vect2d_new(MOVEMENT_SPEED_X, MOVEMENT_SPEED_Y);
	dir = vect2d_new(0,0);
	celery_stalker = entity_new();
	celery_stalker->draw = &sprite_draw;
	celery_stalker->id = id;
	celery_stalker->target = entity_get_by_id(target);

	celery_stalker->update = &celery_stalker_update;
	celery_stalker->free = &celerly_stalker_free;
	celery_stalker->touch = &celerly_stalker_touch;
	celery_stalker = entity_load(celery_stalker, CELERY_STALKER_SPRITE, 128, 128, 1);
	celery_stalker->direction = dir;
	celery_stalker->velocity = vel;
	celery_stalker->position = pos;
	celery_stalker->health = 1;
	celery_stalker->state = NORMAL_STATE;
}

void celery_stalker_think_start(Entity *celery_stalker)
{
	if(!celery_stalker->target)
	{
		slog("No celery_stalker target");
		return;
	}
	if(SDL_GetTicks() >= celery_stalker->nextThink)
	{
		vect2d_subtract(celery_stalker->target->position, celery_stalker->position, celery_stalker->direction);
		vect2d_normalize(&celery_stalker->direction);
		celery_stalker->think = &celery_stalker_think_moving;
		vect2d_mutiply(celery_stalker->velocity, celery_stalker->direction, celery_stalker->velocity);
	}
}

void celery_stalker_think_moving(Entity *celery_stalker)
{
	//kill the celery if it has left the camera's bounds
	camera_free_entity_outside_bounds(celery_stalker);
}

void celery_stalker_update(Entity *celery_stalker)
{
	//this checks if the celery_stalker has already took aim  on the player
	if(celery_stalker->think == &celery_stalker_think_moving)
	{
		vect2d_add(celery_stalker->position, celery_stalker->velocity, celery_stalker->position);
	}
	entity_intersect_all(celery_stalker);
	if(celery_stalker->health <= 0)
	{
		celery_stalker->free(celery_stalker);
	}
}

void celerly_stalker_touch(Entity *celery_stalker, Entity *other)
{
	if(!celery_stalker->target)
	{
		slog("No celery_stalker target");
		return;
	}
	if(!celery_stalker->think)
	{
		if(other == camera_get())
		{
			celery_stalker->think = &celery_stalker_think_start;
			celery_stalker->thinkRate = 2000;
			celery_stalker->nextThink = SDL_GetTicks() + celery_stalker->thinkRate;
		}
	}
	else if(other == celery_stalker->target)
	{
		other->health--;
		celery_stalker->free(celery_stalker);
	}
}

void celerly_stalker_free(Entity *celery_stalker)
{
	if(!celery_stalker)
	{
		slog("No celery_stalker to be freed");
		return;
	}
	celery_stalker->update = NULL;
	celery_stalker->touch = NULL;
	celery_stalker->draw = NULL;
	celery_stalker->think = NULL;
	entity_free(&celery_stalker);
}
