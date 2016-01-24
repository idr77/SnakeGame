#ifndef SNAKE_H
#define SNAKE_H

#define MAXCASES 12
#define MAXSNAKE 5000

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

/* Type booléen */
typedef enum _bool {FALSE, TRUE} bool;

/* Type codant l'état d une case du serpent */
typedef enum _stateSnake
{
	VOID,
	TETE,
	CORPS,
	QUEUE
}StateSnake;

/* Structure indiquant la position (x,y) d' une case */
typedef struct _position
{
	int x;
	int y;
}Position;
	
/* Structure d'une case du serpent */
typedef struct _case
{
	StateSnake etat;
	Position position;
}CaseSnake;

/* Structure du serpent */
typedef struct _snake
{
	int tete, queue;
	CaseSnake posSnake[MAXSNAKE];
}Snake;

/* Codes d' erreurs */

typedef enum _err
{
	ERR_SIZE_SNAKE = -1, ERR_POSITION = -2, NO_ERR = 1
}Erreur;


Position initPosition();
CaseSnake initCaseSnake();
Snake initSnake();
Position newPosition(int x, int y);
CaseSnake newCaseSnake(StateSnake etat, Position pos);
Snake newSnake(int tete, int queue, CaseSnake posSnake[]);
bool testPosSnake(Position pos);


#endif
