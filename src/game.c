#include <stdlib.h>
#include "SDL.h"
#include "SDL_image.h"
#include "graphics.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "sprite.h"
#include "simple_logger.h"
#include "vector.h"
#include "entity.h"
#include "player.h"
#include "mouse.h"
#include "particle.h"
#include "camera.h"
#include "milk_tank.h"
#include "level.h"
#include "celery_stalker.h"
#include "clarence.h"
#include "melt.h"
#include "professor_slice.h"
#include "power_ups.h"

extern SDL_Surface *screen;
extern SDL_Surface *buffer; /*pointer to the draw buffer*/
extern SDL_Rect Camera;

void Init_All();

int getImagePathFromFile(char *filepath,char * filename);
int getCoordinatesFromFile(int *x, int *y,char * filename);
void addCoordinateToFile(char *filepath,int x, int y);

/*this program must be run from the directory directly below images and src, not from within src*/
/*notice the default arguments for main.  SDL expects main to look like that, so don't change it*/
int main(int argc, char *argv[])
{
	int done;
	Level *level;
	int tx = 0,ty = 0;
	const Uint8 *keys;

	Entity *celery_stalker = NULL;
	Entity *celery_stalker2 = NULL;
	Entity *celery_stalker3 = NULL;
	Entity *celery_stalker4 = NULL;
	Entity *celery_stalker5 = NULL;
  
	Vect2d pos, vel;
	pos = vect2d_new(0,0);
	SDL_Rect srcRect={0,0,1024,768};

	Init_All();
	level = level_get();
	power_up_double_tap(celery_stalker, 4, 0, 1200, 200);
	
	done = 0;
	do
	{
		SDL_RenderClear(graphics_get_renderer());
		sprite_draw(level->background, 0, pos);
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

void CleanUpAll()
{
	sprite_close_system();
	/*any other cleanup functions can be added here*/ 
}

void Init_All()
{
	float bgcolor[] = {1,1,1,1};
	int width = 1366;
	int height = 768;
	Vect2d cameraPosition, cameraDimensions;

	graphics_init(
		"Pep's Spicy Adventure",
		width,
		height,
		width,
		height,
		bgcolor,
		0);

  
	init_logger("text/log.txt"); //init simple logger from DJ's source code
	sprite_initialize_system(1000);//sprite.c needs to initialize before the game starts to load sprites
	entity_initialize_system(100); // entity after sprites
	particle_initialize_system(2000); //particle after entity
	level_initialize_system();
	
	
	//this order is important background should init first followed by entities followed by UI and mouse
	level_load("text/level_demo.txt");
	cameraPosition = vect2d_new(0,0);
	cameraDimensions = vect2d_new(width, height);
	camera_initialize(cameraPosition, cameraDimensions, 1);
	player_load();
	//mouse_initialize();
	atexit(CleanUpAll);
}

int getImagePathFromFile(char *filepath,char * filename)
{
    FILE *fileptr = NULL;
    char buf[255];
    int returnValue = -1;
    if (!filepath)
    {
        fprintf(stdout,"getImagePathFromFile: warning, no output parameter provided\n");
        return -1;
    }
    if (!filename)
    {
        fprintf(stdout,"getImagePathFromFile: warning, no input file path provided\n");
        return -1;
    }
    fileptr = fopen(filename,"r");
    if (!fileptr)
    {
        fprintf(stderr,"unable to open file: %s\n",filename);
        return -1;
    }
    if (fscanf(fileptr,"%s",buf))
    {
        if (strcmp(buf,"image:")==0)
        {
            fscanf(fileptr,"%s",filepath);
            returnValue = 0;
        }
    }
    fclose(fileptr);
    return returnValue;
}

void addCoordinateToFile(char *filepath,int x, int y)
{
    FILE *fileptr = NULL;
    if (!filepath)
    {
        fprintf(stdout,"addCoordinateToFile: warning, no input file path provided\n");
        return;
    }
    fileptr = fopen(filepath,"a");
    if (!fileptr)
    {
        fprintf(stderr,"unable to open file: %s\n",filepath);
        return;
    }
    fprintf(fileptr,"%s:%i:newcoordinate: %i %i\n",__FILE__,__LINE__,x,y);
    fclose(fileptr);
}

int getCoordinatesFromFile(int *x, int *y,char * filename)
{
    FILE *fileptr = NULL;
    char buf[255];
    int tx,ty;
    int returnValue = -1;
    if ((!x)&&(!y))
    {
        fprintf(stdout,"getCoordinatesFromFile: warning, no output parameter provided\n");
        return -1;
    }
    if (!filename)
    {
        fprintf(stdout,"getCoordinatesFromFile: warning, no input file path provided\n");
        return -1;
    }
    fileptr = fopen(filename,"r");
    if (!fileptr)
    {
        fprintf(stderr,"unable to open file: %s\n",filename);
        return -1;
    }
    while (fscanf(fileptr,"%s",buf) != EOF)
    {
        fprintf(stdout,"buf is: %s\n",buf);
        if (strcmp(buf,"position:")==0)
        {
            fscanf(fileptr,"%i %i",&tx,&ty);
            fprintf(stdout,"as read: %i, %i\n",tx,ty);
            returnValue = 0;
        }
    }
    fclose(fileptr);
    if (x)*x = tx;
    if (y)*y = ty;
    return returnValue;
}
