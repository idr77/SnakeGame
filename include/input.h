#ifndef INPUT_H
#define INPUT_H

#include "snake.h"

/* Structure de gestion d'entrées clavier/souris */
typedef struct _input
{
	SDL_Event event;
	int clicX, clicY;
	bool mouseButton[8];
	bool keyboardButton[SDL_NUM_SCANCODES];
	bool end;
}Input;


/* Initialise la structure de gestion d'entrées clavier et souris */
Input initInput();
	
/* Met à jour les événements clavier et souris entrés par l utilisateur */
void updateEvents(Input *input);

/* Renvoie la position d'un clic de souris */
Position clicPosition(int clicX, int clicY);

#endif
