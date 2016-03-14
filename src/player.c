#include "player.h"
#include "weapon.h"
#include "camera.h"

#define MOVEMENT_SPEED_X	10
#define MOVEMENT_SPEED_Y	10

static Entity *player = NULL;


void player_load()
{
	Vect2d pos, vel;

	pos = vect2d_new(100, 0);
	vel = vect2d_new(MOVEMENT_SPEED_X, MOVEMENT_SPEED_Y);
	player = entity_new();
	player->draw = &sprite_draw;
	player->id = 1;
	player->think = &player_think;
	player->update = &player_update;
	player->thinkRate = 200;
	player->nextThink = 0;
	player = entity_load(player, "images/pep3.png", 128, 64, 1);
	player->position = pos;
	player->velocity = vel;
	player->owner = camera_get();
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
	
	if(keys[SDL_SCANCODE_SPACE])
	{
		if(!(SDL_GetTicks() >= player->nextThink))
		{
			return;
		}
		weapon_pep_fire(player);
		player->nextThink = SDL_GetTicks() + player->thinkRate;
	}
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
		if(!(player->position.x <= player->owner->position.x))
		{
			player->velocity.x = -MOVEMENT_SPEED_X;
		}
		else
		{
			player->velocity.x = 0;
		}
	}
	else if(keys[SDL_SCANCODE_D])
	{
		if(!(player->position.x + player->sprite->frameSize.x >= player->owner->position.x + player->owner->bounds.w))
		{
			player->velocity.x = MOVEMENT_SPEED_X;
		}
		else
		{
			player->velocity.x = 0;
		}
	}
	else
	{
		player->velocity.x = 0;
	}
	if(keys[SDL_SCANCODE_W])
	{
		if(!player->position.y <= player->owner->bounds.y) //this keeps pep from moving above camera, can assume camera's y position is 0
		{
			player->velocity.y = -MOVEMENT_SPEED_Y;
		}
		else
		{
			player->velocity.y = 0;
		}
	}
	else if(keys[SDL_SCANCODE_S])
	{
		//add player's sprite height to make it perfect
		if(!(player->position.y + player->sprite->frameSize.y > player->owner->position.y + player->owner->bounds.h)) // keeps pep from moving below camera, adds camera's y (0) to its height to get the position of the bottom of the camera
		{
			player->velocity.y = MOVEMENT_SPEED_Y;
		}
		else
		{
			player->velocity.y = 0;
		}
	}
	else
	{
		player->velocity.y = 0;
	}

	vect2d_add(player->position, player->velocity, player->position);
	if(player->position.x < player->owner->position.x)
	{
		player->position.x = player->owner->position.x;
	}
	entity_intersect_all(player);
}