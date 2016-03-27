#include <stdio.h>

#include "graphics.h"
#include "simple_logger.h"
#include "particle.h"
#include "camera.h"
#include "level.h"
#include "player.h"
#include "files.h"

#include "backgrounds.h"


void initialize_all(Uint8 level_number);
void clean_up_all();
void initialize_next_level(Uint8 level_number);

/*this program must be run from the directory directly below images and src, not from within src*/
/*notice the default arguments for main.  SDL expects main to look like that, so don't change it*/
int main(int argc, char *argv[])
{
	int done;
	Level *level;
	const Uint8 *keys;
	SDL_Renderer *the_renderer;
	Entity *player;
	Uint8 levelnum = 1;

	Background *background1;
	Background *background2;
	Background *background3;
  
	Vect2d pos;
	pos = vect2d_new(0,0);

	initialize_all(levelnum++);
	level = level_get();
	
	the_renderer = graphics_get_renderer();
	player = player_get();
	done = 0;
	do
	{
		if(player->position.x > level->end)
		{
			if(levelnum > LEVEL_NUM)
			{
				//you did it, if I have a score system I would show that before exiting or something along those lines but for now exit
				exit(0);
			}
			//start the next level
			clean_up_all();
			initialize_next_level(levelnum++);
		}
		SDL_RenderClear(the_renderer);
		
		sprite_draw(level->background, 0, pos);

		background_update_all();
		background_draw_all();

		entity_think_all();
		entity_update_all();

		particle_check_all_dead();
		particle_draw_all();

		graphics_next_frame();
		SDL_PumpEvents();

		keys = SDL_GetKeyboardState(NULL);
		if(keys[SDL_SCANCODE_ESCAPE])
		{
			done = 1;
		}
	}while(!done);
	exit(0);		/*technically this will end the program, but the compiler likes all functions that can return a value TO return a value*/
	return 0;
}

void clean_up_all()
{
	level_close();
	background_close_system();
	particle_close_system();
	entity_close_system();
	sprite_close_system();
	
	/*any other cleanup functions can be added here*/ 
}

void initialize_all(Uint8 level_number)
{
	int width = 1366;
	int height = 768;
	Vect2d cameraPosition, cameraDimensions;

	graphics_initialize("Pep's Spicy Adventure", width, height, width, height, 0);

  
	init_logger("text/log.txt"); //init simple logger from DJ's source code
	sprite_initialize_system(1000);//sprite.c needs to initialize before the game starts to load sprites
	entity_initialize_system(100); // entity after sprites
	particle_initialize_system(2000); //particle after entity
	level_initialize_system();
	
	cameraPosition = vect2d_new(0,0);
	cameraDimensions = vect2d_new(width, height);
	camera_initialize(cameraPosition, cameraDimensions, 0);
	background_initialize_system(10);
	level_load(level_number);
	atexit(clean_up_all);
}

void initialize_next_level(Uint8 level_number)
{
	int width = 1366;
	int height = 768;
	Vect2d cameraPosition, cameraDimensions;
	sprite_initialize_system(1000);//sprite.c needs to initialize before the game starts to load sprites
	entity_initialize_system(100); // entity after sprites
	particle_initialize_system(2000); //particle after entity
	cameraPosition = vect2d_new(0,0);
	cameraDimensions = vect2d_new(width, height);
	camera_initialize(cameraPosition, cameraDimensions, 0);
	background_initialize_system(10);
	level_load(level_number);
}
