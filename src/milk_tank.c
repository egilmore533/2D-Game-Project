#include "milk_tank.h"
#include "simple_logger.h"


/** @brief	A macro that defines the factor that all milk_tank will be moving by. */
#define MOVEMENT_SPEED	4


void milk_tank_load(Entity *milk_tank, int id, int target, float x, float y)
{
	Vect2d pos, vel;

	pos = vect2d_new(x, y);
	vel = vect2d_new(MOVEMENT_SPEED, MOVEMENT_SPEED);
	milk_tank = entity_new();
	milk_tank->draw = &sprite_draw;
	milk_tank->id = id;
	milk_tank->target = entity_get_by_id(target);
	milk_tank->think = &milk_tank_think;
	milk_tank->update = &milk_tank_update;
	milk_tank->free = &entity_free;
	milk_tank->touch = &milk_tank_touch;
	milk_tank = entity_load(milk_tank, "images/temp_milk_tank.png", 128, 128, 16, pos, vel);
}

void milk_tank_think(Entity *milk_tank)
{
	vect2d_subtract(milk_tank->target->position, milk_tank->position, milk_tank->direction);
	vect2d_normalize(&milk_tank->direction);
	vect2d_mutiply(milk_tank->velocity, milk_tank->direction, milk_tank->velocity);

	entity_intersect_all(milk_tank);
}

void milk_tank_update(Entity *milk_tank)
{
	vect2d_add(milk_tank->position, milk_tank->velocity, milk_tank->position);
	vect2d_set(milk_tank->velocity, MOVEMENT_SPEED, MOVEMENT_SPEED);
}

void milk_tank_touch(Entity *milk_tank, Entity *other)
{
	if(other == milk_tank->target)
	{
		slog("Player Dead");
	}
	else if(other->owner == milk_tank->target)
	{
		slog("milk tank dead");
	}
}
