#ifndef __BACKGROUNDS_H__
#define __BACKGROUNDS_H__

#include "sprite.h"
#include "simple_logger.h"

typedef struct Background_s
{
	Uint8		alive;
	Sprite		*sprite;

	Vect2d		mainPosition, chaserPosition;
	int			frame;
	Vect2d		velocity;

	void (*draw)	(Sprite *sprite, int frame, Vect2d drawPosition);
	void (*update)	(struct Background_s *self);
	void (*free)	(struct Background_s **self);
}Background;

void background_free(Background **background);
void background_close_system();
void background_initialize_system(int maxBackground);
Background *background_new();

void background_draw_all();
void background_update_all();

Background *background_load(char background_file_path[128], float velocityFactor, int width, int height, int fpl);
void background_update(Background *background);

#endif