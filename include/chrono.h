#ifndef CHRONO_H
#define CHRONO_H

#include "affichage.h"

#define TEX_TXT 0
#define TEX_SEC 1

#define DELAY_CHRONO 15

typedef struct _chrono
{
	int currentTime, maxTime;
	int startTicks, pausedTicks;
	bool started, paused;
	SDL_Rect pos[2];
	TTF_Font *font[2];
}
Chrono;

void initTTF();
Chrono initChrono();
void deleteChrono(Chrono *chrono);
bool endChrono(Chrono chrono);
void startChrono(Chrono *chrono);
bool isStarted(Chrono chrono);
int setCurrentTime(Chrono *chrono);
int getTicks(Chrono *chrono);
void pauseChrono(Chrono *chrono);
bool isPaused(Chrono chrono);
void restartChrono(Chrono *chrono);
void drawTextChrono(Chrono chrono, Affichage A);
void drawChrono(Chrono chrono, Affichage A);

#endif
