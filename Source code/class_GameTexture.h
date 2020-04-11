#pragma once

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

#ifndef CLASS_GAME_TEXTURE__H
#define CLASS_GAME_TEXTURE__H

using namespace std;

class GameTexture						//Texture wrapper class
{
private:
	SDL_Texture* texture;			//The actual hardware texture

	//Image dimensions
	int width;
	int height;

public:
	GameTexture();							//Initializes variables
	~GameTexture();							//Deallocates memory
	bool loadFromFile(string path);			//Loads image at specified path
	void free();							//Deallocates texture
	void render(int x, int y);				//Renders texture at given point

	//Gets image dimensions
	int getWidth();
	int getHeight();
};

//SCENE TEXTURES

extern GameTexture player;
extern GameTexture background;

#endif