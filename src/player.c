#include "player.h"
#include "weapon.h"

#define MOVEMENT_SPEED	10

static Entity *player = NULL;


void player_load()
{
	Vect2d pos, vel;

	pos = vect2d_new(100, 100);
	vel = vect2d_new(0, 0);
	player = entity_new();
	player->draw = &sprite_draw;
	player->id = 0;
	player->think = &player_think;
	player->update = &player_update;
	player = entity_load(player, "images/pep2.png", 128, 128, 16, pos, vel);
}

void player_think(Entity *player)
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
		player->velocity.x = -MOVEMENT_SPEED;
	}
	else if(keys[SDL_SCANCODE_D])
	{
		player->velocity.x = MOVEMENT_SPEED;
	}
	else
	{
		player->velocity.x = 0;
	}
	if(keys[SDL_SCANCODE_W])
	{
		player->velocity.y = -MOVEMENT_SPEED;
	}
	else if(keys[SDL_SCANCODE_S])
	{
		player->velocity.y = MOVEMENT_SPEED;
	}
	else
	{
		player->velocity.y = 0;
	}
	if(keys[SDL_SCANCODE_SPACE])
	{
		weapon_fire(player);
	}

	entity_intersect_all(player);
}
void player_update(Entity *player)
{
	if(!player)
	{
		slog("player not yet initialized");
		return;
	}
	vect2d_add(player->position, player->velocity, player->position);
}