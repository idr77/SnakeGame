#include "game.h"

int main(int argc, char *argv[])
{
	bool replay = FALSE;
	bool win = FALSE;
	Damier map = initDamier();
	Snake snake = initSnake();
	Affichage A = initAffichage();
	Sound sound = initSound();
	
	if ( drawMenu(A) == PLAY )
	{
		initGame(&map, &snake);
		
		do
		{
			playSound(sound, START_SOUND);
			win = playGame(A, &map, &snake, sound);
			
			if (win)
			{
				drawTile(A, TILE_WIN);
			}
			
			else
			{
				drawTile(A, TILE_LOSE);
			}
			
			SDL_Delay(3000);
			replay = drawReplay(A);
			
			initGame(&map, &snake);
		}
		while(replay);
	}
	
	deleteAffichage(&A);
	
	return EXIT_SUCCESS;
}

