#ifndef _ENTITY_H__
#define _ENTITY_H__

#include "vector.h"


/** @brief	entity structure containng position, velocity, sprite, frame number, health info and a flag to denote if its active */
typedef struct Entity_s
{
	int inUse;							/**<flag to know if the entity is currently active */
	Vect2d position;					/**<x and y coordinates of the entity */
	Vect2d veloctiy;					/**<x and y velocities that the entity is moving */
	Sprite *sprite;						/**<sprite component of the entity */
	int frame;							/**<frame numebr the entity is on */
	int inventory[];					/**<count of how many each item the entity is holding */
	int state;							/**< what state the enemy is in, states will need to be enumerated */
	float health, maxHealth;			/**<the current healt and total health of the entity */

	void (*think) (Entity_S *self);		/**<each entity will need to have its own think function */

}Entity;

#endif 