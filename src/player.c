#include "player.h"
#include "weapon.h"

#define MOVEMENT_SPEED_X	10
#define MOVEMENT_SPEED_Y	10

static Entity *player = NULL;


void player_load()
{
	Vect2d pos, vel;

	pos = vect2d_new(100, 100);
	vel = vect2d_new(MOVEMENT_SPEED_X, MOVEMENT_SPEED_Y);
	player = entity_new();
	player->draw = &sprite_draw;
	player->id = 0;
	player->think = &player_think;
	player->update = &player_update;
	player->thinkRate = 60;
	player->nextThink = 0;
	player = entity_load(player, "images/pep3.png", 128, 64, 1, pos, vel);
}

void player_think(Entity *player)
{
	const Uint8 *keys;
	if(!player)
	{
		slog("player not yet initialized");
		return;
	}
	if(!(SDL_GetTicks() >= player->nextThink))
	{
		return;
	}
	keys = SDL_GetKeyboardState(NULL);
	if(keys[SDL_SCANCODE_SPACE])
	{
		weapon_pep_fire(player);
	}

	entity_intersect_all(player);
	player->nextThink = SDL_GetTicks() + player->thinkRate;
}

void player_update(Entity *player)
{
	const Uint8 *keys;
	if(!player)
	{
		slog("player not yet initialized");
		return;
	}
	keys = SDL_GetKeyboardState(NULL);
	if(keys[SDL_SCANCODE_A])
	{
		player->velocity.x = -MOVEMENT_SPEED_X;
	}
	else if(keys[SDL_SCANCODE_D])
	{
		player->velocity.x = MOVEMENT_SPEED_X;
	}
	else
	{
		player->velocity.x = 0;
	}
	if(keys[SDL_SCANCODE_W])
	{
		player->velocity.y = -MOVEMENT_SPEED_Y;
	}
	else if(keys[SDL_SCANCODE_S])
	{
		player->velocity.y = MOVEMENT_SPEED_Y;
	}
	else
	{
		player->velocity.y = 0;
	}
	vect2d_add(player->position, player->velocity, player->position);
}