#include "weapon.h"
#include "particle.h"
#include "camera.h"
#include <stdlib.h>

/*
universal weapon functions
*/
Entity *weapon_fire(Entity *owner)
{
	Entity *shot;
	if(!owner)
	{
		slog("No entity to fire from");
		return NULL;
	}

	shot = entity_new(); 
	shot->owner = owner; //the entity firing owns this projectile
	shot->draw = &sprite_draw;
	shot->update = &weapon_update;
	shot->free = &weapon_free;
	shot->target = owner->target;
	return shot;
}

void weapon_think(Entity *shot)
{
	//if the bullet isn't touching the camera free the entity
	if(!entity_intersect(shot, camera_get()))
	{
		shot->free(shot);
	}
}

void weapon_free(Entity *shot)
{
	if(!shot)
	{
		slog("spice doesn't point to anything");
		return;
	}
	shot->owner = NULL;
	shot->draw = NULL;
	shot->think = NULL;
	entity_free(&shot);
}

void weapon_update(Entity *shot)
{
	if(!shot)
	{
		slog("spice doesn't point to anything");
		return;
	}
	vect2d_add(shot->position, shot->velocity, shot->position);
}

/*
Pep firing functions
*/
void weapon_pep_fire(Entity *player)
{
	Entity *spice;
	spice = weapon_fire(player);
	Vect2d pos, vel;
	int offsetX = 128; // this is the offset needed for pep's sprite this would change depending on the size of the sprite and where the bullet would come out
	int offsetY = 40; // this is the offset needed for pep's sprite this would change depending on the size of the sprite and where the bullet would come out
	
	pos = vect2d_new(player->position.x + offsetX, player->position.y + offsetY); 
	vel = vect2d_new(15, 0); 
	spice = entity_load(spice, "images/spice.png", 32, 16, 1); 
	spice->think = &weapon_pep_think_particle;
	spice->touch = &weapon_pep_touch;
	spice->thinkRate = 200;
	spice->nextThink = 0;
	spice->position = pos;
	spice->velocity = vel;

}

void weapon_pep_think_particle(Entity *spice)
{
	Particle *part;
	Vect2d offset;
	if(!spice)
	{
		slog("spice doesn't point to anything");
		return;
	}
	//if the bullet isn't touching the camera free the entity
	if(!entity_intersect(spice, camera_get()))
	{
		weapon_free(spice);
	}

	if(!(SDL_GetTicks() >= spice->nextThink))
	{
		return;
	}
	offset = vect2d_new(-30, -10);
	part = particle_new();
	part = particle_load(part, spice, offset);
	spice->nextThink = SDL_GetTicks() + spice->thinkRate;

}

void weapon_pep_touch(Entity *spice, Entity *other)
{
	if(!spice)
	{
		slog("spice doesn't point to anything");
		return;
	}
	if(!other)
	{
		slog("other doesn't point to anything");
		return;
	}
}

void weapon_pep_bomb(Entity *player)
{
	Entity *bomb = weapon_fire(player);
	Entity *cam;
	Vect2d pos;

	cam = camera_get();
	vect2d_set(pos, cam->position.x, cam->position.y);
	bomb = entity_load(bomb, "images/pep_bomb.png", 1366, 768, 1);
	bomb->thinkRate = 300;
	bomb->nextThink = bomb->thinkRate + SDL_GetTicks();
	bomb->position = pos;
	bomb->think = &weapon_pep_bomb_think;
}

void weapon_pep_bomb_think(Entity *bomb)
{
	if(SDL_GetTicks() >= bomb->nextThink)
	{
		bomb->free(bomb);
	}
}

/*
weapon stuff for melt
 */

void weapon_melt_fire(Entity *melt)
{
	Entity *cream;
	Vect2d pos, vel;
	int offsetX = 0; //change the cream sprite and then change this
	int offsetY = 64; 
	if(!melt)
	{
		slog("No entity to fire from");
		return;
	}
	cream = weapon_fire(melt);

	pos = vect2d_new(melt->position.x + offsetX, melt->position.y + offsetY);
	vel = vect2d_new(-15, 0);
	cream = entity_load(cream, "images/cream.png", 32, 16, 1); //make a new sprite for cream
	cream->think = &weapon_think; //same think until i have a seperate particle effect for cream
	cream->touch = &weapon_melt_touch;
	cream->thinkRate = 200;
	cream->nextThink = 0;
	cream->velocity = vel;
	cream->position = pos;
}

void weapon_melt_touch(Entity *cream, Entity *other)
{
	if(other == cream->target)
	{
		other->health--;
		cream->free(cream);
	}
}

/*
Professor Slice weapon 
*/
void weapon_professor_slice_fire(Entity *professor_slice)
{
	Entity *bread;
	Vect2d pos, vel;
	int offsetX = 0; //change the cream sprite and then change this
	int offsetY = 64; 
	if(!professor_slice)
	{
		slog("No entity to fire from");
		return;
	}
	bread = weapon_fire(professor_slice);

	pos = vect2d_new(professor_slice->position.x + offsetX, professor_slice->position.y + offsetY);
	vel = vect2d_new(-15, 0);
	bread = entity_load(bread, "images/bread_crumb.png", 32, 32, 1); //make a new sprite for bread
	bread->think = &weapon_professor_slice_think; 
	bread->touch = &weapon_professor_slice_touch;
	bread->thinkRate = rand() % 200; // randomly decides how fast it will think, which means it slows down at different rates
	bread->nextThink = 0;
	bread->position = pos;
	bread->velocity = vel;
}

void weapon_professor_slice_touch(Entity *bread, Entity *other)
{
	if(other == bread->target)
	{
		other->health--;
		bread->free(bread);
	}
}

void weapon_professor_slice_think(Entity *bread)
{
	//if the bullet isn't touching the camera free the entity
	if(!entity_intersect(bread, camera_get()))
	{
		bread->free(bread);
	}
	if(bread->velocity.x == 0)
	{
		return;
	}
	if(!(SDL_GetTicks() >= bread->nextThink))
	{
		return;
	}
	
	else if(bread->velocity.x < 0)
	{
		bread->velocity.x++;
		if(bread->velocity.x >= 0)
		{
			bread->velocity.x = 0;
		}
	}
	bread->nextThink = SDL_GetTicks() + bread->thinkRate;
}
