#ifndef _ENTITY_H__
#define _ENTITY_H__

#include "vector.h"
#include "sprite.h"

/** @brief	A macro that defines maximum inventory. */
#define MAX_INVENTORY	12


/** @brief	entity structure with in use flag, id#, position, velocity, direction, bounding box, 
 *			sprite, frame#, inventory array, state, health, maxHealth
 *			owner entity, target entity, projectile entity,
 *			nextThink, and thinkRate(higher the thinkRate the less it thinks)
/**			function pointers - for drawing, thinking, updating, touching, and freeing */
typedef struct Entity_s
{
	int inUse;							/**< flag to know if the entity is currently active */
	int id;								/**< id of the entity to find it */
	Vect2d position;					/**< x and y coordinates of the entity */
	Vect2d velocity;					/**< x and y velocities that the entity is moving */
	Vect2d direction;					/**< normalized vector of which way the  entity will be moving */
	SDL_Rect bounds;					/**< the bounding box of the entity */
	
	Sprite *sprite;						/**< sprite component of the entity */
	int frame;							/**< frame numebr the entity is on */
	int inventory[MAX_INVENTORY];		/**< count of how many each item the entity is holding */
	int health, maxHealth;				/**< the current healt and total health of the entity */

	struct Entity_s *owner;				/**< the owner of the entity, such as the entity that fired the bullet */
	struct Entity_s *target;			/**< the target of this struct (entity will be chasing player) */

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
 * @brief	creates a new entity in the entity list, allocates memory for it and returns a pointer to that position in the entity list
 * @return	A pointer to the new entity in entityList.
 */
Entity *entity_new();

/**
 * @brief	Frees the entity from memory and then frees the pointer to that entity.
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


/** @brief	go through entity list and if the entity is inuse and has an update then run that update function. */
void entity_update_all();


/** @brief	go through all the entities and have them think if they have a think function. */
void entity_think_all();


/** @brief	closes the entity system by freeing the entire entityList and setting the number   
/**			of entities in the list to 0. */
void entity_close_system();


/** @brief	draws an entity to the screen using sprite_draw   
/** @param	entity	the entity in question*/
void entity_draw(Entity *entity);

/**
 * @brief	loads the entitie's sprite and creates the bounding box based on the size of the frame.
 * @param [in,out]	entity	If non-null, the entity.
 * @param	file		  	The filename for the entity's sprite.
 * @param	frameW		  	The frame width.
 * @param	frameH		  	The frame height.
 * @param	fpl			  	The frames per line.
 * @return	null if it fails, else an Entity* that has been loaded with given parameters.
 */
Entity *entity_load(Entity *entity, char file[], int frameW, int frameH, int fpl);

/**
 * @brief	check's if the two given entities are inside each other's bounding box's using rect_intersect defined in vector.h.
 * @param [in,out]	a	If non-null, the Entity to process.
 * @param [in,out]	b	If non-null, the Entity to process.
 * @return	1 if the entities are intersecting, else 0.
 */
int entity_intersect(Entity *a, Entity *b);

/**
 * @brief	go through entire entity list checking if the given ent is colliding with any others, perfroming touch functions if either entity has them.
 * 			used in the main game loop with camera entity so that only the entity's in the camera's bounding box are drawn
 * @param [in,out]	a	If non-null, the Entity to process.
 */
void entity_intersect_all(Entity *a);

/**
 * @brief	returns the entity with the specified id.
 * @param	id	The identifier.
 * @return	null if it fails, else an Entity* with the specified id.
 */
Entity *entity_get_by_id(int id);

#endif 