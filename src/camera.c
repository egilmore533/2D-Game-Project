#include "camera.h"
#include "simple_logger.h"

static Entity *camera = NULL;

void camera_initialize(Vect2d position, Vect2d dimensions)
{
	SDL_Rect bounds;
	camera = entity_new();
	bounds = rect(position.x, position.y, dimensions.x, dimensions.y);
	camera->bounds = bounds;
	camera->position = position;
	camera->cameraEnt = 1;
	camera->think = &camera_think;
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
}

void camera_update(Entity *self)
{
	if(!self)
	{
		slog("self doesn't point to anything");
		return;
	}
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
	//if an entity is touching the camera draw it
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