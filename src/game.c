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
  SDL_Surface *temp = NULL;
  int done;
  int tx = 0,ty = 0;
  const Uint8 *keys;
  SDL_Rect srcRect={0,0,1024,768};

  init_logger("log.txt");
  slog("logger initialized");

  Init_All();

  temp = IMG_Load("images/sex.jpg");/*notice that the path is part of the filename*/
  if(temp != NULL)
  {
      slog("temp image loaded successfully");
      SDL_BlitSurface(temp,NULL,buffer,NULL);
  }
  graphics_render_surface_to_screen(temp,srcRect,0,0);

  done = 0;
  do
  {

	SDL_RenderClear(graphics_get_renderer());
	graphics_render_surface_to_screen(temp,srcRect,0,0);
	entity_think_all();
	entity_update_all();

	entity_intersect_all(camera_get());

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
  SDL_FreeSurface(temp);
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

  

  sprite_initialize_system(1000);//sprite.c needs to initialize before the game starts to load sprites
  entity_initialize_system(100); // entity after sprites
  particle_initialize_system(1000); //particle after entity

  cameraPosition = vect2d_new(0,0);
  cameraDimensions = vect2d_new(width, height);
  camera_initialize(cameraPosition, cameraDimensions);

  //this order is important background should init first followed by entities followed by UI and mouse
  player_load();
  mouse_init();
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
