#include "camera.h"
#include "simple_logger.h"

static Entity *camera = NULL;
#define MOVEMENT_SPEED_X	1
#define MOVEMENT_SPEED_Y	0

void camera_initialize(Vect2d position, Vect2d dimensions, int id)
{
	Vect2d vel;
	SDL_Rect bounds;
	vect2d_set(vel, MOVEMENT_SPEED_X, MOVEMENT_SPEED_Y);
	camera = entity_new();
	bounds = rect(position.x, position.y, dimensions.x, dimensions.y);
	camera->id = id;
	camera->bounds = bounds;
	camera->position = position;
	camera->velocity = vel;
	camera->think = &camera_think;
	camera->update = &camera_update;
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
}

void camera_update(Entity *self)
{
	if(!self)
	{
		slog("self doesn't point to anything");
		return;
	}
	vect2d_add(self->position, self->velocity, self->position);

	//only draw things once, if I left camera touch always on it would draw twice 
	self->touch = &camera_touch;
	entity_intersect_all(self);
	self->touch = NULL;
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

//use this for all bullets, power_ups, and enemies after they have reached the screen
void camera_free_entity_outside_bounds(Entity *ent)
{
	if(!entity_intersect(camera, ent))
	{
		ent->free(ent);
	}
}