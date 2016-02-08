#include <stdlib.h>
#include "SDL.h"
#include "SDL_image.h"
#include "graphics.h"
#include <string.h>
#include <stdio.h>
#include <sstream> /*sstream is for timers*/
#include "shot.h"
#include "particles.h"


extern SDL_Surface *screen;
extern SDL_Surface *buffer; /*pointer to the draw buffer*/
extern SDL_Rect Camera;

void Init_All();

int getImagePathFromFile(char *filepath,char * filename);
int getCoordinatesFromFile(int *x, int *y,char * filename);
void addCoordinateToFile(char *filepath,int x, int y);

/*
//initilize to use renderer instead of just surfaces
bool init(SDL_Window *gWindow, SDL_Renderer *gRenderer)
{
	bool success = true;
	Uint32 flags = 0;
	int imgFlags;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if(!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ))
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		gWindow = SDL_CreateWindow("Pep's Spicy Adventure", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 400, flags);
		if(gWindow == NULL)
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if(gRenderer == NULL)
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}
*/

/*this program must be run from the directory directly below images and src, not from within src*/
/*notice the default arguments for main.  SDL expects main to look like that, so don't change it*/
int main(int argc, char *argv[])
{
	SDL_Surface *tempSurface; //background img

	//for particle system
	LTexture *texture = (LTexture *)malloc(sizeof(LTexture *));
	//Shot *shot = (Shot *)malloc(sizeof(Shot *));
	//LTexture *gRedTexture = (LTexture *)malloc(sizeof(LTexture *));
	//LTexture *gGreenTexture = (LTexture *)malloc(sizeof(LTexture *));
	//LTexture *gBlueTexture = (LTexture *)malloc(sizeof(LTexture *));

	int done;
	int tx = 0,ty = 0;
	const Uint8 *keys;
	char imagepath[512];
	SDL_Rect srcRect={0,0,800,600};
	

	/*
	if(!init(gWindow, gRenderer))
	{
	printf("Failed to initialize Window and Renderer\n");
	exit(0);
	return 0;
	}

	else
	{
	bitmapSurface = IMG_Load("images/bgtest.png");
	bitmapTex = SDL_CreateTextureFromSurface(gRenderer, bitmapSurface);
	if(bitmapTex == NULL)
	{
		printf("Unable to create texture! SDL Error: %s\n", SDL_GetError());
	}
	SDL_FreeSurface(bitmapSurface);

	while (1) {
		SDL_Event e;
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				break;
			}
		}

		SDL_RenderClear(gRenderer);
		SDL_RenderCopy(gRenderer, bitmapTex, NULL, NULL);
		SDL_RenderPresent(gRenderer);
	}
	/*
	
	if(loadFromFile(texture, "images/bgtest.png", gRenderer))
	{
		printf("background loaded succesfully\n");
		done = 0;
		do
		{
			DrawMouse();
			NextFrame();
			SDL_PumpEvents();
			keys = SDL_GetKeyboardState(NULL);
			if(keys[SDL_SCANCODE_ESCAPE])
			{
				done = 1;
			}
		}
		while(!done);
	}
	else
	{
		printf("Failed to initialize Background\n");
		exit(0);
		return 0;
	}
	
	}
	*/

	Init_All();
	tempSurface = IMG_Load("images/bgtest.png"); //notice that the path is part of the filename
	if(tempSurface != NULL)
	{
		printf("temp image loaded successfully\n");
		SDL_BlitSurface(tempSurface,NULL,buffer,NULL);
	}
	gt_graphics_render_surface_to_screen(tempSurface,srcRect,0,0);
	SDL_FreeSurface(tempSurface);
	//loadMedia(gRedTexture, gGreenTexture, gBlueTexture);
	//addShot(shot);
	loadFromFile(texture, "images/shot.png");
	renderLTexture(texture, 200, 200);
	//loadFromFile(shot->mTexture, "images/shot.png");
	//loadFromFile(gRedTexture, "images/redSpark.png");
	//loadFromFile(gGreenTexture, "images/greenSpark.png");
	//loadFromFile(gBlueTexture, "images/blueSpark.png");
	done = 0;
	do
	{
	ResetBuffer();
	DrawMouse();
	NextFrame();
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
  CloseSprites();
  /*any other cleanup functions can be added here*/ 
}

void Init_All()
{
	float bgcolor[] = {1,1,1,1};
  Init_Graphics(
	"Game Test",
    800,
    500,
    800,
    500,
    bgcolor,
    0);

  InitMouse();
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
