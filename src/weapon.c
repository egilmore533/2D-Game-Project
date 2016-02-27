#include "weapon.h"

void weapon_fire(Entity *entity)
{
	Entity *spice;
	Vect2d pos, vel;
	int offsetX = 128; // this is the offset needed for pep's sprite this would change depending on the size of the sprite and where the bullet would come out
	int offsetY = 40; // this is the offset needed for pep's sprite this would change depending on the size of the sprite and where the bullet would come out
	if(!entity)
	{
		slog("No entity to fire from");
		return;
	}

	pos = vect2d_new(entity->position.x + offsetX, entity->position.y + offsetY);
	vel = vect2d_new(15, 0);

	spice = entity_new(); 
	spice = entity_load(spice, "images/Shot.png", 64, 64, 16, pos, vel);
	spice->draw = &sprite_draw;
}
