#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "variables_prototype.h"
#include "class_GameTexture.h"

using namespace std;

GameTexture player;
GameTexture background;

//CLASS Texture's (CONSTRUCTORS + FUNCTIONS) DEFINITIONS

GameTexture::GameTexture()
{
	//Initialize
	texture = NULL;
	width = 0;
	height = 0;
}

GameTexture::~GameTexture()
{
	free();			//Deallocate
}

bool GameTexture::loadFromFile(string path)
{
	free();							//Get rid of pre-existing texture
	SDL_Texture* final = NULL;		//The final texture

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) cout << "Unable to load image " << path.c_str() << "SDL_image Error: " << IMG_GetError() << endl;
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));

		//Create texture from surface pixels
		final = SDL_CreateTextureFromSurface(g_renderer, loadedSurface);
		if (final == NULL) cout << "Unable to create texture from " << path.c_str() << "SDL_image Error: " << IMG_GetError() << endl;
		else
		{
			//Get image dimensions
			width = loadedSurface->w;
			height = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);			//Get rid of old loaded surface
	}

	//Return success
	texture = final;
	return texture != NULL;
}

void GameTexture::free()
{
	//Free texture if it exists
	if (texture != NULL)
	{
		SDL_DestroyTexture(texture);
		texture = NULL;
		width = 0;
		height = 0;
	}
}

void GameTexture::render(int x, int y)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, width, height };
	SDL_RenderCopy(g_renderer, texture, NULL, &renderQuad);
}

int GameTexture::getWidth()
{
	return width;
}

int GameTexture::getHeight()
{
	return height;
}