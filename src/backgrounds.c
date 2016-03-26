#include "backgrounds.h"
#include "camera.h"

static Background *backgroundList = NULL;
static int backgroundNum;
static int backgroundMax = 0;

void background_free(Background **background)
{
	Background *target;
	if(!background)
	{
		return;
	}
	else if(!*background)
	{
		return;
	}
	target = *background;
	target->alive--;

	if(target->sprite != NULL)
	{
		sprite_free(&target->sprite);
	}
	backgroundNum--;
	*background = NULL;
}

Background *background_new()
{
	int i;
	if(backgroundNum + 1 > backgroundMax)
	{
		slog("Maximum background reached");
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

void background_close_system()
{
	int i;
	Background *background;
	if(!backgroundList)
	{
		slog("backgroundList not initialized");
		return;
	}
	for(i = 0; i < backgroundMax; i++)
	{
		background = &backgroundList[i];
		background_free(&background);
	}
	backgroundNum = 0;
	free(backgroundList);
	backgroundList = NULL;
}

void background_initialize_system(int maxBackground)
{
	int i;
	if(maxBackground == 0)
	{
		slog("Max Background == 0");
		return;
	}
	backgroundList = (Background *) malloc (sizeof (Background) * maxBackground);
	if(!backgroundList)
	{
		slog("failed to initialize entityList");
		return;
	}
	memset(backgroundList, 0, sizeof (Background) * maxBackground);
	backgroundNum = 0;
	for(i = 0; i < maxBackground; i++)
	{
		backgroundList[i].sprite = NULL;
	}
	backgroundMax = maxBackground;
	atexit(background_close_system);
}

void background_update_all()
{
	int i;
	for(i = 0; i < backgroundMax; i++)
	{
		if(!backgroundList[i].alive)
		{
			continue;
		}
		if(!backgroundList[i].update)
		{
			continue;
		}
		backgroundList[i].update(&backgroundList[i]);
	}
}

void background_draw_all()
{
	int i;
	for(i = 0; i < backgroundMax; i++)
	{
		if(!backgroundList[i].alive)
		{
			continue;
		}
		if(!backgroundList[i].draw)
		{
			continue;
		}
		backgroundList[i].draw(backgroundList[i].sprite, backgroundList[i].frame, backgroundList[i].mainPosition);
		backgroundList[i].draw(backgroundList[i].sprite, backgroundList[i].frame, backgroundList[i].chaserPosition);
	}
}

Background *background_load(char background_file_path[128], float velocityFactor, int width, int height, int fpl)
{
	Background *background;
	background = background_new();
	Vect2d mainPos, chaserPos, vel;
	Entity *cam = camera_get();

	if(!background)
	{
		slog("failed to find space for a new background");
		return NULL;
	}
	background->draw = &sprite_draw;
	background->frame = 0;
	background->free = &background_free;
	background->update = &background_update;
	vel = vect2d_new(cam->velocity.x * velocityFactor, 0);
	vect2d_negate(vel, vel);
	mainPos = vect2d_new(cam->position.x, cam->position.y);
	chaserPos = vect2d_new(cam->position.x + width, cam->position.y);
	background->sprite = sprite_load(background_file_path, width, height, fpl);
	background->velocity = vel;
	background->mainPosition = mainPos;
	background->chaserPosition = chaserPos;
	return background;
}


void background_update(Background *background)
{
	vect2d_add(background->mainPosition, background->velocity, background->mainPosition);
	vect2d_add(background->chaserPosition, background->velocity, background->chaserPosition);
	
	if(background->chaserPosition.x <= camera_get()->position.x)
	{
		background->mainPosition = background->chaserPosition;
		background->chaserPosition = vect2d_new(background->mainPosition.x + background->sprite->frameSize.x, 0);

	}
}

