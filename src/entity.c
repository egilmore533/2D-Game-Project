#include "entity.h"
#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>

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
	Entity *entityNew = (Entity *) malloc (sizeof (Entity));


	return entityNew;
}

void entity_close_system()
{
	int i;
	Entity *entity;
	for(i = 0; i < entityMax; ++i)
	{
		entity = &entityList[i];
		entity_free(&entity);
	}
	entityNum = 0;
	memset(entityList, 0, sizeof(Sprite) * entityMax);
}

void entity_init_system(int maxEntity)
{
	int i;
	if(maxEntity == 0)
	{
		printf("Max sprite == 0\n");
		return;
	}
	entityList = (Entity *) malloc (sizeof (Entity) * maxEntity);
	memset(entityList, 0, sizeof (Entity) * maxEntity);
	entityNum = 0;
	for(i = 0; i < maxEntity; ++i)
	{
		entityList[i].sprite = NULL;
	}
	entityMax = maxEntity;
	atexit(entity_close_system);
}


