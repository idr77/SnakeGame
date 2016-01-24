#include "game.h"
#include "timer.h"

/* Fonction qui ajoute une position au serpent */
int addPositionSnake(Damier *map, Snake *snake, Position pos, Sound sound)
{
	if (snake->tete-1 >= MAXSNAKE)
	{
		perror("Plus de place !");
		return ERR_SIZE_SNAKE;
	}
	
	if (!testPosSnake(pos))
	{
		return ERR_POSITION;
	}
	
	if (!isProie(*map, pos))
	{
		snake->posSnake[snake->queue] = initCaseSnake();
		snake->posSnake[++snake->queue].etat = QUEUE;
	}
	
	else
	{
		snake->posSnake[snake->queue + 1].etat = CORPS;
		snake->posSnake[snake->queue].etat = QUEUE;
		playSound(sound, CROC_SOUND);
	}
		
	if (isSnake(*map, pos))
	{
		return END_GAME;
	}
	
	snake->posSnake[snake->tete].etat = CORPS;	
	snake->posSnake[++snake->tete].position = pos;
	snake->posSnake[snake->tete].etat = TETE;
	
	return 0;
}

/* Fonctions de mise à jour des positions */
void setPositionsToMap(Damier *map, Snake *snake)
{
	int i, j;
	Position proies[MAXSNAKE];
	
	j = savePosProies(*map, proies);
	
	*map = initDamier();
	
	reloadProiesToMap(map, proies, j);
	
	for (i = snake->queue; i <= snake->tete ; i++)
	{
		setVerMap(map, snake->posSnake[i].position);
	}
	
	setPositionHead(map, snake->posSnake[snake->tete].position);
	setPositionQueue(map, snake->posSnake[snake->queue].position);
}


/* Fonctions de jeu */
void initGame(Damier *map, Snake *snake)
{
	CaseSnake pos[MAXSNAKE];
	int i;
	
	pos[0] = newCaseSnake(QUEUE, newPosition(MAXCASES/2 , MAXCASES/2));
	pos[1] = newCaseSnake(CORPS, newPosition(MAXCASES/2 + 1, MAXCASES/2));
	pos[2] = newCaseSnake(TETE, newPosition(MAXCASES/2 + 2, MAXCASES/2));	
	
	for (i = 3; i < MAXSNAKE ; i++)
		pos[i] = newCaseSnake(VOID, newPosition(0,0));
		
	*snake = newSnake(2,0,pos);
	setPositionsToMap(map, snake);
	
}
 
bool playGame(Affichage A, Damier *map, Snake *snake, Sound sound)
{
	int end = 0;
	bool win = FALSE;
	Position newPos = initPosition();
	Input input = initInput();
	Chrono chrono = initChrono();
	Timer timer = initTimer();
	
	
	setProiesToMap(map);
	
	drawTile(A, TILE_TITLE);
	drawTextChrono(chrono, A);
	drawMap(A, *map, newPosition(MAXCASES/2 + 3,MAXCASES/2), *snake);

	startChrono(&chrono);
	while (1)
	{
		
		setTimer(&timer);
		newPos = updatePositions(map, snake, &input);
		
		if (input.end)
			break;

		if (testPosMap(newPos))
		{
			end = addPositionSnake(map, snake, newPos, sound);
			if (end)
			{
				win = FALSE;
				break;
			}
		}
		
		setPositionsToMap(map, snake);
		drawChrono(chrono, A);
		drawMap(A, *map, newPos, *snake);
		
		if(endChrono(chrono))
		{
			win = FALSE;
			break;
		}
		
		if (endGame(map))
		{
			win = TRUE;
			break;
		}
		
		reguleFPS(&timer);
	}
	
	deleteChrono(&chrono);
	return win;
}

bool endGame(Damier *map)
{
	Position p;
	
	for (p.y = 0; p.y < MAXCASES ; p.y++)
	{
		for (p.x = 0; p.x < MAXCASES ; p.x++)
		{
			if (isProie(*map, p))
				return FALSE;
		}
	}
	
	return TRUE;
}









