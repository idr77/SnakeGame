#ifndef TIMER_H
#define TIMER_H

#define FPS 20

#include "snake.h"

typedef struct _Timer
{
	int startTime;
	int ellapsedTime;
	int currentTime;
	int lastTime;
}Timer;

Timer initTimer();
void setTimer(Timer *timer);
void reguleFPS(Timer *timer);

#endif
