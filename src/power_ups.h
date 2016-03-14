#ifndef __POWER_UPS_H__
#define __POWER_UPS_H__

#include "entity.h"

Entity *power_up_spawn(int id, int targetID, float x, float y);

void power_up_update(Entity *power_up);

void power_up_free(Entity *power_up);

/*
Double Tap code
*/

void power_up_double_tap(Entity *double_tap, int id, int targetID, float x, float y);

void power_up_double_tap_touch(Entity *double_tap, Entity *other);


#endif
