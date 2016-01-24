#include "snake.h"

/* Fonction d initialisation des structures 
 * Elles doivent être utilisées avant toute opération sur les structures
 * */
 
Position initPosition()
{
	Position pos;
	pos.x = -1;
	pos.y = -1;
	return pos;
}

CaseSnake initCaseSnake()
{
	CaseSnake cas;
	cas.etat = VOID;
	cas.position = initPosition();
	return cas;
}

Snake initSnake()
{
	Snake snake;
	int i;

	snake.tete = snake.queue = -1;
	
	for (i = 0 ; i < MAXSNAKE ; i++)
		snake.posSnake[i] = initCaseSnake();
	
	return snake;
}
	
/* Fonctions de création de structures */

Position newPosition(int x, int y)
{
	Position pos;
	pos.x = x;
	pos.y = y;
	return pos;
}

CaseSnake newCaseSnake(StateSnake etat, Position pos)
{
	CaseSnake cas;
	cas.etat = etat;
	cas.position =  pos;
	return cas;
}

Snake newSnake(int tete, int queue, CaseSnake posSnake[])
{
	Snake snake;
	int i;
	
	if (tete >= MAXSNAKE && queue >= MAXSNAKE)
	{
		perror("La tete ou la queue dépasse les limites du tableau!");
		exit(ERR_SIZE_SNAKE);
	}
	
	snake.tete = tete;
	snake.queue = queue;
	
	for (i = queue ; i <= tete ; i++)
		snake.posSnake[i] = posSnake[i];
	
	for (i = 0; i < queue ; i++)
		snake.posSnake[i] = initCaseSnake();
	
	for (i = tete+1; i < MAXSNAKE ; i++)
		snake.posSnake[i] = initCaseSnake();
	
	return snake;
}


/* Fonction de test de position */

bool testPosSnake(Position pos)
{
	return ( (pos.x < 0 || pos.x >= MAXSNAKE) && (pos.y < 0 || pos.y >= MAXSNAKE) )? FALSE : TRUE;
}

