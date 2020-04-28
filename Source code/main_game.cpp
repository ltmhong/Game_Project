#include "base_system.h"
#include <cstdlib>
#include <ctime>



int main(int argc, char* argv[])
{
	init();
	createWindow();
	load();
	srand(time(NULL));
	
	while (state != QUIT)
	{
		startLoop = SDL_GetTicks();
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
		endLoop = SDL_GetTicks() - startLoop;
		if (endLoop < delay) SDL_Delay(delay - endLoop);

		SDL_RenderPresent(g_renderer);
		SDL_RenderClear(g_renderer);
	}

	close();

	return 0;
}