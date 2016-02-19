#ifndef _ENTITY_H__
#define _ENTITY_H__

#include "vector.h"
#include "sprite.h"

#define MAX_INVENTORY	12


/** @brief	entity structure containng position, velocity, sprite, frame number, health   
/**			info and a flag to denote if its active */
typedef struct Entity_s
{
	int inUse;							/**<flag to know if the entity is currently active */
	Vect2d position;					/**<x and y coordinates of the entity */
	Vect2d velocity;					/**<x and y velocities that the entity is moving */
	Sprite *sprite;						/**<sprite component of the entity */
	int frame;							/**<frame numebr the entity is on */
	int inventory[MAX_INVENTORY];					/**<count of how many each item the entity is holding */
	int state;							/**< what state the enemy is in, states will need to be enumerated */
	int health, maxHealth;				/**<the current healt and total health of the entity */
	
	void (*draw)(struct Entity_s *self, SDL_Renderer *renderer);
	int nextThink;
	int thinkRate;
	void (*think) (struct Entity_s *self);		/**<each entity will need to have its own think function */
	void (*update) (struct Entity_s *self);
	void (*touch) (struct Entity_s *self, struct Entity_s *other);
	void (*free) (struct Entity_s *self);

}Entity;

/**
 * @brief	creates a new entity, allocates memory for it and returns a pointer to the entity
 * @return	An new Entity.
 */
Entity *entity_new();

/**
 * @brief	Free's the entity from memory.
 * @param [in,out]	entity	If non-null, the entity.
 */
void entity_free(Entity **entity);


/** @brief	Initializes the entity system by allocating space for the entityList according to   
/**			information in entity.c */
void entity_initialize_system(int maxEntity);


/** @brief	go through entity list and draw them all to renderer. */
void entity_draw_all();


/** @brief	go through entity list and add velocities to positions. */
void entity_update_all();


void entity_think_all();


/** @brief	closes the entity system by freeing the entire entityList and setting the number   
/**			of entities in the list to 0. */
void entity_close_system();

#endif 