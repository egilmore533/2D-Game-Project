#include "celery_stalker.h"
#include "simple_logger.h"
#include "camera.h"
#include "weapon.h"
#include "melt.h"

/** @brief	A macro that defines the factor that all celery stalker will be moving by. */
#define MOVEMENT_SPEED_X	2
#define MOVEMENT_SPEED_Y	5

void melt_load(Entity *melt, int id, int target, float x, float y)
{
	Vect2d pos, vel, dir;

	pos = vect2d_new(x, y);
	vel = vect2d_new(MOVEMENT_SPEED_X, MOVEMENT_SPEED_Y);
	dir = vect2d_new(0,0);
	melt = entity_new();
	melt->draw = &sprite_draw;
	melt->id = id;
	melt->target = entity_get_by_id(target);

	melt->update = &melt_update;
	melt->free = &melt_free;
	melt->touch = &melt_touch;
	melt = entity_load(melt, "images/melt.png", 128, 128, 1);
	melt->direction = dir;
	melt->position = pos;
	melt->velocity = vel;
	melt->thinkRate = 800;
	melt->nextThink = 0;
}

void melt_think(Entity *melt)
{
	vect2d_subtract(melt->target->position, melt->position, melt->direction);
	vect2d_normalize(&melt->direction);
	vect2d_set(melt->direction, -1, melt->direction.y);
	vect2d_mutiply(melt->velocity, melt->direction, melt->velocity);
	if(!(SDL_GetTicks() >= melt->nextThink))
	{
		return;
	}
	weapon_melt_fire(melt);
	melt->nextThink = SDL_GetTicks() + melt->thinkRate;
}

void melt_update(Entity *melt)
{
	if(melt->think)
	{
		vect2d_add(melt->position, melt->velocity, melt->position);
		vect2d_set(melt->velocity, MOVEMENT_SPEED_X, MOVEMENT_SPEED_Y);
	}
	entity_intersect_all(melt);
}

void melt_free(Entity *melt)
{
	if(!melt)
	{
		slog("spice doesn't point to anything");
		return;
	}
	melt->update = NULL;
	melt->touch = NULL;
	melt->draw = NULL;
	melt->think = NULL;
	entity_free(&melt);
}

void melt_touch(Entity *melt, Entity *other)
{
	if(!melt->think)
	{
		if(other == camera_get())
		{
			melt->think = &melt_think;
		}
	}
	if(other == melt->target)
	{
		slog("Player Dead");
	}
	if(other->owner == melt->target)
	{
		other->free(other);
		melt->free(melt);
	}
}

