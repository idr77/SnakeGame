/* sound.c */
#include "sound.h"

Sound initSound()
{
	int i;
	Sound sound;
	
	for (i = 0; i < MAX_MSC ; i++)
	{
		sound.msc[i] = NULL;
	}
	
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) 
	{  
	    fprintf(stderr, "Impossible d'initialiser le son :: %s", Mix_GetError() ); 
	    exit(EXIT_FAILURE);
	}
	
	Mix_AllocateChannels(32);
	Mix_Volume(1, MIX_MAX_VOLUME);
	
	sound.msc[START_SOUND] = Mix_LoadWAV("./sound/start.wav");
	sound.msc[CROC_SOUND] = Mix_LoadWAV("./sound/croc.wav");
	
	Mix_VolumeChunk(sound.msc[START_SOUND], MIX_MAX_VOLUME);
	Mix_VolumeChunk(sound.msc[CROC_SOUND], MIX_MAX_VOLUME/2);
	
	return sound;
}

void deleteSound(Sound *sound)
{
	int i;
	for (i = 0; i < MAX_MSC ; i++)
	{
		Mix_FreeChunk(sound->msc[i]);
		sound->msc[i] = NULL;
	}
	
	Mix_CloseAudio();	
}

void playSound(Sound sound, int noSound)
{
	Mix_PlayChannel(1, sound.msc[noSound], 0);
}
