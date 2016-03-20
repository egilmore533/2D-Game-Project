#include "milk_tank.h"
#include "simple_logger.h"
#include "camera.h"
#include "files.h"

/** @brief	A macro that defines the factor that all milk_tank will be moving by. */
#define MOVEMENT_SPEED_X	4
#define MOVEMENT_SPEED_Y	4

void milk_tank_load(Entity *milk_tank, int id, int target, float x, float y)
{
	Vect2d pos, vel;

	pos = vect2d_new(x, y);
	vel = vect2d_new(MOVEMENT_SPEED_X, MOVEMENT_SPEED_Y);
	milk_tank = entity_new();
	milk_tank->draw = &sprite_draw;
	milk_tank->id = id;
	milk_tank->target = entity_get_by_id(target);
	milk_tank->update = &milk_tank_update;
	milk_tank->free = &milk_tank_free;
	milk_tank->touch = &milk_tank_touch;
	milk_tank = entity_load(milk_tank, MILK_TANK_SPRITE, 128, 128, 1);
	milk_tank->velocity = vel;
	milk_tank->position = pos;
	milk_tank->thinkRate = 2000; //only used for stickied thinking
	milk_tank->state = NORMAL_STATE;
	milk_tank->health = 5;
}

void milk_tank_think(Entity *milk_tank)
{
	if(milk_tank->state == STICKIED_STATE)
	{
		milk_tank->think = &milk_tank_stickied_think;
		vect2d_set(milk_tank->velocity, 0, 0);
		milk_tank->thinkRate = 2000;
		milk_tank->nextThink = SDL_GetTicks() + milk_tank->thinkRate;
		return;
	}
	if(!(SDL_GetTicks() >= milk_tank->nextThink))
	{
		return;
	}
	vect2d_subtract(milk_tank->target->position, milk_tank->position, milk_tank->direction);
	vect2d_normalize(&milk_tank->direction);
	vect2d_mutiply(milk_tank->velocity, milk_tank->direction, milk_tank->velocity);
	//7camera_free_entity_outside_bounds(milk_tank);
}

void milk_tank_stickied_think(Entity *milk_tank)
{
	vect2d_set(milk_tank->velocity, 0, 0);
	if(!(SDL_GetTicks() >= milk_tank->nextThink))
	{
		return;
	}
	milk_tank->state = NORMAL_STATE;
	milk_tank->think = &milk_tank_think;
	milk_tank->thinkRate = 40;
	milk_tank->nextThink = milk_tank->thinkRate + SDL_GetTicks();
}

void milk_tank_update(Entity *milk_tank)
{
	if(milk_tank->think)
	{
		vect2d_add(milk_tank->position, milk_tank->velocity, milk_tank->position);
		vect2d_set(milk_tank->velocity, MOVEMENT_SPEED_X, MOVEMENT_SPEED_Y);
	}
	entity_intersect_all(milk_tank);
	if(milk_tank->health <= 0)
	{
		milk_tank->free(milk_tank);
	}
	
}

void milk_tank_touch(Entity *milk_tank, Entity *other)
{
	if(other == milk_tank->target)
	{
		other->health--;
		milk_tank->free(milk_tank);
	}
	else if(!milk_tank->think && other == camera_get())
	{
		milk_tank->think = &milk_tank_think;
	}
}

void milk_tank_free(Entity *milk_tank)
{
	if(!milk_tank)
	{
		slog("spice doesn't point to anything");
		return;
	}
	milk_tank->update = NULL;
	milk_tank->touch = NULL;
	milk_tank->draw = NULL;
	milk_tank->think = NULL;
	entity_free(&milk_tank);
}
