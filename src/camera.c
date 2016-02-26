#include "camera.h"

static SDL_Rect _Camera = {0,0,0,0};

SDL_Rect camera_get_active()
{
	return _Camera;
}

Vect2d camera_get_position()
{
	Vect2d pos = {_Camera.x, _Camera.y};
	return pos;
}

void camera_set_position(Vect2d pos)
{
	_Camera.x = pos.x;
	_Camera.y = pos.y;
}

void camera_set_size(Vect2d size)
{
	_Camera.w = size.x;
	_Camera.h = size.y;
}

Vect2d camera_get_size()
{
	Vect2d size = {_Camera.w, _Camera.h};
	return size;
}
