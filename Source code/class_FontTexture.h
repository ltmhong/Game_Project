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
	FontTexture();																//Initializes variables
	~FontTexture();																//Deallocates memory
	bool loadFromRenderedText(string textureText, SDL_Color textColor);			//Creates image from font string
	void free();																//Deallocates texture
	void render(int x, int y);													//Renders texture at given point

	//Gets image dimensions
	int getWidth();
	int getHeight();
};

//FONT TEXTURES

extern FontTexture g_textTexture;

#endif