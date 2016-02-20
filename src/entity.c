#include "entity.h"
#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include "simple_logger.h"
#include "graphics.h"

Entity *entityList = NULL;
int entityNum;
int entityMax = 0;

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

	*entity = NULL;
}

Entity *entity_new()
{
	int i;
	for(i = 0; i < entityMax; i++)
	{
		if(entityList[i].inUse)
		{
			continue;
		}
		memset(&entityList[i],0,sizeof(Entity));
		entityList[i].inUse = 1;
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
		slog("Max sprite == 0");
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
		entityList[i].draw(entityList[i].sprite, entityList[i].frame, entityList[i].sprite->frameW, entityList[i].sprite->frameH);
	}
}

Entity *entity_load(Entity *entity, char file[], int frameW, int frameH, Vect2d position, Vect2d velocity)
{
	entity->sprite = sprite_load(file, frameW, frameH);
	entity->position = position;
	entity->velocity = velocity;
	
	return entity;
}
