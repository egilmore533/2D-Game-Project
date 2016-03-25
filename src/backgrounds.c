#include "backgrounds.h"
#include "camera.h"

static Background *backgroundList = NULL;
static int backgroundMax;
static int backgroundNum;

void background_free(Background **background)
{
	Background *self;
	if(!background)
	{
		slog("background isn't pointing to anything");
		return;
	}
	else if(!*background) 
	{
		slog("background pointer isn't pointing to anything");
		return;
	}
	self = *background;
	self->alive--;
	backgroundNum--;
	if(self->sprite != NULL)
	{
		sprite_free(&self->sprite);
	}
	*background = NULL;
}

void background_close_system()
{
	int i;
	Background *background;
	if(!backgroundList)
	{
		slog("backgroundList not initialized");
		return;
	}
	for(i = 0; i < backgroundMax; ++i)
	{
		background = &backgroundList[i];
		background_free(&background);
	}
	backgroundList = NULL;
}

void background_initialize_system(int maxBackground)
{
	int i;
	if(maxBackground == 0)
	{
		slog("maxBackground == 0");
		return;
	}
	backgroundList = (Background *) malloc (sizeof (Background) * maxBackground);
	if(!backgroundList)
	{
		slog("failed to initialize backgroundList");
		return;
	}
	memset(backgroundList, 0, sizeof (Background) * maxBackground);
	for(i = 0; i < maxBackground; ++i)
	{
		backgroundList[i].sprite = NULL;
	}
	backgroundMax = maxBackground;
	atexit(background_close_system);
}

Background *background_new()
{
	int i;
	if(!backgroundList)
	{
		slog("backgroundList not yet initialized");
		return NULL;
	}
	/*makesure we have the room for a new sprite*/
	if(backgroundNum + 1 > backgroundMax)
	{
		slog("Maximum Backgrounds Reached.");
		exit(1);
	}
	for(i = 0; i < backgroundMax; i++)
	{
		if(backgroundList[i].alive)
		{
			continue;
		}
		memset(&backgroundList[i],0,sizeof(Background));
		backgroundList[i].alive = 1;
		backgroundNum++;
		return &backgroundList[i];
	}
	return NULL;
}

void background_draw_all()
{
	int i;
	if(!backgroundList)
	{
		slog("particleList not yet initialized");
		return;
	}
	for(i = 0; i < backgroundMax; i++)
	{
		if(!backgroundList[i].alive)
		{
			continue;
		}
		backgroundList[i].draw(backgroundList[i].sprite, backgroundList[i].frame, backgroundList[i].mainPosition);
		backgroundList[i].draw(backgroundList[i].sprite, backgroundList[i].frame, backgroundList[i].chaserPosition);
	}
}

void background_update_all()
{
	int i;
	if(!backgroundList)
	{
		slog("particleList not yet initialized");
		return;
	}
	for(i = 0; i < backgroundMax; i++)
	{
		if(!backgroundList[i].alive)
		{
			continue;
		}
		backgroundList[i].update(&backgroundList[i]);
	}
}

Background *background_load(char background_file_path[128], float velocityFactor, int width, int height, int fpl)
{
	Background *temp = NULL;
	Vect2d mainPos, chaserPos, vel;
	Entity *cam = camera_get();

	temp = background_new();
	temp->sprite = sprite_load(background_file_path, width, height, fpl);
	
	mainPos = vect2d_new(0, 0);
	chaserPos = vect2d_new(temp->mainPosition.x + width, 0);
	vel = vect2d_new(cam->velocity.x * velocityFactor, cam->velocity.y * velocityFactor);

	temp->mainPosition = mainPos;
	temp->chaserPosition = chaserPos;
	temp->velocity = vel;
	temp->frame = 0;
	temp->draw = &sprite_draw;
	temp->update = &background_update;
	return temp;
}

void background_update(Background *background)
{
	vect2d_add(background->mainPosition, background->velocity, background->mainPosition);
	vect2d_add(background->chaserPosition, background->velocity, background->chaserPosition);

	background->frame++;

	if(background->chaserPosition.x <= camera_get()->position.x)
	{
		background->mainPosition = background->chaserPosition;
		vect2d_set(background->chaserPosition, background->mainPosition.x + background->sprite->frameSize.x, 0);
	}
}