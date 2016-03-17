#include "camera.h"
#include "simple_logger.h"

static Entity *camera = NULL;

void camera_initialize(Vect2d position, Vect2d dimensions, int id)
{
	SDL_Rect bounds;
	camera = entity_new();
	bounds = rect(position.x, position.y, dimensions.x, dimensions.y);
	camera->id = id;
	camera->bounds = bounds;
	camera->position = position;
	camera->think = &camera_think;
	camera->thinkRate = 33;
	camera->nextThink = 0;
	camera->update = &camera_update;
	camera->touch = &camera_touch;
}

void camera_think(Entity *self)
{
	if(!self)
	{
		slog("self doesn't point to anything");
		return;
	}
	if(!(SDL_GetTicks() >= self->nextThink))
	{
		return;
	}
	//move this so camera has it's own velocity, and moves in update like enemies
	self->position.x += 3;
	self->nextThink = SDL_GetTicks() + self->thinkRate;
}

void camera_update(Entity *self)
{
	if(!self)
	{
		slog("self doesn't point to anything");
		return;
	}
	entity_intersect_all(self);
}

void camera_touch(Entity *self, Entity *other)
{
	if(!self)
	{
		slog("self doesn't point to anything");
		return;
	}
	if(!other)
	{
		slog("other doesn't point to anything");
		return;
	}
	//if an entity is touching the camera at all draw it
	entity_draw(other);
}

Entity *camera_get()
{
	if(!camera)
	{
		slog("camera not yet initialized");
		return NULL;
	}
	return camera;
}