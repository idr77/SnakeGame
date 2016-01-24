/* sound.h */
#include <SDL2/SDL_mixer.h>

#define START_SOUND 0
#define CROC_SOUND 1
#define MAX_MSC 2

typedef struct _Sound
{
	Mix_Chunk *msc[MAX_MSC];
}Sound;

Sound initSound();
void deleteSound(Sound* sound);
void playSound(Sound sound, int noSound);

