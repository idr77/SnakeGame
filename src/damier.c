#include "damier.h"
#include "affichage.h"

/* Initialise la map */
Damier initDamier()
{
	Damier map;
	int i, j;
	for (j = 0 ; j < MAXCASES ; j++)	
		for (i = 0; i < MAXCASES ; i++)
			map.map[j][i] = NO;
	
	
	map.posTete = map.posQueue = initPosition();
	return map;			
}

/* Teste si une position est valide sur la map */
bool testPosMap(Position pos)
{
	return ( (pos.x < 0 || pos.x >= MAXCASES) && ( pos.y < 0 || pos.y >= MAXCASES) )? FALSE : TRUE; 
}

/* Fonctions d affectation de position de la tete et de la queue sur la map */
void setPositionHead(Damier *map, Position head)
{
	map->posTete = head;
	map->map[head.y][head.x] = VER;
}

void setPositionQueue(Damier *map, Position queue)
{
	map->posQueue = queue;
	map->map[queue.y][queue.x] = VER;
}

/* Fonctions renvoyant l état d une case*/
bool isProie(Damier map, Position pos)
{
	return (map.map[pos.y][pos.x] == PROIE)? TRUE : FALSE;
}

bool isFree(Damier map, Position pos)
{
	return (map.map[pos.y][pos.x] == NO)? TRUE : FALSE;
}

bool isSnake(Damier map, Position pos)
{
	return (map.map[pos.y][pos.x] == VER)? TRUE : FALSE;
}

/* Fonction qui ajoute une proie sur la map en position pos */		
void addProieMap(Damier *map, Position pos)
{
	map->map[pos.y][pos.x] = PROIE;
}

/* Fonction qui ajoute un bout de serpent à la position pos */
void setVerMap(Damier *map, Position pos)
{
	map->map[pos.y][pos.x] = VER;
}

/* Fonction qui dispose aléatoirement des proies sur la map */
void setProiesToMap(Damier *map)
{
	int i;
	Position pos;
	srand(time(NULL));
	
	for (i = 0 ; i < MAXCASES*2 ; i++)
	{
		pos.x = rand()%MAXCASES;
		pos.y = rand()%MAXCASES;
		
		if (isFree(*map, pos))
			addProieMap(map,pos);
	}

}

/* Fonction qui sauvegarde dans un tableau la position des proies */
int savePosProies(Damier map, Position proies[])
{
	Position p;
	int i = 0;
	for (p.y = 0; p.y < MAXCASES ; p.y++)
	{
		for (p.x = 0; p.x < MAXCASES ; p.x++)
		{
			if (isProie(map, p))
			{
				proies[i++] = p;
			}
		}
	}
	return i;
}

/* Fonction qui remet les proies sur la map à partir d un tableau de position */
void reloadProiesToMap(Damier *map, Position proies[], int nbProies)
{
	int i;
	for (i=0; i < nbProies ; i++)
	{
		addProieMap(map, proies[i]);
	}
}

/* Fonction de mise à jour des positions selon les événements clavier/souris */
Position updatePositions(Damier *map, Snake *snake, Input *input)
{
	Position newPos;
	
	do
	{
		updateEvents(input);
	}
	while (!input->mouseButton[SDL_BUTTON_LEFT] && !input->keyboardButton[SDL_SCANCODE_LEFT] &&
	 !input->keyboardButton[SDL_SCANCODE_RIGHT] && !input->keyboardButton[SDL_SCANCODE_UP] &&
	 !input->keyboardButton[SDL_SCANCODE_DOWN] && !input->end);
	 
	/* Souris */
	if (input->mouseButton[SDL_BUTTON_LEFT])
	{
		input->mouseButton[SDL_BUTTON_LEFT] = FALSE;
		newPos = clicPosition(input->clicX, input->clicY);
	}
	
	/* Clavier */
	if (input->keyboardButton[SDL_SCANCODE_LEFT])
	{
		newPos = newPosition( map->posTete.x - 1, map->posTete.y);
		input->keyboardButton[SDL_SCANCODE_LEFT] = FALSE;
	}
	
	if (input->keyboardButton[SDL_SCANCODE_RIGHT])
	{
		newPos = newPosition(map->posTete.x + 1, map->posTete.y);
		input->keyboardButton[SDL_SCANCODE_RIGHT] = FALSE;
	}
	
	if (input->keyboardButton[SDL_SCANCODE_UP])
	{
		newPos = newPosition(map->posTete.x, map->posTete.y - 1);
		input->keyboardButton[SDL_SCANCODE_UP] = FALSE;
	}
	
	if (input->keyboardButton[SDL_SCANCODE_DOWN])
	{
		newPos = newPosition(map->posTete.x, map->posTete.y + 1);
		input->keyboardButton[SDL_SCANCODE_DOWN] = FALSE;
	}
	
	if (newPos.x < 0)
		newPos.x = 0;
	
	if (newPos.y < 0)
		newPos.y = 0;
	
	if (newPos.x >= MAXCASES)
		newPos.x = MAXCASES - 1;
	
	if (newPos.y >= MAXCASES)
		newPos.y = MAXCASES - 1;
	
	#ifdef DEBUG
	printf("newPos.x = %d , newPos.y = %d\n", newPos.x, newPos.y);
	#endif
	
	if ((newPos.x == map->posTete.x + 1 || newPos.x == map->posTete.x - 1 
		||  newPos.y == map->posTete.y - 1 ||  newPos.y == map->posTete.y + 1) && testPosMap(newPos))
	{
		return newPos;
	}
	
	return (newPos = initPosition());
}

