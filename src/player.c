#include "player.h"

#define MOVEMENT_SPEED	10


Entity *player_load()
{
	Vect2d pos, vel;
	Entity *player;

	pos = vect2d_new(100, 100);
	vel = vect2d_new(0, 0);
	player = entity_new();
	player->draw = &sprite_draw;
	player->think = &player_think;
	player = entity_load(player, "images/pep2.png", 128, 128, 16, pos, vel);
	return player;
}

void player_think(Entity *player)
{
	const Uint8 *keys;
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
}