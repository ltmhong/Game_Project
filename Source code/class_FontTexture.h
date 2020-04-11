#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "variables_prototype.h"

#ifndef CLASS_FONTTEXTURE__H
#define CLASS_FONTTEXTURE__H

using namespace std;

class FontTexture						//Texture wrapper class
{
private:
	SDL_Texture* texture;			//The actual hardware texture

	//Image dimensions
	int width;
	int height;

public:
	FontTexture();																	//Initializes variables
	~FontTexture();																	//Deallocates memory
	bool loadFromFile(string path);												//Loads image at specified path
	bool loadFromRenderedText(string textureText, SDL_Color textColor);			//Creates image from font string
	void free();																//Deallocates texture
	void setColor(Uint8 red, Uint8 green, Uint8 blue);							//Set color modulation
	void setBlendMode(SDL_BlendMode blending);									//Set blending
	void setAlpha(Uint8 alpha);													//Set alpha modulation
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0,		//Renders texture at given point
		SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Gets image dimensions
	int getWidth();
	int getHeight();
};

//FONT TEXTURES

extern FontTexture g_textTexture;

#endif