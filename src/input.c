#include "input.h"
#include "affichage.h"

Input initInput()
{
	Input input;
	int i;
	
	input.clicX = -1;
	input.clicY = -1;
	input.end = FALSE;
	
	for (i=0 ; i < SDL_NUM_SCANCODES; i++)
		input.keyboardButton[i] = FALSE;
	
	for (i=0 ; i < 8 ; i++)
		input.mouseButton[i] = FALSE;
	
	return input;

}


void updateEvents(Input *input)
{
	*input = initInput();

	while (SDL_PollEvent(&input->event))
	{
		
		switch(input->event.type)
		{
			case SDL_WINDOWEVENT:
				if (input->event.window.event == SDL_WINDOWEVENT_CLOSE)
					input->end = TRUE;
			break;
			
			case SDL_MOUSEBUTTONDOWN:
				input->mouseButton[input->event.button.button] = TRUE;
				input->clicX = input->event.button.x;
				input->clicY = input->event.button.y;
			break;
			
			case SDL_MOUSEBUTTONUP:
				input->mouseButton[input->event.button.button] = FALSE;
				input->clicX = -1;
				input->clicY = -1;
			break;
			
			case SDL_KEYDOWN:
                input->keyboardButton[input->event.key.keysym.scancode] = TRUE;
            break;

            case SDL_KEYUP:
                input->keyboardButton[input->event.key.keysym.scancode] = FALSE;
            break;
	
		}
	}
}
 
Position clicPosition(int clicX, int clicY)
{
	 Position posClic;
	 posClic.x = (clicX - CENTER_X)/T_CASE;
	 posClic.y = (clicY - CENTER_Y)/T_CASE;
	 return posClic;
}        
