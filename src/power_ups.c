#include "power_ups.h"
#include "simple_logger.h"
#include "player.h"
#include "files.h"

#define MOVEMENT_SPEED_X	0
#define MOVEMENT_SPEED_Y	0

Entity *power_up_spawn(int id, int targetID, float x, float y)
{
	Entity *power_up;
	Vect2d vel, pos;

	vect2d_set(pos, x, y);
	power_up = entity_new(); 
	power_up->draw = &sprite_draw;
	power_up->update = &power_up_update;
	power_up->free = &power_up_free;
	power_up->target = entity_get_by_id(targetID);
	power_up->position = pos;
	return power_up;
}

void power_up_update(Entity *power_up)
{
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
	double_tap = entity_load(double_tap, DOUBLE_TAP_PICKUP_SPRITE, 32, 32, 1);
	double_tap->touch = &power_up_double_tap_touch;
}

void power_up_double_tap_touch(Entity *double_tap, Entity *other)
{
	if(other == double_tap->target)
	{
		other->thinkRate /= 2;
		double_tap->free(double_tap);
	}
}

/*
Heat Shield Code
*/

void power_up_heat_shield(Entity *heat_shield, int id, int targetID, float x, float y)
{
	heat_shield = power_up_spawn(id, targetID, x, y);
	heat_shield = entity_load(heat_shield, HEAT_SHIELD_PICKUP_SPRITE, 32, 32, 1);
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
	bomb = entity_load(bomb, BOMB_PICKUP_SPRITE, 32, 32, 1);
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

void power_up_spread_shot(Entity *spread, int id, int targetID, float x, float y)
{
	spread = power_up_spawn(id, targetID, x, y);
	spread = entity_load(spread, SPREAD_SHOT_PICKUP_SPRITE, 32, 32, 1);
	spread->touch = &power_up_spread_shot_touch;
}

void power_up_spread_shot_touch(Entity *spread, Entity *other)
{
	if(other == spread->target)
	{
		other->inventory[SPREAD_SLOT]++;
		spread->free(spread);
	}
}

/*
Sticky Goo Code
*/

void power_up_sticky_shot(Entity *sticky_shot, int id, int targetID, float x, float y)
{
	sticky_shot = power_up_spawn(id, targetID, x, y);
	sticky_shot = entity_load(sticky_shot, GOO_SHOT_PICKUP_SPRITE, 32, 32, 1);
	sticky_shot->touch = &power_up_sticky_shot_touch;
}

void power_up_sticky_shot_touch(Entity *sticky_shot, Entity *other)
{
	if(other == sticky_shot->target)
	{
		other->bullet_state = GOO_SHOT_STATE;
		sticky_shot->free(sticky_shot);
	}

}

/*
Extra Life Code
*/

void power_up_extra_life(Entity *extra_life, int id, int targetID, float x, float y)
{
	extra_life = power_up_spawn(id, targetID, x, y);
	extra_life = entity_load(extra_life, EXTRA_LIFE_PICKUP_SPRITE, 32, 32, 1);
	extra_life->touch = &power_up_extra_life_touch;
}
void power_up_extra_life_touch(Entity *extra_life, Entity *other)
{
	if(other == extra_life->target)
	{
		player_add_life();
		extra_life->free(extra_life);
	}
}