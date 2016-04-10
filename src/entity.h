#ifndef _ENTITY_H__
#define _ENTITY_H__

#include "vector.h"
#include "sprite.h"

/** @file	entity.h
 *	@brief	Entity System, handles how each entity updates, thinks, collides with other entities, and is drawn
 */


////////////////////Inventory/////////////////////
/** @brief	A macro that defines maximum inventory. */
#define MAX_INVENTORY	12

/** @brief A macro that defines which slot is the the lives in the player's inventory */
#define LIVES_SLOT		0

/** @brief  A macro that defines which slot is the bomb slot in the player's inventory */
#define BOMB_SLOT		1

/** @brief A macro that defines which slot is the the spread shots in the player's inventory 0 means normal firing, each one added gives two extra shots */
#define SPREAD_SLOT		2 


//////////////////////Entity States///////////////////////////////////
/** @brief entity is in the normal state */
#define NORMAL_STATE	0

/** @brief player is being shielded by the heat_shield*/
#define SHIELDED_STATE	1

/** @brief enemy has been stickied by the goo shot */
#define STICKIED_STATE	2

//////////////////Bullet States//////////////////////////////
/** @brief bullet is in the normal state*/
#define NORMAL_SHOT_STATE	0

/** @brief bullet will sticky the enemy it strikes*/
#define GOO_SHOT_STATE		1



/** 
 * @struct	Entity structure
 * @brief	anything that can act or be acted upon (Enemies, players, power_ups, weapons, etc.) 
 */
typedef struct Entity_s
{
	int inUse;							/**< flag to know if the entity is currently active */
	int id;								/**< id of the entity to find it */
	Vect2d position;					/**< x and y coordinates of the entity */
	Vect2d velocity;					/**< x and y velocities that the entity is moving */
	Vect2d direction;					/**< normalized vector of which way the entity will be moving */
	SDL_Rect bounds;					/**< the bounding box of the entity, determined by the sprite */
	
	Sprite *sprite;						/**< sprite component of the entity */
	int frame;							/**< frame number the entity is on */
	int inventory[MAX_INVENTORY];		/**< count of how many each item the entity is holding */
	int health;							/**< the current health of the entity */
	Uint8  state;						/**< special states for each entity type (ie: stickied enemy, shielded player, goo bullet)*/
	Uint8  bullet_state;				/**< the state an entities bullets will be in*/

	struct Entity_s *owner;				/**< the owner of the entity, such as the entity that fired the bullet */
	struct Entity_s *target;			/**< the target of this struct (ie: entity will be chasing player, power_up gives player a shield) */

	void (*draw)(Sprite *sprite,
				 int frame, 
				 Vect2d drawPos);			/**< draw function for the entity, most if not all entities will just be using sprite_draw */
	Uint32 nextThink;						/**< the next moment the entity will think */
	Uint32 thinkRate;						/**< how long the entity will wait to think again */
	void (*think) (struct Entity_s *self);	/**< behavior of the entity */
	void (*update) (struct Entity_s *self);	/**< update function for changing the entity's data and checking its status */
	void (*touch) (struct Entity_s *self,	
				   struct Entity_s *other); /**< collision behavior of the entity */
	void (*free) (struct Entity_s *self);	/**< function to free the entity */

}Entity;

/**
 * @brief	creates a new entity in the entity list, sets it to being used and returns a pointer to the entity in that position
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


/** @brief	go through entity list and draw them all to renderer. Not used anymore. */
void entity_draw_all();


/** @brief	go through entity list and if the entity is inuse and has an update then run that update function. */
void entity_update_all();


/** @brief	go through all the entities and have them think if they have a think function. */
void entity_think_all();


/** 
 *  @brief	closes the entity system by freeing the entire entityList and setting the number   
 *	   		 of entities in the list to 0. 
 */
void entity_close_system();


/** 
 *  @brief	draws an entity to the screen using sprite_draw   
 *  @param	entity	the entity in question
 */
void entity_draw(Entity *entity);

/**
 * @brief	loads the entity's sprite and creates the bounding box based on the size of the frame.
 * @param [in,out]	entity	If non-null, the entity.
 * @param	file		  	The filename for the entity's sprite.
 * @param	frameW		  	The frame width.
 * @param	frameH		  	The frame height.
 * @param	fpl			  	The frames per line.
 * @return	null if it fails, else an Entity* that has been loaded with given parameters.
 */
Entity *entity_load(Entity *entity, char file[], int frameW, int frameH, int fpl);

/**
 * @brief	checks if the two given entities are inside each other's bounding box's using rect_intersect defined in vector.h.
 * @param [in,out]	a	If non-null, the Entity to process.
 * @param [in,out]	b	If non-null, the Entity to process.
 * @return	1 if the entities are intersecting, else 0.
 */
int entity_intersect(Entity *a, Entity *b);

/**
 * @brief	go through all active entities checking if the given ent is colliding with any others, perfroming touch functions if either entity has them.
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