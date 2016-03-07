#include "camera.h"
#include "simple_logger.h"

static Entity *camera = NULL;

void camera_initialize(Vect2d position, Vect2d dimensions, int id, int targetID)
{
	SDL_Rect bounds;
	SDL_Rect cameraBounds;
	camera = entity_new();
	bounds = rect(position.x, position.y, dimensions.x, dimensions.y);
	cameraBounds = rect(position.x, position.y, dimensions.x / 2, dimensions.y / 2);
	camera->id = id;
	camera->target = entity_get_by_id(targetID);
	camera->bounds = bounds;
	camera->cameraBounds = cameraBounds;
	camera->position = position;
	camera->cameraEnt = 1;
	camera->think = &camera_think;
	camera->update = &camera_update;
	camera->touch = &camera_only_touching_bounds;
}

void camera_think(Entity *self)
{
	if(!self)
	{
		slog("self doesn't point to anything");
		return;
	}
	entity_intersect_all(self);
}

void camera_update(Entity *self)
{
	if(!self)
	{
		slog("self doesn't point to anything");
		return;
	}
	self->position.x = self->target->position.x - 200; // this sets the camera so that pep is always on the same x position on the screen
}

void camera_only_touching_bounds(Entity *self, Entity *other)
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