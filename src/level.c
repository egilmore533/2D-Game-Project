#include "level.h"
#include "simple_logger.h"
#include <string.h>
#include <stdio.h>

static Level level;
extern SDL_Surface *screen;

void level_load(char *filename)
{
	FILE *levelfile = NULL;
	char buf[128];
	char background_file[128];
	int width, height;
	int i;
	Sprite * temp;

	levelfile = fopen(filename,"r");
	if (levelfile == NULL)
	{
		slog("could not open file: %s",filename);
		return;
	}
	while(fscanf(levelfile, "%s", buf) != EOF)
	{
		// # are bash comments skip these lines
		if (buf[0] == '#')
		{
			fgets(buf, sizeof(buf), levelfile);
		}
		else if (strncmp(buf,"image:",128)==0)
		{
			fscanf(levelfile,"%s",background_file);
		}
		else if (strncmp(buf,"width:",128)==0)
		{
			fscanf(levelfile,"%i",&width);      
		}
		else if (strncmp(buf,"height:",128)==0)
		{
			fscanf(levelfile,"%i",&height);      
		}
		else
		{
			/*eat up the rest of this line, and ignore it*/
			fgets(buf, sizeof(buf), levelfile);
		}
	}

	fclose(levelfile);
	temp = sprite_load(background_file, width, height, 1);
	if (!temp)
	{
		slog("could not open sprite file: %s",background_file);
		return;
	}
	level_close();
	level.loaded = 1;
	level.background = temp;
	
}

void level_close()
{
	if (!level.loaded)
	{
		return;
	}
	if (level.background != NULL)
	{
		sprite_free(&level.background);
	}
}

void level_initialize_system()
{
	memset(&level,0,sizeof(Level));
	atexit(level_close);
}

Level *level_get()
{
	return &level;
}
