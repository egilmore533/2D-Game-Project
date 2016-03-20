#include "files.h"

char *files_get_level(int num)
{
	if(num == 1)
	{
		return LEVEL_1;
	}
	if(num == 2)
	{
		return LEVEL_2;
	}
	if(num == 3)
	{
		return LEVEL_3;
	}
}