#include "affichage.h"
#include "input.h"
#include "timer.h"

Affichage initAffichage()
{
	Affichage affichage;

	affichage.window = NULL;
	affichage.screen = NULL;
	affichage.interface = NULL;
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0 )
	{
		fprintf(stderr, "Impossible d initialiser le mode vidéo: %s", SDL_GetError() );
		exit(EXIT_FAILURE);
	}
	
	if (SDL_CreateWindowAndRenderer(W_SCREEN, H_SCREEN, 
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL, &affichage.window, &affichage.screen) != 0)
	{
		fprintf(stderr, "Impossible d initialiser la fenêtre: %s", SDL_GetError() );
		exit(EXIT_FAILURE);
	}
	
	SDL_SetWindowTitle(affichage.window, "Snake");
	
	if ( IMG_Init(IMG_INIT_PNG) == 0 )
	{
		fprintf(stderr,"Impossible d'initialiser l'image : %s \n", IMG_GetError() );
		exit(EXIT_FAILURE);
	}
	
	affichage.interface = IMG_LoadTexture(affichage.screen, "img/interface.png");
	if (affichage.interface == NULL)
	{
		fprintf(stderr,"Erreur :: %s", IMG_GetError() );
		exit(EXIT_FAILURE);
	}
	
	/** Positions sources du tileset */
	
	affichage.tilesets[TILE_TITLE] = newBox(20, 8, 492, 135);
	affichage.tilesets[TILE_CASE] = newBox(33, 166, T_CASE, T_CASE);
	affichage.tilesets[TILE_HEAD] = newBox(80, 167, T_CASE, T_CASE);
	affichage.tilesets[TILE_PROIE] = newBox(127, 165, T_CASE, T_CASE);
	affichage.tilesets[TILE_BODY] = newBox(176, 166, T_CASE, T_CASE);
	affichage.tilesets[TILE_QUEUE] = newBox(224, 166, T_CASE, T_CASE);
	affichage.tilesets[TILE_REPLAY] = newBox(285, 143, 248, 133);
	affichage.tilesets[TILE_WIN] = newBox(10, 215, 273, 109);
	affichage.tilesets[TILE_LOSE] = newBox(12, 327, 271, 108);
	affichage.tilesets[TILE_MENU] = newBox(293, 273, 486, 320);
	
	/** Positions cibles */
	
	affichage.positions[TILE_MENU] = newBox(X_MENU, Y_MENU, W_MENU, H_MENU);	
	
	/* Meme position : TILE_CASE, TILE_PROIE, TILE_HEAD, TILE_BODY, TILE_QUEUE */
	affichage.positions[TILE_CASE] = newBox(0, 0, T_CASE, T_CASE);	
	
	affichage.positions[TILE_TITLE] = newBox(X_TITLE, Y_TITLE, W_TITLE, H_TITLE);
	
	/* Meme position: TILE_WIN, TILE_LOSE */
	affichage.positions[TILE_WIN] = newBox(X_WIN, Y_WIN, W_WIN, H_WIN);
	affichage.positions[TILE_LOSE] = affichage.positions[TILE_WIN];
	
	affichage.positions[TILE_REPLAY] = newBox(X_REPLAY, Y_REPLAY, W_REPLAY, H_REPLAY);
		
	SDL_SetRenderDrawColor(affichage.screen,206,238,156,255);
	SDL_RenderClear(affichage.screen);

	return affichage;
}

void deleteAffichage(Affichage *A)
{
	SDL_DestroyTexture(A->interface);
	SDL_DestroyRenderer(A->screen);
	SDL_DestroyWindow(A->window);
	IMG_Quit();
	SDL_Quit();
}

void drawTile (Affichage A, Tiles noTile)
{
	SDL_RenderCopy(A.screen, A.interface, &A.tilesets[noTile], &A.positions[noTile]);
	SDL_RenderPresent(A.screen);
}

CMenu drawMenu(Affichage A)
{
	Input input = initInput();
	Timer timer = initTimer();
	drawTile(A, TILE_MENU);
	
	while (1)
	{
		setTimer(&timer);
		updateEvents(&input);
		
	
		if (input.mouseButton[SDL_BUTTON_LEFT])
		{
			input.mouseButton[SDL_BUTTON_LEFT] = FALSE;
			if (X_PLAY <= input.clicX && input.clicX <= X_PLAY + W_PLAY && Y_PLAY <= input.clicY && input.clicY <= Y_PLAY + H_PLAY)
			{
				SDL_RenderClear(A.screen);
				SDL_RenderPresent(A.screen);
				return PLAY;
			}
			
			else if (X_QUIT <= input.clicX && input.clicX <= X_QUIT + W_QUIT && Y_QUIT <= input.clicY && input.clicY <= Y_QUIT + H_QUIT)
			{
				SDL_RenderClear(A.screen);
				SDL_RenderPresent(A.screen);
				return QUIT;
			}
			
		}
		
		reguleFPS(&timer);
	}	 
	
	return QUIT;
}

bool drawReplay(Affichage A)
{
	Input input = initInput();
	Timer timer = initTimer();
	SDL_RenderClear(A.screen);
	drawTile(A, TILE_REPLAY);
	
	while(1)
	{
		setTimer(&timer);
		updateEvents(&input);
	
		if (input.mouseButton[SDL_BUTTON_LEFT])
		{
			input.mouseButton[SDL_BUTTON_LEFT] = FALSE;
			if (X_YES <= input.clicX && input.clicX <= X_YES + W_YES && Y_YES <= input.clicY && input.clicY <= Y_YES + H_YES)
			{
				SDL_RenderClear(A.screen);
				SDL_RenderPresent(A.screen);
				return TRUE;
			}
				
			else if ((X_NO <= input.clicX && input.clicX <= X_NO + W_YES && Y_NO <= input.clicY && input.clicY <= Y_NO + H_YES) || input.end)
			{
				SDL_RenderClear(A.screen);
				SDL_RenderPresent(A.screen);
				break;		
			}
		}
		
		reguleFPS(&timer);
	}
	
	return FALSE;
}

DialogBox newBox(int x, int y, int w, int h)
{
	DialogBox r;
	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;
	return r;
}



