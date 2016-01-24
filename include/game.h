#ifndef _GAME_H
#define _GAME_H

#define END_GAME 1

#include "damier.h"
#include "snake.h"
#include "sound.h"
#include "chrono.h"


int addPositionSnake(Damier *map, Snake *snake, Position pos, Sound sound);
void setPositionsToMap(Damier *map, Snake *snake);
void initGame(Damier *map, Snake *snake);
bool playGame(Affichage A, Damier *map, Snake *snake, Sound sound);
bool endGame(Damier *map);

#endif
