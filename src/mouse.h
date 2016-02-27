#ifndef __MOUSE_H__
#define __MOUSE_H__

#include "entity.h"
#include "simple_logger.h"

void mouse_init();
void mouse_think(Entity *mouse);
void mouse_update(Entity *mouse);

#endif