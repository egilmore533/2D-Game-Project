#include "weapon.h"
#include "particle.h"
#include "camera.h"
#include "files.h"
#include <stdlib.h>
#include <math.h>

#define PEP_WEAPON_OFFSET_X	128
#define PEP_WEAPON_OFFSET_Y	40

#define PI			3.141589

#define PEP_CHARGE_BULLET_VEL_X		20
#define PEP_CHARGE_BULLET_VEL_Y		20

#define PEP_SPREAD_BULLET_VEL_X		15
#define PEP_SPREAD_BULLET_VEL_Y		15

extern Entity *make_spread_bullet(Entity *owner);

/*
universal weapon functions
*/
Entity *weapon_fire(Entity *owner)
{
	Entity *shot;
	//don't check for owner's target because not every entity that fires has a target (Player)

	shot = entity_new(); 

	shot->owner = owner; //the entity firing owns this projectile
	shot->draw = &sprite_draw;
	shot->update = &weapon_update;
	shot->free = &weapon_free;
	shot->target = owner->target;
	if(owner->bullet_state == GOO_SHOT_STATE)
	{
		shot->state = GOO_SHOT_STATE;
	}
	else
	{
		shot->state = NORMAL_SHOT_STATE;
	}
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
		slog("shot doesn't point to anything");
		return;
	}
	shot->owner = NULL;
	shot->draw = NULL;
	shot->think = NULL;
	entity_free(&shot);
}

void weapon_update(Entity *shot)
{
	vect2d_add(shot->position, shot->velocity, shot->position);
}

/*
Pep firing functions
*/

///////////////////////Spread shot///////////////////////////////////
void weapon_pep_spread_fire(Entity *player)
{
	Entity *spice_temp;
	Vect2d velocity;
	Uint8 shots;
	int i;

	//need to set default SPREAD_SLOT value to 0 so it will fire once for 0 instead of twice for 1
	shots = player->inventory[SPREAD_SLOT];
	for(i = 0; i <= shots; i++)
	{
		if(i == 0) //will always fire one shot straight forward
		{
			//this is the center bullet
			spice_temp = make_spread_bullet(player);
			vect2d_set(spice_temp->velocity, PEP_SPREAD_BULLET_VEL_X, 0);//will always be moving straight accross the screen horizontally
		}
		else // each extra spread shot pickup gives one extra top and bottom bullet
		{
			velocity.y = PEP_SPREAD_BULLET_VEL_X * sin(PI / 8 / i);
			velocity.x = PEP_SPREAD_BULLET_VEL_X * cos(PI / 8 / i);

			//top bullet
			spice_temp = make_spread_bullet(player);
			spice_temp->velocity = velocity;

			//bottom bullet
			velocity.y *= -1;
			spice_temp = make_spread_bullet(player);
			spice_temp->velocity = velocity;
		}
	}
}

void weapon_pep_spread_touch(Entity *spread, Entity *other)//
{
	if(other->target == spread->owner)
	{
		other->health--; // one damage for normal bullets
		if(spread->state == GOO_SHOT_STATE)
		{
			other->state = STICKIED_STATE;
		}
		spread->free(spread);
	}
}

Entity *make_spread_bullet(Entity *owner)
{
	Entity *spread_bullet;
	Vect2d pos, vel;

	spread_bullet = weapon_fire(owner);
	spread_bullet = entity_load(spread_bullet, SPICE_SPREAD_SHOT_SPRITE, 32, 16, 1); 
	spread_bullet->think = &weapon_pep_think;
	spread_bullet->touch = &weapon_pep_spread_touch;
	spread_bullet->thinkRate = 30;
	spread_bullet->nextThink = 0;
	pos = vect2d_new(owner->position.x + PEP_WEAPON_OFFSET_X, owner->position.y + PEP_WEAPON_OFFSET_Y); 
	spread_bullet->position = pos;
	vel = vect2d_new(PEP_SPREAD_BULLET_VEL_X, PEP_SPREAD_BULLET_VEL_Y);
	spread_bullet->velocity = vel;
	return spread_bullet;
}

