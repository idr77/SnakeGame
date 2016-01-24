#ifndef DAMIER_H
#define DAMIER_H

#include "snake.h"
#include "input.h"
#include "affichage.h"

typedef enum _state
{
	NO,
	PROIE,
	VER
}StateMap;


typedef struct _damier
{
	StateMap map[MAXCASES][MAXCASES];
	Position posTete, posQueue;
}Damier;

Damier initDamier();
void setPositionHead(Damier *map, Position head);
void setPositionQueue(Damier *map, Position queue);
void addProieMap(Damier *map, Position pos);
void setVerMap(Damier *map, Position pos);
Position updatePositions(Damier *map, Snake *snake, Input*);
void setProiesToMap(Damier *map);
void drawMap(Affichage A, Damier map, Position newPos, Snake snake);
bool isProie(Damier map, Position pos);
bool isFree(Damier map, Position pos);
bool isSnake(Damier map, Position pos);
bool testPosMap(Position pos);
int savePosProies(Damier map, Position proies[]);
void reloadProiesToMap(Damier *map, Position proies[], int nbProies);

#endif
