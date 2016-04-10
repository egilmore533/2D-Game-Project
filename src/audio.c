#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "audio.h"
#include "simple_logger.h"
#include <SDL.h>

int numSounds = 0;
int maxSounds = 0;
int numMusics = 0;
int maxMusics = 0;
Sound *soundList = NULL;
Music *musicList = NULL;

void audio_music_free(Music **music)
{
	Music *target;
	if(!music)
	{
		return;
	}
	else if(!*music) 
	{
		return;
	}
	target = *music;
	target->used--;

	if(target->music != NULL)
	{
		Mix_FreeMusic(target->music);
	}
	numMusics--;
	*music = NULL;
}

void audio_sound_free(Sound **sound)
{
	Sound *target;
	if(!sound)
	{
		return;
	}
	else if(!*sound) 
	{
		return;
	}
	target = *sound;
	target->used--;

	if(target->sound != NULL)
	{
		Mix_FreeChunk(target->sound);
	}
	numSounds--;
	*sound = NULL;
}

void audio_close_music()
{
	int i;
	Music *music;
	if(!musicList)
	{
		slog("musicList not initialized");
		return;
	}
	for(i = 0; i < maxMusics; i++)
	{
		music = &musicList[i];
		audio_music_free(&music);
	}
	maxMusics = 0;
	free(musicList); 
	musicList = NULL;
}

void audio_close_sound()
{
	int i;
	Sound *sound;
	if(!soundList)
	{
		slog("soundList not initialized");
		return;
	}
	for(i = 0; i < maxSounds; i++)
	{
		sound = &soundList[i];
		audio_sound_free(&sound);
	}
	maxSounds = 0;
	free(soundList); 
	soundList = NULL;
}

void audio_close_lists()
{
	audio_close_music();
	audio_close_sound();
	Mix_CloseAudio();
}

void audio_initialize(int soundMax, int musicMax)
{
	int flags=MIX_INIT_OGG;
	if(soundMax <= 0 || musicMax <= 0)
	{
		slog("cannot initialize for 0 sounds or 0 musics");
		return;
	}
	if(Mix_Init(flags) != flags)
	{
		slog("Not initialized for ogg");
		return;
	}
	if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) != 0)
	{
		slog("failed to open audio");
		return;
	}
	atexit(audio_close_lists);

	if(Mix_AllocateChannels(5) != 5)
	{
		slog("unable to allocate enough channels");
		return;
	}

	musicList = (Music *) malloc (sizeof (Music) * musicMax);
	soundList = (Sound *) malloc (sizeof (Sound) * soundMax);

	memset(musicList, 0, sizeof (Music) * musicMax);
	memset(soundList, 0, sizeof (Sound) * soundMax);

	maxMusics = musicMax;
	maxSounds = soundMax;
}

Music *audio_load_music(char *filename, int loop)
{
	Music *music_new = NULL;
	music_new = audio_music_new();

	strcpy(music_new->filename, filename);
	music_new->music = Mix_LoadMUS(filename);
	music_new->loop = loop;
	return music_new;
}

Sound *audio_load_sound(char *filename, int loop, int channel)
{
	Sound *sound_new = NULL;
	sound_new = audio_sound_new();

	strcpy(sound_new->filename, filename);
	sound_new->channel = channel;
	sound_new->loop = loop;
	sound_new->sound = Mix_LoadWAV(filename);
	return sound_new;
}

Sound *audio_sound_new()
{
	int i;
	if(numSounds  + 1 > maxSounds)
	{
		slog("Maximum sounds reached");
		exit(1);
	}
	for(i = 0; i < maxSounds; i++)
	{
		if(soundList[i].used)
		{
			continue;
		}
		memset(&soundList[i],0,sizeof(Sound));
		soundList[i].used = 1;
		numSounds++;
		return &soundList[i];
	}
	return NULL;
}

Music *audio_music_new()
{
	int i;
	if(numMusics  + 1 > maxMusics)
	{
		slog("Maximum musics reached");
		exit(1);
	}
	for(i = 0; i < maxMusics; i++)
	{
		if(musicList[i].used)
		{
			continue;
		}
		memset(&musicList[i],0,sizeof(Music));
		musicList[i].used = 1;
		numMusics++;
		return &musicList[i];
	}
	return NULL;
}

void audio_play_music(Music *music)
{
	Mix_PlayMusic(music->music, music->loop);
}

void audio_play_sound(Sound *sound)
{
	Mix_PlayChannel(sound->channel, sound->sound, sound->loop);
}