////////////////////Charge Shot////////////////////////////////
void weapon_pep_charge_fire(Entity *player)
{
	Entity *spice;
	Vect2d pos, vel;
	spice = weapon_fire(player);
	
	pos = vect2d_new(player->position.x + PEP_WEAPON_OFFSET_X, player->position.y + PEP_WEAPON_OFFSET_Y); 
	vel = vect2d_new(PEP_CHARGE_BULLET_VEL_X, 0); 
	spice = entity_load(spice, SPICE_CHARGE_SHOT_SPRITE, 64, 64, 1); 
	spice->think = &weapon_pep_think;
	spice->touch = &weapon_pep_charge_touch;
	spice->thinkRate = 30;
	spice->nextThink = 0;
	spice->position = pos;
	spice->velocity = vel;

}

void weapon_pep_think(Entity *spice) //this is used for spread shot and charge shot so all spiciness 
{
	Particle *part;
	Vect2d offset;
	//if the bullet isn't touching the camera free the entity
	camera_free_entity_outside_bounds(spice);

	if(!(SDL_GetTicks() >= spice->nextThink))
	{
		return;
	}
	offset = vect2d_new(-30, -10);
	part = particle_new();
	part = particle_load(part, spice, offset);
	spice->nextThink = SDL_GetTicks() + spice->thinkRate;

}

void weapon_pep_charge_touch(Entity *spice, Entity *other)
{
	if(other->target == spice->owner)
	{
		other->health -= 5; //five damage is fairly big considering most enemies only have 1 health
		if(spice->state == GOO_SHOT_STATE)
		{
			other->state = STICKIED_STATE;
		}
		//charge shot is so sick it blows up the baddies and keeps going looking for more baddies to tear up
	}
}

//////////////////Bomb////////////////////////////////
void weapon_pep_bomb(Entity *player)
{
	Entity *bomb = weapon_fire(player);
	Entity *cam;
	Vect2d pos, vel;

	cam = camera_get();
	vect2d_set(pos, cam->position.x, cam->position.y);
	vect2d_set(vel, cam->velocity.x, cam->velocity.y);
	bomb = entity_load(bomb, BOMB_EXPLODE_SPRITE, 1366, 768, 1);
	bomb->thinkRate = 300;
	bomb->nextThink = bomb->thinkRate + SDL_GetTicks();
	bomb->position = pos;
	bomb->velocity = vel;
	bomb->think = &weapon_pep_bomb_think;
	bomb->touch = &weapon_pep_bomb_touch;
}

void weapon_pep_bomb_think(Entity *bomb)
{
	if(SDL_GetTicks() >= bomb->nextThink)
	{
		bomb->free(bomb);
	}
}

void weapon_pep_bomb_touch(Entity *bomb, Entity *other)
{
	if(!bomb->owner)
	{
		slog("no bomb owner");
		return;
	}
	else if(!other->target)
	{
		slog("no other target");
		return;
	}
	if(other->target == bomb->owner)//if other is an enemy deplete its health, if its a power_up nothing will happen to it, but enemies will die
	{
		other->health -= 1000000; //might have to change this if I add bosses
	}
}

/*
weapon stuff for melt
 */

void weapon_melt_fire(Entity *melt)
{
	Entity *cream;
	Vect2d pos, vel;
	int offsetX = 0; 
	int offsetY = 55; 
	cream = weapon_fire(melt);
	pos = vect2d_new(melt->position.x + offsetX, melt->position.y + offsetY);
	vel = vect2d_new(-15, 0);
	cream = entity_load(cream, CREAM_SPRITE, 32, 16, 1); //make a new sprite for cream
	cream->think = &weapon_think; //same think until i have a seperate particle effect for cream
	cream->touch = &weapon_melt_touch;
	cream->thinkRate = 200;
	cream->nextThink = 0;
	cream->velocity = vel;
	cream->position = pos;
}

void weapon_melt_touch(Entity *cream, Entity *other)
{
	if(!cream->target)
	{
		slog("no cream target");
	}
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
	bread = weapon_fire(professor_slice);
	pos = vect2d_new(professor_slice->position.x + offsetX, professor_slice->position.y + offsetY);
	vel = vect2d_new(-15, 0);
	bread = entity_load(bread, BREAD_CRUMB_SPRITE, 32, 32, 1); //make a new sprite for bread
	bread->think = &weapon_professor_slice_think; 
	bread->touch = &weapon_professor_slice_touch;
	bread->thinkRate = rand() % 200; // randomly decides how fast it will think, which means it slows down at different rates
	bread->nextThink = 0;
	bread->position = pos;
	bread->velocity = vel;
}

void weapon_professor_slice_touch(Entity *bread, Entity *other)
{
	if(!bread->target)
	{
		slog("no bread target");
		return;
	}
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
