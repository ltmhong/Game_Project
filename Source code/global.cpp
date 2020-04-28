#include "base_system.h"

SDL_Window* g_window;
SDL_Renderer* g_renderer;
SDL_Event g_event;
Mix_Music* g_music = Mix_LoadMUS("sound/back_music.mp3");

bool init()
{
	bool success;
	if ((SDL_Init(SDL_INIT_EVERYTHING) == 0) && (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == 0) && (TTF_Init() == 0))
		success = true;
	else success = false;

	return success;
}

bool createWindow()
{
	g_window = SDL_CreateWindow("JiLL  being STUPID", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
								SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
	if (g_window != 0)
	{
		g_renderer = SDL_CreateRenderer(g_window, -1, 0);
		if (g_renderer != 0)
		{
			SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			return true;
		}
	}
	return false;
}

int getEvent()
{
	if (SDL_PollEvent(&g_event) != 0)
	{
		return g_event.type;
	}
	return 0;
}

void close()
{
	destroyTiles();
	SDL_DestroyTexture(grass.texture);
	SDL_DestroyTexture(bush.texture);
	SDL_DestroyTexture(water.texture);
	SDL_DestroyTexture(road.texture);
	SDL_DestroyTexture(rail.texture);

	SDL_DestroyTexture(Car.texture);
	Mix_FreeChunk(Car.sfx);
	SDL_DestroyTexture(car2);
	SDL_DestroyTexture(car3);

	SDL_DestroyTexture(Log.texture);
	Mix_FreeChunk(Log.sfx);

	SDL_DestroyTexture(Train.texture);
	Mix_FreeChunk(Train.sfx);

	SDL_DestroyTexture(Light.texture);
	Mix_FreeChunk(Light.sfx);
	SDL_DestroyTexture(redLight);

	SDL_DestroyTexture(Eagle.texture);
	Mix_FreeChunk(Eagle.sfx);

	SDL_DestroyTexture(Coin.texture);
	Mix_FreeChunk(Coin.sfx);

	SDL_DestroyTexture(sheep);
	SDL_DestroyTexture(cow);
	SDL_DestroyTexture(pig);
	Mix_FreeChunk(Player.sfx);

	SDL_DestroyTexture(ScoreText.texture);
	SDL_DestroyTexture(TopScoreText.texture);

	SDL_DestroyTexture(CoinText.texture);

	SDL_DestroyTexture(GameOverText.texture);
	SDL_DestroyTexture(Logo.texture);

	SDL_DestroyTexture(ClickButton.texture);
	SDL_DestroyTexture(TryAgainButton.texture);
	SDL_DestroyTexture(PauseButton.texture);
	SDL_DestroyTexture(PlayerChooseButton.texture);

	Mix_FreeChunk(clickSound);
	
	IMG_Quit();
	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);
	SDL_Quit();
}