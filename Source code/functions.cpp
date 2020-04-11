#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "variables_prototype.h"
#include "class_GameTexture.h"
#include "class_FontTexture.h"

using namespace std;

//GLOBAL VARIABLES

SDL_Window* g_window = NULL;					//The window we'll be rendering to
SDL_Renderer* g_renderer = NULL;				//The window renderer
TTF_Font* g_font = NULL;						//Global used font

//FUNCTIONS DEFINITIONS

bool init()
{
	bool success = true;			//Initialization flag

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) cout << "Warning: Linear texture filtering not enabled!";

		//Create window
		g_window = SDL_CreateWindow("JiLL being STUPID", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (g_window == NULL)
		{
			cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
			success = false;
		}
		else
		{
			g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);        //Create renderer for window
			if (g_renderer == NULL)
			{
				cout << "Renderer could not be create! SDL Error: " << SDL_GetError() << endl;
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);           //Initialize renderer color
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
					success = false;
				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << endl;
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()			//Loads media
{
	bool success = true;			//Loading success flag

	if (!player.loadFromFile("Photo/tempo_player.png"))
	{
		cout << "Failed to load character!" << endl;
		success = false;
	}

	//Load background texture
	if (!background.loadFromFile("Photo/tempo_back.png"))
	{
		cout << "Failed to load background!" << endl;
		success = false;
	}
	
	g_font = TTF_OpenFont("Font/SFURhythmRegular.ttf", 50);
	if (g_font == NULL)
	{
		cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << endl;
		success = false;
	}

	else
	{
		//Render text
		SDL_Color textColor = { 0, 0, 100 };
		if (!g_textTexture.loadFromRenderedText("CROSS    THE    ROAD", textColor))
		{
			cout << "Failed to render text texture!" << endl;
			success = false;
		}
	}

	return success;
}

void close()			//Frees media and shuts down SDL
{
	//Free loaded images
	player.free();
	background.free();
	g_textTexture.free();

	//Free global font
	TTF_CloseFont(g_font);
	g_font = NULL;

	//Destroy window
	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);
	g_renderer = NULL;
	g_window = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}