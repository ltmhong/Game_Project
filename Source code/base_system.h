#pragma once

#include "global.h"
#include <deque>


enum TileType { GRASS, WATER, ROAD, RAIL, BUSH };
enum ObjectType { PLAYER, CAR, TRAIN, LOG, LIGHT, EAGLE, COIN };
enum GameState { START, PLAY, QUIT, PAUSE, GAME_OVER, OUT, CHOOSE_PLAYER };
enum Direction { UP, DOWN, LEFT, RIGHT };

struct Object
{
	SDL_Rect position;
	SDL_Texture* texture;
	ObjectType type;
	SDL_Point tile;
	bool isMoving = false;
	Direction direction;
	Mix_Chunk* sfx = NULL;

	union
	{
		int moveSpeed;		//for everything else
		int timer;			//for trains
	};
};


struct Tile
{
	TileType type;
	SDL_Rect position;
	SDL_Texture* texture;
};


struct Other			//For Fonts, Buttons, logo,... !
{
	SDL_Rect position;
	SDL_Texture* texture;
};



//VARIABLES

extern int startLoop, endLoop;
extern int cameraSpeed;
extern int gameEvent;
extern int rows, columns;
extern int maxScore, score, coins, topScore;
extern bool eagleIntersect;



extern Tile** map;

extern GameState state;

extern Object Player;
extern Object Car, Log, Train, Light, Eagle, Coin;
extern Tile grass, bush, water, road, rail;

extern SDL_Texture* car2;
extern SDL_Texture* car3;
extern SDL_Texture* redLight;
extern SDL_Texture* cow;
extern SDL_Texture* sheep;
extern SDL_Texture* pig;

extern Other ScoreText, Logo, TryAgainButton, ClickButton, GameOverText, PauseButton,
				PlayerChooseButton, PlayerButton, CoinText, TopScoreText;

extern TTF_Font* font;
extern Mix_Chunk* clickSound;



//Function Portotypes


void load();

void initTiles();
void drawTiles();
void drawObjects();

void update();
void checkPlayerStatus();
void adjustCameraSpeed();

void generateTiles(int);
void addObjects(int);
void addCar(int);
void addStick(int);
void addTrain(int);
void addCoins(int);

void deleteObjects();

void draw();
void start();
void choose_player();
void play();
void updateScore();
void pause();
void eagle();
void game_over();
void destroyTiles();
bool clickOnButton(SDL_Rect*);