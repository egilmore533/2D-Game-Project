#include "level.h"
#include "simple_logger.h"
#include <string.h>
#include <stdio.h>
#include "entity.h"

#include "player.h"
#include "melt.h"
#include "celery_stalker.h"
#include "professor_slice.h"
#include "milk_tank.h"
#include "clarence.h"
#include "power_ups.h"

#include "files.h"

static Level level;
extern SDL_Surface *screen;

/** @brief the total number of entities the level code is prepared to load */
#define ENTITIES_NUM	12

/** @brief array of function pointers that load entities, used in conjuction with the entity_types array to determine which entity to load and how to load it */
static void (*entity_load_array[ENTITIES_NUM]) (Entity *entity, int id, int target, float x, float y);

/** @breif array of char arrays that is used to help determine what type of entity the level file wants to load, and then corresponds to a specific load function in entity_load_array */
char entity_types[ENTITIES_NUM][16] = {"player", "melt", "celery_stalker", "professor_slice", "milk_tank", "clarence", "double_tap", "heat_shield", "bomb", "spread_shot", "sticky_shot", "extra_life"};

void level_load(Uint8 level_number)
{
	FILE *levelfile = NULL;
	char buf[128];
	int linenum = 0;

	//background loading storage
	char background_file[128];
	int width, height;
	int i;
	Sprite * temp;

	Uint32 end;

	//entity loading storage 
	char entity_type[30];
	Entity *ent = NULL;
	int id;
	int targetID;
	float x, y;

	levelfile = fopen(files_get_level(level_number),"r");
	if (levelfile == NULL)
	{
		slog("could not open file: %s",files_get_level(level_number));
		return;
	}
	while(fscanf(levelfile, "%s", buf) != EOF)
	{
		slog("%s", buf, linenum);
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
		else if (strncmp(buf, "end:", 128)==0)
		{
			fscanf(levelfile,"%i",&end);
			slog("end: %i", end);
		}

		else if(strncmp(buf,"entity:",128) == 0)
		{
			fscanf(levelfile,"%s",entity_type);
			slog("entity_type %s",entity_type);
		}
		else if(strncmp(buf,"id:",128)==0)
		{
			fscanf(levelfile,"%i",&id);
			slog("id %i",id);
		}
		else if(strncmp(buf,"target:",128)==0)
		{
			fscanf(levelfile,"%i",&targetID);
			slog("target %i",targetID);
		}
		else if(strncmp(buf,"position:",128)==0)
		{
			fscanf(levelfile,"%f",&x);
			fscanf(levelfile,"%f",&y);
			slog("x %f : y %f",x,y);
		}
		//this signifies the end of a entity, needs to be after every entity even the last one before the end of the list
		else if(buf[0] == '~')
		{
			for(i = 0; i < ENTITIES_NUM; i++)
			{
				if(strncmp(entity_type, entity_types[i], 16) == 0)
				{
					if(!entity_load_array[i])
					{
						slog("error finding entity's load function");
						return;
					}
					entity_load_array[i](ent,id,targetID,x,y);
				}
			}
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
	level.file = files_get_level(level_number);
	level.end = end;
	return;
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
	entity_load_array[0] = &player_load;
	entity_load_array[1] = &melt_load;
	entity_load_array[2] = &celery_stalker_load;
	entity_load_array[3] = &professor_slice_load;
	entity_load_array[4] = &milk_tank_load;
	entity_load_array[5] = &clarence_load;
	entity_load_array[6] = &power_up_double_tap;
	entity_load_array[7] = &power_up_heat_shield;
	entity_load_array[8] = &power_up_bomb;
	entity_load_array[9] = &power_up_spread_shot;
	entity_load_array[10]= &power_up_sticky_shot;
	entity_load_array[11]= &power_up_extra_life;
	atexit(level_close);
}

Level *level_get()
{
	return &level;
}
