#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <iostream>

using namespace std;


//BASIC VARIABLES FOR SDL PROGRAM

extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern SDL_Event g_event;
extern Mix_Music* g_music;



//CONSTANTS

const int SCREEN_WIDTH = 1092;
const int SCREEN_HEIGHT = 756;
const int TILE_SIZE = 84;

const int playerSpeed = 10;
const int trainSpeed = 18;
const int cameraBaseSpeed = 1;		//speed when player doesn't move (normal speed)

const int maxBushes = 3;			//maximum number of bushes in a row
const int maxLogs = 5;				//maximum number of logs in a row
const int minLogs = 2;				//minimum number of logs in a row
const int maxCoins = 2;				//maximum number of coins in a row

const int FPS = 60;					//frames per second
const int delay = 1000 / FPS;



//GENERATE AND END PROGRAM

bool init();
bool createWindow();
int getEvent();
void close();