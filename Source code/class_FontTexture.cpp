#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "variables_prototype.h"
#include "class_FontTexture.h"

using namespace std;

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

bool FontTexture::loadFromFile(string path)
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

void FontTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, width, height };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(g_renderer, texture, clip, &renderQuad, angle, center, flip);
}

int FontTexture::getWidth()
{
	return width;
}

int FontTexture::getHeight()
{
	return height;
}