#include "professor_slice.h"
#include "simple_logger.h"
#include "weapon.h"
#include "camera.h"
#include "files.h"
#include <stdlib.h>

/** @brief	A macro that defines the factor that all celery stalker will be moving by. */
#define MOVEMENT_SPEED_X	0
#define MOVEMENT_SPEED_Y	10

void professor_slice_load(Entity *professor_slice, int id, int target, float x, float y)
{
	Vect2d pos, vel, dir;

	pos = vect2d_new(x, y);
	vel = vect2d_new(MOVEMENT_SPEED_X, MOVEMENT_SPEED_Y);
	dir = vect2d_new(0,0);

	professor_slice = entity_new();
	professor_slice->draw = &sprite_draw;
	professor_slice->id = id;
	professor_slice->target = entity_get_by_id(target);
	professor_slice->update = &professor_slice_update;
	professor_slice->free = &professor_slice_free;
	professor_slice->touch = &professor_slice_touch;
	professor_slice = entity_load(professor_slice, PROFESSOR_SLICE_SPRITE, 128, 128, 1);
	professor_slice->direction = dir;
	professor_slice->velocity = vel;
	professor_slice->position = pos;
	professor_slice->thinkRate = 2000;
	professor_slice->nextThink = 0;
	professor_slice->state = NORMAL_STATE;
	professor_slice->health = 3;
}

void professor_slice_think(Entity *professor_slice)
{
	if(!professor_slice)
	{
		slog("professor slice hasn't been loaded");
		return;
	}
	if(professor_slice->state == STICKIED_STATE)
	{
		professor_slice->think = &professor_slice_stickied_think;
		vect2d_set(professor_slice->velocity, 0, 0);
		professor_slice->nextThink = SDL_GetTicks() + professor_slice->thinkRate;
		return;
	}
	if(!(SDL_GetTicks() >= professor_slice->nextThink))
	{
		return;
	}
	vect2d_set(professor_slice->velocity, MOVEMENT_SPEED_X, MOVEMENT_SPEED_Y);
	camera_free_entity_outside_bounds(professor_slice);
	vect2d_subtract(professor_slice->target->position, professor_slice->position, professor_slice->direction);
	vect2d_normalize(&professor_slice->direction);
	vect2d_negate(professor_slice->direction, professor_slice->direction);
	vect2d_mutiply(professor_slice->velocity, professor_slice->direction, professor_slice->velocity);
	weapon_professor_slice_fire(professor_slice);
	professor_slice->nextThink = SDL_GetTicks() + professor_slice->thinkRate;
}

void professor_slice_stickied_think(Entity *professor_slice)
{
	vect2d_set(professor_slice->velocity, 0, 0);
	if(!(SDL_GetTicks() >= professor_slice->nextThink))
	{
		return;
	}
	professor_slice->state = NORMAL_STATE;
	professor_slice->think = &professor_slice_think;
}

void professor_slice_update(Entity *professor_slice)
{
	Entity *cam = camera_get();
	if(!professor_slice)
	{
		slog("professor slice hasn't been loaded");
		return;
	}
	if(professor_slice->think)
	{
		if(professor_slice->position.y <= cam->bounds.x)
		{
			if(professor_slice->velocity.y < 0)
			{
				professor_slice->velocity.y = rand() % 2;
			}
		}

		if(professor_slice->position.y + professor_slice->sprite->frameSize.y >= cam->bounds.x + cam->bounds.h)
		{
			if(professor_slice->velocity.y > 0)
			{
				professor_slice->velocity.y = -(rand() % 2);
			}
		}
		vect2d_add(professor_slice->position, professor_slice->velocity, professor_slice->position);
	}
	entity_intersect_all(professor_slice);
	if(professor_slice->health <= 0)
	{
		professor_slice->free(professor_slice);
	}
}

void professor_slice_free(Entity *professor_slice)
{
	if(!professor_slice)
	{
		slog("professor slice hasn't been loaded");
		return;
	}
	professor_slice->update = NULL;
	professor_slice->touch = NULL;
	professor_slice->draw = NULL;
	professor_slice->think = NULL;
	entity_free(&professor_slice);
}

void professor_slice_touch(Entity *professor_slice, Entity *other)
{
	if(!professor_slice)
	{
		slog("professor slice hasn't been loaded");
		return;
	}
	else if(!other)
	{
		slog("Professor slice is hitting something that doesn't exist");
		return;
	}
	
	if(!professor_slice->think)
	{
		if(other == camera_get())
		{
			professor_slice->think = &professor_slice_think;
		}
	}
	else if(other == professor_slice->target)
	{
		other->health--;
		professor_slice->free(professor_slice);
	}
}