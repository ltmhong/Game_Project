#pragma once

#include "global.h"
#include <deque>


enum TileType { GRASS, WATER, ROAD, RAIL, BUSH };
enum ObjectType { PLAYER, CAR, TRAIN, LOG, LIGHT, EAGLE, COIN };
enum GameState { START, PLAY, QUIT, PAUSE, GAME_OVER, OUT, CHOOSE_PLAYER };
enum Direction { UP, DOWN, LEFT, RIGHT };

struct Object
{
	SDL_Rect position;			//objects' size and position
	SDL_Texture* texture;
	ObjectType type;			//types of objects: cars, logs, coins, trains, etc
	SDL_Point tile;				//coordinates of objects
	bool isMoving = false;		//check whether the objects (logs) are moving or not
	Direction direction;		//direction of objects
	Mix_Chunk* sfx = NULL;		//sounds that objects create (sfx)

	union
	{
		int moveSpeed;		//for everything else
		int timer;			//for trains
	};
};


struct Tile
{
	TileType type;				//types of the tiles: grass, bush, water, etc
	SDL_Rect position;			//position of tiles
	SDL_Texture* texture;
};


struct Other			//For Fonts, Buttons, logo,... !
{
	SDL_Rect position;
	SDL_Texture* texture;
};



//VARIABLES

extern int cameraSpeed;
extern int gameEvent;
extern int rows, columns;
extern int maxScore, score, coins, highScore;			//we update score with 'maxScore' instead of 'score'
extern bool eagleIntersect;



extern Tile** map;				//creating tile map

extern GameState state;			//states of game: start, play, pause, gameOver, etc

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
				PlayerChooseButton, PlayerButton, CoinText, HighScoreText;

extern TTF_Font* font;
extern Mix_Chunk* clickSound;		//the sound when you click mouse button



//Function Portotypes


void load();									//load every media that needed

void generateTiles(int);						//generate all types of tiles
void addCar(int);								//add cars
void addLogs(int);								//COPY FUNCTION - add logs to the river (water)
void addTrain(int);								//add trains
void addCoins(int);								//add coins
void addObjects(int);							//add every objects

void initTiles();								//get everything generated and added on the screen

void update();									//update everything: state, render, player's action
void checkPlayerStatus();						//check player's state: on logs?, fall into water?, crashed?, in/out of the screen?
void adjustCameraSpeed();						//adjust the screen's render to follow player's position

void deleteObjects();							//delete objects when they are out of the screen

void drawTiles();								//draw all Tiles
void drawObjects();								//draw all objects
void draw();									//draw everything in the game

void choose_player();
bool clickOnButton(SDL_Rect*);					//check if we click the mouse button
void play();									//in game
void start();									//starting game
void updateScore();
void pause();
void eagle();
void game_over();

void destroyTiles();							//delete the entire map