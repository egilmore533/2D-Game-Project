#include "power_ups.h"
#include "simple_logger.h"

#define MOVEMENT_SPEED_X	-3
#define MOVEMENT_SPEED_Y	0

Entity *power_up_spawn(int id, int targetID, float x, float y)
{
	Entity *power_up;
	Vect2d vel, pos;

	vect2d_set(pos, x, y);
	vect2d_set(vel, MOVEMENT_SPEED_X, MOVEMENT_SPEED_Y);
	power_up = entity_new(); 
	power_up->draw = &sprite_draw;
	power_up->update = &power_up_update;
	power_up->free = &power_up_free;
	power_up->target = entity_get_by_id(targetID);
	power_up->velocity = vel;
	power_up->position = pos;
	return power_up;
}

void power_up_update(Entity *power_up)
{
	vect2d_add(power_up->position, power_up->velocity, power_up->position);
	entity_intersect_all(power_up);
}

void power_up_free(Entity *power_up)
{
	if(!power_up)
	{
		slog("professor slice hasn't been loaded");
		return;
	}
	power_up->draw = NULL;
	power_up->update = NULL;
	power_up->free = NULL;
	power_up->target = NULL;
	power_up->touch = NULL;
	entity_free(&power_up);
 }

/*
Double tap code
*/

void power_up_double_tap(Entity *double_tap, int id, int targetID, float x, float y)
{
	double_tap = power_up_spawn(id, targetID, x, y);
	double_tap = entity_load(double_tap, "images/double_tap.png", 32, 32, 1);
	double_tap->touch = &power_up_double_tap_touch;
}

void power_up_double_tap_touch(Entity *double_tap, Entity *other)
{
	if(other == double_tap->target)
	{
		other->thinkRate *= 0.5;
		double_tap->free(double_tap);
	}
}

/*
Heat Shield Code
*/

void power_up_heat_shield(Entity *heat_shield, int id, int targetID, float x, float y)
{
	heat_shield = power_up_spawn(id, targetID, x, y);
	heat_shield = entity_load(heat_shield, "images/heat_shield.png", 32, 32, 1);
	heat_shield->touch = &power_up_heat_shield_touch;
}

void power_up_heat_shield_touch(Entity *heat_shield, Entity *other)
{
	if(other == heat_shield->target)
	{
		other->health = 2;
		heat_shield->free(heat_shield);
	}
}

/*
Bomb pickup code
*/

void power_up_bomb(Entity *bomb, int id, int targetID, float x, float y)
{
	bomb = power_up_spawn(id, targetID, x, y);
	bomb = entity_load(bomb, "images/bomb_pickup.png", 32, 32, 1);
	bomb->touch = &power_up_bomb_touch;
}

void power_up_bomb_touch(Entity *bomb, Entity *other)
{
	if(other == bomb->target)
	{
		other->inventory[BOMB_SLOT]++;
		bomb->free(bomb);
	}
}

/*
Spread Code
*/

void power_up_spread(Entity *spread, int id, int targetID, float x, float y)
{
	spread = power_up_spawn(id, targetID, x, y);
	spread = entity_load(spread, "images/heat_shield.png", 32, 32, 1);
	spread->touch = &power_up_spread_touch;
}

void power_up_spread_touch(Entity *spread, Entity *other)
{
	if(other == spread->target)
	{
		other->inventory[SPREAD_SLOT]++;
		spread->free(spread);
	}
}
