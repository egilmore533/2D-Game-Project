#include "camera.h"

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
	
}

void camera_update(Entity *self)
{
	
}

void camera_touch(Entity *self, Entity *other)
{
	//if an entity is touching the camera draw it
	entity_draw(other);
}

Entity *camera_get()
{
	return camera;
}