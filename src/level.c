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
	level.file = filename;
	
}

void level_entity_load()
{
	FILE *levelfile = NULL;
	char buf[128];
	
	char entity_type[30];
	Entity *ent = NULL;
	int id;
	int targetID;
	float x, y;
	
	levelfile = fopen(level.file,"r");
	if (levelfile == NULL)
	{
		slog("could not open file: %s",level.file);
		return;
	}
	while(fscanf(levelfile, "%s", buf) != EOF)
	{
		//this signifies the start of the entity list in the level file
		if(strncmp(buf,"===Entity List===",128))
		{
			while(fscanf(levelfile,"%s", buf) != EOF)
			{
				/*
				Needs to identify the entity list start
					It needs to identify the start of an entity
						It needs to store the entity type its going to load, its id, targetID, and x & y position values
						It needs to identify the end of a specific entity and load one with the stored values	
					Repeat finding the start of an entity.
				stop loading when it identifies the end of the list
				*/
				if (buf[0] == '#')
				{
					fgets(buf, sizeof(buf), levelfile);
				}
				//this signifies the end of a entity, needs to be after every entity even the last one before the end of the list
				else if(strncmp(buf, "~", 128) == 0)
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
					fscanf(levelfile,"%s",&entity_type);
				}
				else if(strncmp(buf,"id:",128))
				{
					fscanf(levelfile,"%i",&id);
				}
				else if(strncmp(buf,"target:",128))
				{
					fscanf(levelfile,"%i",&targetID);
				}
				else if(strncmp(buf,"x:",128))
				{
					fscanf(levelfile,"%f",&x);
				}
				else if(strncmp(buf,"y:",128))
				{
					fscanf(levelfile,"%f",&y);
				}

				//this signifies the end of the entity list in the level file
				else if(strncmp(buf,"===End List===",128) == 0)
				{
					break;
				}
				else
				{
					/*eat up the rest of this line, and ignore it*/
					fgets(buf, sizeof(buf), levelfile);
				}
			}
		}
	}
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
