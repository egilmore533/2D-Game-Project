#include "entity.h"
#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include "simple_logger.h"
#include "graphics.h"

static Entity *entityList = NULL;
static int entityNum;
static int entityMax = 0;

void entity_free(Entity **entity)
{
	Entity *self;
	if(!entity)
	{
		return;
	}
	if(!*entity) 
	{
		return;
	}
	self = *entity;
	self->inUse--;

	if(self->sprite != NULL)
	{
		sprite_free(&self->sprite);
	}
	entityNum--;
	*entity = NULL;
}

Entity *entity_new()
{
	int i;
	/*makesure we have the room for a new sprite*/
	if(entityNum + 1 > entityMax)
	{
		slog("Maximum Entity Reached.");
		exit(1);
	}
	for(i = 0; i < entityMax; i++)
	{
		if(entityList[i].inUse)
		{
			continue;
		}
		memset(&entityList[i],0,sizeof(Entity));
		entityList[i].inUse = 1;
		entityNum++;
		return &entityList[i];
	}
	return NULL;
}

void entity_close_system()
{
	int i;
	Entity *entity;
	if(!entityList)
	{
		slog("entityList not initialized");
		return;
	}
	for(i = 0; i < entityMax; ++i)
	{
		entity = &entityList[i];
		entity_free(&entity);
	}
	entityNum = 0;
	free(entityList);
	entityList = NULL;
}

void entity_initialize_system(int maxEntity)
{
	int i;
	if(maxEntity == 0)
	{
		slog("Max entity == 0");
		return;
	}
	entityList = (Entity *) malloc (sizeof (Entity) * maxEntity);
	if(!entityList)
	{
		slog("failed to initialize entityList");
		return;
	}
	memset(entityList, 0, sizeof (Entity) * maxEntity);
	entityNum = 0;
	for(i = 0; i < maxEntity; ++i)
	{
		entityList[i].sprite = NULL;
	}
	entityMax = maxEntity;
	atexit(entity_close_system);
}

void entity_think_all()
{
	int i;
	for(i = 0; i < entityMax; i++)
	{
		if(!entityList[i].inUse)
		{
			continue;
		}

		if(!entityList[i].think)
		{
			continue;
		}

		entityList[i].think(&entityList[i]);
	}
}

void entity_update_all()
{
	int i;
	for(i = 0; i < entityMax; i++)
	{
		if(!entityList[i].inUse)
		{
			continue;
		}

		vect2d_add(entityList[i].position, entityList[i].velocity, entityList[i].position);
		
		if(!entityList[i].update)
		{
			continue;
		}

		entityList[i].update(&entityList[i]);
	}
}

void entity_draw_all()
{
	int i;
	for(i = 0; i < entityMax; i++)
	{
		if(!entityList[i].inUse)
		{
			continue;
		}
		if(!entityList[i].draw)
		{
			continue;
		}
		entityList[i].draw(entityList[i].sprite, entityList[i].frame, entityList[i].position);
	}
}

void entity_draw(Entity *entity)
{
	entity->draw(entity->sprite, entity->frame, entity->position);
}

Entity *entity_load(Entity *entity, char file[], int frameW, int frameH, int fpl, Vect2d position, Vect2d velocity)
{
	entity->sprite = sprite_load(file, frameW, frameH, fpl);
	entity->position = position;
	entity->velocity = velocity;
	entity->bounds = rect(0, 0, frameW, frameH);
	return entity;
}

void entity_intersect_all(Entity *a)
{
	int i;
	if(!a)
		return;
	for(i = 0; i  < entityMax; i++)
	{
		if(!entityList[i].inUse)
		{
			continue;
		}
		/* don't check yourself*/
		if(a == &entityList[i])
		{
			continue;
		}
		/* this only tells you which entity you are intersecting thats first in the list*/
		if(entity_intersect(a, &entityList[i]))
		{
			if(a->touch)
			{
				a->touch(a, &entityList[i]);
			}
			if(entityList[i].touch)
			{
				entityList[i].touch(&entityList[i], a);
			}
		}
	}
	return;
}

int entity_intersect(Entity *a, Entity *b)
{
	SDL_Rect aB, bB;
	if(!a || !b)
	{
		slog("entity error");
		return 0;
	}
	aB = rect(a->position.x + a->bounds.x,
				a->position.y + a->bounds.y,
				a->bounds.w,
				a->bounds.h
		);
	bB = rect(b->position.x + b->bounds.x,
				b->position.y + b->bounds.y,
				b->bounds.w,
				b->bounds.h
		);
	return rect_intersect(aB, bB);
}
