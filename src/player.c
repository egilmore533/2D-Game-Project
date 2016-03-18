#include "player.h"
#include "weapon.h"
#include "camera.h"

#define MOVEMENT_SPEED_X	10
#define MOVEMENT_SPEED_Y	10
#define CHARGE_RATE			1000

void player_load(Entity *player, int id, int target, float x, float y)
{
	Vect2d pos, vel;

	pos = vect2d_new(x, y);
	vel = vect2d_new(MOVEMENT_SPEED_X, MOVEMENT_SPEED_Y);
	player = entity_new();
	player->draw = &sprite_draw;
	player->id = id;
	player->think = &player_think;
	player->update = &player_update;
	player->free = &player_free;
	player->thinkRate = 200;
	player->nextThink = 0;
	player = entity_load(player, "images/pep3.png", 128, 64, 2);
	player->position = pos;
	player->velocity = vel;
	player->owner = camera_get();
	player->health = 1;
	player->maxHealth = 1;
	player->inventory[BOMB_SLOT] = 2;
	player->inventory[SPREAD_SLOT] = 0;
}

void player_think(Entity *player)
{
	static Uint32 full_charge;
	const Uint8 *keys;
	SDL_Event click_event;
	static Uint8 clicked = 0;
	if(!player)
	{
		slog("player not yet initialized");
		return;
	}
	SDL_PollEvent(&click_event);
	keys = SDL_GetKeyboardState(NULL);
	if(keys[SDL_SCANCODE_SPACE])
	{
		if(SDL_GetTicks() >= player->nextThink)
		{
			if(player->inventory[BOMB_SLOT] > 0)
			{
				weapon_pep_bomb(player);
				player->inventory[BOMB_SLOT]--;
				player->nextThink = SDL_GetTicks() + player->thinkRate;
			}
		}
	}
	if(click_event.type == SDL_MOUSEBUTTONDOWN)
	{
		clicked = 1;
		full_charge = SDL_GetTicks() + CHARGE_RATE;
	}
	else if(click_event.type == SDL_MOUSEBUTTONUP && clicked)
	{
		if(full_charge >= SDL_GetTicks())
		{
			//this needs to be the spread version
			weapon_pep_spread_fire(player);
			player->nextThink = SDL_GetTicks() + player->thinkRate;
		}
		else
		{
			weapon_pep_charge_fire(player);
			player->nextThink = SDL_GetTicks() + player->thinkRate;
		}
		clicked = 0;
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
	//if the player picked up the shield power up it will get a health of 2
	//using maxHealth purely to help implement the logic
	//if maxHealth is less than 2, but the player health is 2 then the shield needs to be activated
	if(player->health > 1 && player->maxHealth < 2)
	{
		player->maxHealth = 2;
		player->frame++;
	}
	//if the player has a maxHealth of 2, but has a health of 1 then they lost their shield
	//set the maxHEalth to 1 and reset the sprite to be the normal player sprite
	else if(player->maxHealth >= 2 && player->health == 1)
	{
		player->maxHealth = 1;
		player->frame--;
	}
	//if the player's health is less than 1 then kill
	else if(player->health <= 0)
	{
		//put player_dead_think here if thats the route I go for this problem
		player->free(player);
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

void player_free(Entity *player)
{
	if(!player)
	{
		slog("spice doesn't point to anything");
		return;
	}
	player->update = NULL;
	player->touch = NULL;
	player->draw = NULL;
	player->think = NULL;
	entity_free(&player);
}