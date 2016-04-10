#ifndef __AUDIO_H__
#define __AUDIO_H__

#include <SDL_mixer.h>
enum SOUND_GROUPS	{FX_NULL, FX_Bullets, FX_Impacts, FX_Monsters, FX_Player};

typedef struct Sound_s
{
	Mix_Chunk *sound;
	char filename[80];
	int used;
	float volume;
	int loop;
	int channel;
}Sound;

typedef struct Music_s
{
	Mix_Music *music;
	char filename[80];
	int used;
	float volume;
	int loop;
}Music;

typedef struct SoundPak_S
{
	int loaded;
	Sound *moving;
	Sound *firing;
	Sound *death;
}SoundPak;

void audio_initialize(int soundMax, int musicMax);

void audio_close_lists();
void audio_close_music();
void audio_close_sound();

void audio_music_free(Music **music);
void audio_sound_free(Sound **sound);


Music *audio_music_new();

Sound *audio_sound_new();

/**
 * @brief loads a sound file into the soundList
 * @param filename - the name of the file to be loaded
 * @param loop	   - the number of times to loop the audio (-1 forever)
 * @param channel  - the channel number for this audio file
 * @return the loaded Sound data
 */
Sound *audio_load_sound(char *filename, int loop, int channel);

/**
 * @brief loads a music file into the musicList
 * @param filename - the name of the file to be loaded
 * @param loop	   - the number of times to loop the audio (-1 forever)
 * @return the loaded Music data
 */
Music *audio_load_music(char *filename, int loop);

void audio_play_music(Music *music);
void audio_play_sound(Sound *sound);


#endif