#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "variables_prototype.h"
#include "class_FontTexture.h"

using namespace std;

FontTexture g_textTexture;

//CLASS Texture's (CONSTRUCTORS + FUNCTIONS) DEFINITIONS

FontTexture::FontTexture()
{
	//Initialize
	texture = NULL;
	width = 0;
	height = 0;
}

FontTexture::~FontTexture()
{
	free();			//Deallocate
}

bool FontTexture::loadFromRenderedText(string textureText, SDL_Color textColor)
{
	free();			//Get rid of preexisting texture

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(g_font, textureText.c_str(), textColor);
	if (textSurface == NULL)
	{
		cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << endl;
	}
	else
	{
		//Create texture from surface pixels
		texture = SDL_CreateTextureFromSurface(g_renderer, textSurface);
		if (texture == NULL)
		{
			cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << endl;
		}
		else
		{
			//Get image dimensions
			width = textSurface->w;
			height = textSurface->h;
		}

		SDL_FreeSurface(textSurface);			//Get rid of old surface
	}

	return texture != NULL;						//Return success
}

void FontTexture::free()
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

void FontTexture::render(int x, int y)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, width, height };
	SDL_RenderCopy(g_renderer, texture, NULL, &renderQuad);
}

int FontTexture::getWidth()
{
	return width;
}

int FontTexture::getHeight()
{
	return height;
}