/* Affiche la map dans une fenetre */
void drawMap(Affichage A, Damier map, Position newPos, Snake snake)
{
	int i, j;
	for (j = 0; j < MAXCASES ; j++)
	{
		A.positions[TILE_CASE].y = CENTER_Y + j * T_CASE;
		
		for (i = 0; i < MAXCASES ; i++)
		{
			A.positions[TILE_CASE].x = CENTER_X + i * T_CASE;
						
			if (map.map[j][i] == NO)
			{
				/* Dessine la case vide */
				SDL_RenderCopy(A.screen, A.interface, &A.tilesets[TILE_CASE], &A.positions[TILE_CASE]);
			}
			
			else if (map.map[j][i] == PROIE)
			{
				/* Dessine la case proie */
				SDL_RenderCopy(A.screen, A.interface, &A.tilesets[TILE_PROIE], &A.positions[TILE_CASE]);
			}
			
			else if (map.map[j][i] == VER)
			{
				if (j == map.posTete.y && i == map.posTete.x)
				{
					/* Dessine la tete du serpent dans l angle de sa direction */
					
					/* Droite */
					if (snake.tete > 0 && newPos.x == snake.posSnake[snake.tete - 1].position.x + 1 )
						SDL_RenderCopyEx(A.screen, A.interface, &A.tilesets[TILE_HEAD], &A.positions[TILE_CASE], 90, NULL, SDL_FLIP_HORIZONTAL);
					
					/* Gauche */
					else if (snake.tete > 0 && newPos.x == snake.posSnake[snake.tete - 1].position.x - 1)
						SDL_RenderCopyEx(A.screen, A.interface, &A.tilesets[TILE_HEAD], &A.positions[TILE_CASE], 270, NULL, SDL_FLIP_HORIZONTAL);
					
					/* Bas */
					else if (snake.tete > 0 && newPos.y == snake.posSnake[snake.tete - 1].position.y + 1 )
						SDL_RenderCopyEx(A.screen, A.interface, &A.tilesets[TILE_HEAD], &A.positions[TILE_CASE], 180, NULL, SDL_FLIP_HORIZONTAL);
					
					/* Haut */
					else
						SDL_RenderCopy(A.screen, A.interface, &A.tilesets[TILE_HEAD], &A.positions[TILE_CASE]);
				}
				
				else if (j == map.posQueue.y && i == map.posQueue.x )
				{
					/* Dessine la queue du serpent */
					if (snake.posSnake[snake.queue + 1].position.x == i && snake.posSnake[snake.queue + 1].position.y == j+1 )
						SDL_RenderCopy(A.screen, A.interface, &A.tilesets[TILE_BODY], &A.positions[TILE_CASE]);
					else
						SDL_RenderCopy(A.screen, A.interface, &A.tilesets[TILE_QUEUE], &A.positions[TILE_CASE]);
				}
				
				else
				{
					/* Dessine le corps du serpent */
					SDL_RenderCopy(A.screen, A.interface, &A.tilesets[TILE_BODY], &A.positions[TILE_CASE]);
				}
			}
		}
	}
	SDL_RenderPresent(A.screen);
}


	
