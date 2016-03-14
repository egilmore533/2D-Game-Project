#include "level.h"
#include "simple_logger.h"
#include <string.h>
#include <stdio.h>
#include "entity.h"
#include "melt.h"
#include "power_ups.h"

static Level level;
extern SDL_Surface *screen;

void level_load(char filename[])
{
	FILE *levelfile = NULL;
	char buf[128];
	int linenum = 0;

	//background loading storage
	char background_file[128];
	int width, height;
	int i;
	Sprite * temp;

	//entity loading storage 
	char entity_type[30];
	Entity *ent = NULL;
	int id;
	int targetID;
	float x, y;

	levelfile = fopen(filename,"r");
	if (levelfile == NULL)
	{
		slog("could not open file: %s",filename);
		return;
	}
	while(fscanf(levelfile, "%s", buf) != EOF)
	{
		linenum++;
		slog("%s: linenum %i", buf, linenum);
		// # are bash comments skip these lines
		if (buf[0] == '#')
		{
			fgets(buf, sizeof(buf), levelfile);
		}
		else if (strncmp(buf,"image:",128)==0)
		{
			fscanf(levelfile,"%s",background_file);
			slog("backgroundfile %s", background_file);
		}
		else if (strncmp(buf,"width:",128)==0)
		{
			fscanf(levelfile,"%i",&width); 
			slog("width %i",width);
		}
		else if (strncmp(buf,"height:",128)==0)
		{
			fscanf(levelfile,"%i",&height);
			slog("height %i",height);
		}

		//this signifies the end of a entity, needs to be after every entity even the last one before the end of the list
		else if(buf[0] == '~')
		{
			if(strncmp(entity_type, "melt", 30))
			{
				melt_load(ent, id, targetID, x, y);
			}
			else if(strncmp(entity_type, "double tap", 30))
			{
				power_up_double_tap(ent, id, targetID, x, y);
			}
		}
		else if(strncmp(buf,"entity:",128) == 0)
		{
			fscanf(levelfile,"%s",entity_type);
			slog("entity_type %s",entity_type);
		}
		else if(strncmp(buf,"id:",128))
		{
			fscanf(levelfile,"%i",&id);
			slog("id %i",id);
		}
		else if(strncmp(buf,"target:",128))
		{
			fscanf(levelfile,"%i",&targetID);
			slog("targetID %i",targetID);
		}
		else if(strncmp(buf,"x_position:",128))
		{
			fscanf(levelfile,"%i",&x);
			slog("x %i",x);
		}
		else if(strncmp(buf,"y_position:",128))
		{
			fscanf(levelfile,"%i",&y);
			slog("y %i",y);
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
	level.file = filename;
	
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
