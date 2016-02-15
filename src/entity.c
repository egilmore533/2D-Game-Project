#include "entity.h"
#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>

Entity *entityList = NULL;
int numEntity;
int entityMax = 100;

void entity_free(Entity *entity)
{
	entity->inUse--;

	if(entity->sprite != NULL)
	{
		sprite_free(entity->sprite);
	}

	entity->sprite = NULL;
}

Entity *entity_new()
{
	Entity *entityNew = (Entity *) malloc (sizeof (Entity));


	return entityNew;
}

void entity_close_system()
{
	int i;
	for(i = 0; i < entityMax; ++i)
	{
		entity_free(&entityList[i]);
	}
	numEntity = 0;
	memset(entityList, 0, sizeof(Sprite) * entityMax);
}

void entity_init_system()
{
	int i;
	if(entityMax == 0)
	{
		printf("Max sprite == 0\n");
		return;
	}
	entityList = (Entity *) malloc (sizeof (Entity) * entityMax);
	memset(entityList, 0, sizeof (Entity) * entityMax);
	numEntity = 0;
	for(i = 0; i < entityMax; ++i)
	{
		entityList[i].sprite = NULL;
	}
	atexit(entity_close_system);
}


