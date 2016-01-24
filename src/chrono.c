#include "chrono.h"

void initTTF()
{
	if(TTF_Init() == -1)
	{
		fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}
}

Chrono initChrono()
{
	int i;
	Chrono chrono;
	
	for (i = 0; i < 2 ; i++)
		chrono.font[i] = NULL;
	
	initTTF();
	
	chrono.font[TEX_TXT] = TTF_OpenFont("font/SIXTY.TTF", 20);
	chrono.font[TEX_SEC] = TTF_OpenFont("font/SIXTY.TTF", 50);
	
	chrono.maxTime = DELAY_CHRONO;
	chrono.currentTime = 0;
	chrono.started = FALSE;
	chrono.paused = FALSE;
	chrono.startTicks = 0;
	chrono.pausedTicks = 0;
	
	TTF_SizeText(chrono.font[TEX_SEC], "00" , &chrono.pos[TEX_SEC].w , &chrono.pos[TEX_SEC].h);
	chrono.pos[TEX_SEC].x = (W_SCREEN - chrono.pos[TEX_SEC].w)/10;
	chrono.pos[TEX_SEC].y = (H_SCREEN - chrono.pos[TEX_SEC].h)/10;
	
	TTF_SizeText(chrono.font[TEX_TXT], "Il vous reste", &chrono.pos[TEX_TXT].w, &chrono.pos[TEX_TXT].h );
	chrono.pos[TEX_TXT].x = chrono.pos[TEX_SEC].x;
	chrono.pos[TEX_TXT].y = chrono.pos[TEX_SEC].y - 20 ;
	
	TTF_SetFontStyle(chrono.font[TEX_SEC], TTF_STYLE_NORMAL);
	TTF_SetFontStyle(chrono.font[TEX_TXT], TTF_STYLE_ITALIC);
	
	return chrono;
}

void deleteChrono(Chrono *chrono)
{
	TTF_CloseFont(chrono->font[TEX_TXT]);
	TTF_CloseFont(chrono->font[TEX_SEC]);
	TTF_Quit();
}

bool endChrono(Chrono chrono)
{
	setCurrentTime(&chrono);
	return (chrono.maxTime - (chrono.currentTime/1000) <= 0)? TRUE:FALSE;
}

void startChrono(Chrono *chrono)
{
	chrono->started = TRUE;
	chrono->paused = FALSE;
	chrono->startTicks = chrono->currentTime = SDL_GetTicks();
}

bool isStarted(Chrono chrono)
{
	return chrono.started;
}

int setCurrentTime(Chrono *chrono)
{
	if (chrono->paused)
		chrono->currentTime = chrono->pausedTicks;
		
	else
		chrono->currentTime = SDL_GetTicks() - chrono->startTicks;
		
	return chrono->currentTime;
}

int getTicks(Chrono *chrono)
{
	if (chrono->started)
	{
		if (chrono->paused)
			return chrono->pausedTicks;
		return chrono->currentTime - chrono->startTicks;
	}
	
	return 0;
}

void pauseChrono(Chrono *chrono)
{
	if (isStarted(*chrono) && !chrono->paused)	
	{
		chrono->paused = TRUE;
		chrono->pausedTicks = SDL_GetTicks() - chrono->startTicks;
	}
}

bool isPaused(Chrono chrono)
{
	return chrono.paused;
}

void restartChrono(Chrono *chrono)
{
	if (isPaused(*chrono))
	{
		chrono->paused = FALSE;
		chrono->pausedTicks = 0;
	}
}

void drawTextChrono(Chrono chrono, Affichage A)
{
	SDL_Surface *surfaceTexte = NULL;
	SDL_Texture *textureTexte = NULL;
	char *txt = "Il vous reste";
	SDL_Color color = {64, 182, 22};
	
	surfaceTexte = TTF_RenderText_Blended(chrono.font[TEX_TXT], txt, color);
	
	textureTexte = SDL_CreateTextureFromSurface(A.screen, surfaceTexte);
	SDL_FreeSurface(surfaceTexte);
	
	SDL_RenderCopy(A.screen, textureTexte, NULL, &chrono.pos[TEX_TXT]);
	SDL_RenderPresent(A.screen);
	SDL_DestroyTexture(textureTexte);
}

void drawChrono(Chrono chrono, Affichage A)
{
	SDL_Surface *surfaceTime = NULL;
	SDL_Texture *textureTime = NULL;
	char nbsec[3];
	SDL_Color color = {64, 182, 22};
	
	setCurrentTime(&chrono);
	sprintf(nbsec, "%d", chrono.maxTime - (((int)chrono.currentTime)/1000) );

	surfaceTime = TTF_RenderText_Solid(chrono.font[TEX_SEC], nbsec, color);
	
	textureTime = SDL_CreateTextureFromSurface(A.screen, surfaceTime);
	SDL_FreeSurface(surfaceTime);
	
	SDL_RenderFillRect(A.screen, &chrono.pos[TEX_SEC]);
	SDL_RenderCopy(A.screen, textureTime, NULL, &chrono.pos[TEX_SEC]);
	SDL_RenderPresent(A.screen);
	SDL_DestroyTexture(textureTime);
	
}



