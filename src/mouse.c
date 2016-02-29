#include "mouse.h"

static Entity *mouse = NULL;

void mouse_init()
{
	Vect2d pos, vel;
	pos = vect2d_new(0, 0);
	vel = vect2d_new(0, 0);
	mouse = entity_new();
	mouse = entity_load(mouse, "images/mouse.png", 16, 16, 16, pos, vel);
	if(mouse->sprite == NULL)
	{
		slog("Mouse didn't load");
	}
	SDL_ShowCursor(SDL_DISABLE );
	mouse->frame = 0;
	mouse->draw = &sprite_draw;
	mouse->think = &mouse_think;
	mouse->update = &mouse_update;
	mouse->touch = &mouse_touch;
}

void mouse_think(Entity *mouse)
{
	//click behavior goes here
}

void mouse_update(Entity *self)
{
	int mouseX, mouseY;
	Vect2d mousePos;
	SDL_GetMouseState(&mouseX, &mouseY);
	mousePos = vect2d_new(mouseX, mouseY);
	if(mouse != NULL)
	{
		mouse->position = mousePos;
	}
}

void mouse_touch(Entity *self, Entity *other)
{
	slog("collision");
}
