#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "variables_prototype.h"
#include "class_GameTexture.h"
#include "class_FontTexture.h"

using namespace std;	

//main() FUNCTION

int main(int argc, char* argv[])
{
	//Start up SDL and create window
	if (!init())
	{
		cout << "Failed to initialize!" << endl;
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			cout << "Failed to load media!" << endl;
		}
		else
		{
			bool quit = false;                      //Main loop flag
			SDL_Event e;                            //Event handler
			while (!quit)                           //while application is running
			{
				while (SDL_PollEvent(&e) != 0)      //Handle events on queue
					if (e.type == SDL_QUIT) quit = true;

				SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(g_renderer);          //Clear screen

				background.render(0, 0);										//Render background texture to screen
				player.render(SCREEN_WIDTH / 2 - 70, SCREEN_HEIGHT - 140);		//Render man to the screen

				//Render current frame
				g_textTexture.render(15, 10);

				SDL_RenderPresent(g_renderer);		//Update screen
			}
		}
	}
	close();			//Free and close SDL

	return 0;
}