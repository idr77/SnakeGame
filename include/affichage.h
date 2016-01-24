#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "snake.h"

#define T_CASE 40

/* Positions cibles */
#define W_SCREEN 1024
#define H_SCREEN 768

#define W_MENU 640
#define H_MENU 480
#define X_MENU (W_SCREEN - W_MENU)/2
#define Y_MENU 0

#define W_TITLE 492
#define H_TITLE 135
#define X_TITLE (W_SCREEN - W_TITLE)/2
#define Y_TITLE 0

#define W_WIN 500
#define H_WIN 250
#define X_WIN (W_SCREEN - W_WIN)/2
#define Y_WIN (H_SCREEN - H_WIN)/2

#define W_REPLAY 500
#define H_REPLAY 250
#define X_REPLAY (W_SCREEN - W_REPLAY)/2
#define Y_REPLAY (H_SCREEN - H_REPLAY)/2


#define X_YES (X_REPLAY + 50)
#define Y_YES (Y_REPLAY + 154)
#define W_YES 162
#define H_YES 67

#define X_NO (X_REPLAY + 282)
#define Y_NO (Y_REPLAY + 157)

#define W_PLAY 563
#define H_PLAY 102
#define X_PLAY (X_MENU + 44 )
#define Y_PLAY (Y_MENU + 133)

#define W_QUIT 553
#define H_QUIT 96
#define X_QUIT (X_MENU + 54)
#define Y_QUIT (Y_MENU + 305)

#define CENTER_X (W_SCREEN - (MAXCASES * T_CASE))/2
#define CENTER_Y (H_SCREEN - (MAXCASES * T_CASE))/2

#define MAX_TILES 10

typedef enum _Tilecases
{
	TILE_MENU,
	TILE_HEAD,
	TILE_BODY,
	TILE_QUEUE,
	TILE_CASE,
	TILE_PROIE,
	TILE_TITLE,
	TILE_WIN,
	TILE_LOSE,
	TILE_REPLAY
}Tiles;

typedef SDL_Rect DialogBox;

typedef struct t_aff
{
	SDL_Window* window;
	SDL_Renderer* screen;
	SDL_Texture* interface;
	SDL_Rect positions[MAX_TILES];
	SDL_Rect tilesets[MAX_TILES];
}Affichage;

typedef enum _Cmenu
{
	PLAY,
	QUIT
}CMenu;


Affichage initAffichage();
void deleteAffichage(Affichage *A);
void drawTile (Affichage A, Tiles noTile);
CMenu drawMenu(Affichage A);
bool drawReplay(Affichage A);
DialogBox newBox(int x, int y, int w, int h);

#endif
