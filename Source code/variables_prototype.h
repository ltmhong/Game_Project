#pragma once

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#ifndef VARIABLES_PROTOTYPE__H
#define VARIABLES_PROTOTYPE__H

using namespace std;

//GLOBAL VARIABLES

extern SDL_Window* g_window;					//The window we'll be rendering to
extern SDL_Renderer* g_renderer;				//The window renderer
extern TTF_Font* g_font;						//Global used font

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 700;

//PROTOTYPE

bool init();											//Starts up SDL and creates window
bool loadMedia();										//Loads media
void close();											//Frees media and shuts down SDL

#endif