#ifndef _ENTITY_H__
#define _ENTITY_H__

#include "vector.h"
#include "sprite.h"

/** @brief	A macro that defines maximum inventory. */
#define MAX_INVENTORY	12


/** @brief	entity structure w/ flag to know if that entity is being used, position, velocity, bounding box,   
/**			flag to know if it is the camera, sprite, current frame, inventory array, current state of the entity,   
/**			and min/max health  
/**			function pointers - for drawing, thinking, updating, touching, and freeing */
typedef struct Entity_s
{
	int inUse;							/**< flag to know if the entity is currently active */
	Vect2d position;					/**< x and y coordinates of the entity */
	Vect2d velocity;					/**< x and y velocities that the entity is moving */
	SDL_Rect bounds;					/**< the bounding box of the entity */
	int cameraEnt;						/**< flag that is set to 1 if the entity is a camera*/
	Sprite *sprite;						/**< sprite component of the entity */
	int frame;							/**< frame numebr the entity is on */
	int inventory[MAX_INVENTORY];		/**< count of how many each item the entity is holding */
	int state;							/**< what state the enemy is in, states will need to be enumerated */
	int health, maxHealth;				/**< the current healt and total health of the entity */
	
	void (*draw)(Sprite *sprite,
				 int frame, 
				 Vect2d drawPos);			/**< draw function for the entity, most if not all entities will just be using sprite_draw */
	int nextThink;							/**< stuff for thinking and the think rate */
	int thinkRate;							/**< rate of thinking */
	void (*think) (struct Entity_s *self);	/**< behavior of the entity will be defined in the think function */
	void (*update) (struct Entity_s *self);	/**< update function for changing the entity's data */
	void (*touch) (struct Entity_s *self,	
				   struct Entity_s *other); /**< collision behavior of the entity */
	void (*free) (struct Entity_s *self);	/**< function to free the entity's structs */

}Entity;

/**
 * @brief	creates a new entity, allocates memory for it and returns it
 * @return	A pointer to the new entity.
 */
Entity *entity_new();

/**
 * @brief	Free's the entity from memory and then free's the pointer to that entity.
 * @param [in,out]	double pointer to the entity.
 */
void entity_free(Entity **entity);

/**
 * @brief	Initializes the entity system by allocating space for the entityList.
 * @param	maxEntity	the maximum number of entities for the game saved in a static variable for later use.
 */
void entity_initialize_system(int maxEntity);


/** @brief	go through entity list and draw them all to renderer. */
void entity_draw_all();


/** @brief	go through entity list and add velocities to positions. */
void entity_update_all();


/** @brief	go through all the entities and have them think. */
void entity_think_all();


/** @brief	closes the entity system by freeing the entire entityList and setting the number   
/**			of entities in the list to 0. */
void entity_close_system();


/** @brief	draws an entity if the entity is in side the cameras bounds. */
void entity_draw();

/**
 * @brief	entity constructor.
 * @param [in,out]	entity	If non-null, the entity.
 * @param	file		  	The filename for the entity's sprite.
 * @param	frameW		  	The frame width.
 * @param	frameH		  	The frame height.
 * @param	fpl			  	The frames per line.
 * @param	position	  	The x y coordinates.
 * @param	velocity	  	The x and y velocities.
 * @return	null if it fails, else an Entity* that has been loaded with given parameters.
 */
Entity *entity_load(Entity *entity, char file[], int frameW, int frameH, int fpl, Vect2d position, Vect2d velocity);

/**
 * @brief	check's if the two given entities are inside each other's bounding box's using rect_intersect defined in vector.h.
 * @param [in,out]	a	If non-null, the Entity to process.
 * @param [in,out]	b	If non-null, the Entity to process.
 * @return	1 if the entities are intersecting, else 0.
 */
int entity_intersect(Entity *a, Entity *b);

/**
 * @brief	go through entire entity list checking if the given ent perfroming touch functions if either entity has them.
 * @param [in,out]	a	If non-null, the Entity to process.
 */
void entity_intersect_all(Entity *a);

#endif 