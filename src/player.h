#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "entity.h"


/** @brief	load's the static player entity by allocating memory and then giving it position, velocity, draw, think, and update. */
void player_load(Entity *player, int id, int target, float x, float y);

/**
 * @brief	input for the player, wasd movement and space to fire projectile.
 * @param [in,out]	player	If non-null, the player.
 */
void player_think(Entity *player);

/**
 * @brief	updates the player's position.
 * @param [in,out]	player	the player entity.
 */
void player_update(Entity *player);

#endif 