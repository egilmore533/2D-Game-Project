#include "weapon.h"
#include "particle.h"
#include "camera.h"

void weapon_fire(Entity *entity)
{
	Entity *spice;
	Vect2d pos, vel;
	int offsetX = 128; // this is the offset needed for pep's sprite this would change depending on the size of the sprite and where the bullet would come out
	int offsetY = 40; // this is the offset needed for pep's sprite this would change depending on the size of the sprite and where the bullet would come out
	if(!entity)
	{
		slog("No entity to fire from");
		return;
	}

	pos = vect2d_new(entity->position.x + offsetX, entity->position.y + offsetY);
	vel = vect2d_new(15, 0);

	spice = entity_new(); 
	spice = entity_load(spice, "images/Shot.png", 64, 64, 16, pos, vel);
	spice->owner = entity; //the entity firing owns this projectile
	spice->draw = &sprite_draw;
	spice->think = &weapon_think_particle;
	spice->update = &weapon_update;
	spice->free = &weapon_free;
	spice->touch = &weapon_touch;
	spice->thinkRate = 20;
	spice->nextThink = 0;
}

void weapon_think_particle(Entity *spice)
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

void weapon_think(Entity *spice)
{
	//if the bullet isn't touching the camera free the entity
	if(!entity_intersect(spice, camera_get()))
	{
		spice->free(spice);
	}
}

void weapon_free(Entity *spice)
{
	if(!spice)
	{
		slog("spice doesn't point to anything");
		return;
	}
	spice->owner = NULL;
	spice->draw = NULL;
	spice->think = NULL;
	entity_free(&spice);
}

void weapon_update(Entity *spice)
{
	if(!spice)
	{
		slog("spice doesn't point to anything");
		return;
	}
	vect2d_add(spice->position, spice->velocity, spice->position);
}

void weapon_touch(Entity *spice, Entity *other)
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

/*
weapon stuff for melt
 */

void weapon_melt_fire(Entity *entity)
{
	Entity *cream;
	Vect2d pos, vel;
	int offsetX = 0; //change the cream sprite and then change this
	int offsetY = 64; 
	if(!entity)
	{
		slog("No entity to fire from");
		return;
	}

	pos = vect2d_new(entity->position.x + offsetX, entity->position.y + offsetY);
	vel = vect2d_new(-15, 0);

	cream = entity_new(); 
	cream = entity_load(cream, "images/Shot.png", 64, 64, 16, pos, vel);
	cream->owner = entity; //the entity firing owns this projectile
	cream->draw = &sprite_draw;
	cream->think = &weapon_think; //same think until i have a seperate particle effect for cream
	cream->update = &weapon_update; //same update for all bullet entities, just move it along
	cream->free = &weapon_free; //same free for all weapons
	cream->touch = &weapon_melt_touch;
	cream->thinkRate = 20;
	cream->nextThink = 0;
}

void weapon_melt_think_particle(Entity *cream)
{

}

void weapon_melt_update(Entity *cream)
{

}

void weapon_melt_touch(Entity *cream, Entity *other)
{
	
}

