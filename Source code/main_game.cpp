#include "base_system.h"
#include <cstdlib>
#include <ctime>



//REFERENCES

/*
	LOGIC FOR SETTING DEFAULTED POSITION FOR THE CHARACTER (WHEN STARTING GAME)
		https://www.youtube.com/watch?v=06-ZvYmSeus (The Coding Train)

	HOW TO USE DEQUE
		1. https://www.youtube.com/watch?v=gyb8y-vK_g8 (NVitanovic)
		2. https://www.youtube.com/watch?v=MRzl0Is_Nd8 (NVitanovic)
		3. https://www.youtube.com/watch?v=NzozgsaWwQM (NVitanovic)
*/



int main(int argc, char* argv[])
{
	init();
	createWindow();
	load();
	srand(time(NULL));
	
	while (state != QUIT)
	{
		gameEvent = getEvent();
		draw();
		if (state != PAUSE) update();
		switch (state)
		{
			case START:
				start();
				break;

			case PLAY:
				play();
				break;

			case OUT:
				eagle();
				break;

			case PAUSE:
				pause();
				break;

			case CHOOSE_PLAYER:
				choose_player();
				break;

			case GAME_OVER:
				game_over();
				break;
		}

		if (gameEvent == SDL_QUIT || (gameEvent == SDL_KEYDOWN && g_event.key.keysym.sym == SDLK_ESCAPE)) state = QUIT;
		SDL_Delay(delay);

		SDL_RenderPresent(g_renderer);
		SDL_RenderClear(g_renderer);
	}

	close();

	return 0;
}