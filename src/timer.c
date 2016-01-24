#include "timer.h"

Timer initTimer()
{
	Timer timer;
	timer.startTime = 0;
	timer.ellapsedTime = 0;
	timer.currentTime = 0;
	timer.lastTime = 0;
	return timer;
}

void setTimer(Timer *timer)
{
	timer->currentTime = SDL_GetTicks();
	timer->ellapsedTime = timer->currentTime - timer->lastTime;
	timer->lastTime = timer->currentTime;
}

void reguleFPS(Timer *timer)
{
	timer->ellapsedTime = SDL_GetTicks() - timer->lastTime;
		if (timer->ellapsedTime < FPS)
			SDL_Delay(FPS-timer->ellapsedTime);
}
