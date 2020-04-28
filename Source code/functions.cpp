#include "base_system.h"
#include "image_system.h"
#include "music_system.h"
#include <string>



//VARIABLES

int startLoop, endLoop;
int cameraSpeed = cameraBaseSpeed;
int gameEvent;
int rows, columns;
int maxScore = 0, score = 0, topScore = 0, coins = 0;
char chars[10] = "";										//Used in updateScore();
bool eagleIntersect = false;

deque<Object> objects;

Tile** map = NULL;

GameState state = START;
SDL_Rect realPlayerClip = { 30,0,40,100 };

Object Player;
Object Car, Log, Train, Light, Eagle, Coin;
Tile grass, bush, water, road, rail;

SDL_Texture* car2;
SDL_Texture* car3;
SDL_Texture* redLight;
SDL_Texture* cow;
SDL_Texture* sheep;
SDL_Texture* pig;

Other ScoreText, Logo, TryAgainButton, ClickButton, GameOverText, PauseButton,
PlayerChooseButton, PlayerButton, CoinText, TopScoreText;

TTF_Font* font;
Mix_Chunk* clickSound;



void load()
{
	grass.texture = loadImage("Photo/grass_pattern.png");
	grass.position = { 0, 0, 84, 84 };
	grass.type = GRASS;

	bush.texture = loadImage("Photo/bush_pattern.png");
	bush.position = { 0,0,84,84 };
	bush.type = BUSH;

	water.texture = loadImage("Photo/water_pattern.png");
	water.position = { 0,0,84,84 };
	water.type = WATER;

	road.texture = loadImage("Photo/road_pattern.png");
	road.position = { 0,0,84,84 };
	road.type = ROAD;

	rail.texture = loadImage("Photo/rail_pattern.png");
	rail.position = { 0,0,84,84 };
	rail.type = RAIL;


	Car.texture = loadImage("Photo/car01.png");
	Car.position = { 0, 0, 147, 71 };
	Car.isMoving = true;
	Car.type = CAR;
	Car.sfx = loadSfx("sound/car_horn.wav");
	car2 = loadImage("Photo/car02.png");
	car3 = loadImage("Photo/car03.png");

	Log.texture = loadImage("Photo/log.png");
	Log.position = { 0,0,84,84 };
	Log.type = LOG;
	Log.sfx = loadSfx("sound/water.wav");

	Train.texture = loadImage("Photo/train.png");
	Train.position = { 0, 0, 384, 82 };
	Train.type = TRAIN;
	Train.sfx = loadSfx("sound/train_pass_no_horn.wav");

	Light.texture = loadImage("Photo/green_light.png");
	Light.position = { 0, 0, 21, 77 };
	Light.type = LIGHT;
	Light.sfx = loadSfx("sound/train_alarm.wav");
	redLight = loadImage("Photo/red_light.png");

	Eagle.texture = loadImage("Photo/eagle.png");
	Eagle.position = { 0, 0, 162, 104 };
	Eagle.type = EAGLE;
	Eagle.moveSpeed = 20;
	Eagle.sfx = loadSfx("sound/eagle.wav");

	Coin.texture = loadImage("Photo/coin1.png");
	Coin.position = { SCREEN_WIDTH - 50, 50, 84, 84 };
	Coin.direction = LEFT;
	Coin.type = COIN;
	Coin.sfx = loadSfx("sound/coin.wav");

	initTiles();

	sheep = loadImage("Photo/player1.png");
	cow = loadImage("Photo/player2.png");
	pig = loadImage("Photo/player3.png");
	Player.texture = sheep;
	Player.tile = { columns / 2 , rows - 2 };
	Player.position = map[Player.tile.x][Player.tile.y].position;
	Player.type = PLAYER;
	Player.sfx = loadSfx("sound/smash.wav");

	font = TTF_OpenFont("Font/ARCADE_N.TTF", 72);
	ScoreText.texture = loadFont(font, "0", 255, 255, 255);
	ScoreText.position = { 20, 10, 31, 42 };

	TopScoreText.texture = loadFont(font, "HIGH SCORE: 0", 255, 255, 255);
	TopScoreText.position = { 20, 60, 130, 25 };

	CoinText.texture = loadFont(font, "0", 253, 230, 75);
	CoinText.position = { SCREEN_WIDTH - 85 , 10, 39, 50 };

	GameOverText.texture = loadFont(font, "GAME OVER!", 0, 0, 0);
	GameOverText.position = { (SCREEN_WIDTH - 345) / 2,(SCREEN_HEIGHT - 43) / 2,345,43 };

	Logo.texture = loadImage("Photo/Title.png");
	Logo.position = { (SCREEN_WIDTH - 764) / 2,(SCREEN_HEIGHT - 170) / 3, 780, 170 };

	ClickButton.texture = loadImage("Photo/click.png");
	ClickButton.position = { (SCREEN_WIDTH - 100) / 2,Logo.position.y + 190 , 100, 160 };

	TryAgainButton.texture = loadImage("Photo/again.png");
	TryAgainButton.position = { (SCREEN_WIDTH - 177) / 2,(SCREEN_HEIGHT / 2) + 150, 162, 107 };

	PauseButton.texture = loadImage("Photo/pause.png");
	PauseButton.position = { SCREEN_WIDTH - 70, 70, 50, 50 };

	PlayerChooseButton.texture = loadImage("Photo/settings.png");
	PlayerChooseButton.position = { 20, SCREEN_HEIGHT - 100, 125, 80 };

	clickSound = loadSfx("sound/click.wav");
}

void initTiles()
{
	columns = ceil(SCREEN_WIDTH / TILE_SIZE);
	rows = ceil(SCREEN_HEIGHT / TILE_SIZE) + 1;
	map = new Tile * [columns];
	for (int i = 0; i < columns; i++)
		map[i] = new Tile[rows];

	for (int y = rows - 1; y >= 0; y--)
	{
		if (y >= rows - 2)
		{
			for (int x = 0; x < columns; x++)
			{
				map[x][y] = (x == 0 || x == columns - 1) ? bush : grass;
				map[x][y].position.x = x * TILE_SIZE;
				map[x][y].position.y = (y - 1) * TILE_SIZE;
			}
		}
		else
		{
			generateTiles(y);
			addObjects(y);
		}
	}
}

void drawTiles()
{
	for (int i = 0; i < columns; i++)
		for (int j = 0; j < rows; j++) draw(map[i][j].texture, &map[i][j].position);
}

void drawObjects()
{
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i].direction == LEFT)
			draw(objects[i].texture, &objects[i].position);
		else
			drawEx(objects[i].texture, &objects[i].position, SDL_FLIP_HORIZONTAL);
	}
}

void update()
{
	adjustCameraSpeed();

	for (int y = 0; y < rows; y++)
		for (int x = 0; x < columns; x++)
			map[x][y].position.y += cameraSpeed;

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i].position.y += cameraSpeed;
		if (objects[i].type == CAR)
		{
			if (objects[i].direction == LEFT && objects[i].position.x < -Car.position.w)
				objects[i].position.x = SCREEN_WIDTH;
			else if (objects[i].direction == RIGHT && objects[i].position.x > SCREEN_WIDTH)
				objects[i].position.x = -Car.position.w;
		}

		if (objects[i].type == LOG) {
			if (objects[i].direction == LEFT && objects[i].position.x < -Log.position.w)
				objects[i].position.x = SCREEN_WIDTH;
			else if (objects[i].direction == RIGHT && objects[i].position.x > SCREEN_WIDTH)
				objects[i].position.x = -Log.position.w;
		}

		if (objects[i].type == TRAIN)
		{
			if (objects[i].isMoving)
			{
				if (objects[i].direction == LEFT && objects[i].position.x < -Train.position.w)
				{
					objects[i].position.x = SCREEN_WIDTH;
					objects[i].isMoving = false;
					objects[i + 1].texture = Light.texture; // We Are Sure there is a lamp just after a train!!
					objects[i].timer = ((rand() % 5) + 2) * FPS;
				}

				else if (objects[i].direction == RIGHT && objects[i].position.x > SCREEN_WIDTH)
				{
					objects[i].position.x = -Train.position.w;
					objects[i].isMoving = false;
					objects[i + 1].texture = Light.texture;
					objects[i].timer = ((rand() % 5) + 2) * FPS;
				}
			}
			else
			{
				if (objects[i].timer == FPS)		//1 Second Before it move we should change the lamp!!
				{
					objects[i + 1].texture = redLight;
					playSfx(Light.sfx, 0);
				}

				if (objects[i].timer == 0)
				{
					objects[i].isMoving = true;
					playSfx(Train.sfx, 0);
				}
				else objects[i].timer--;
			}
		}

		if (objects[i].isMoving)
		{
			if (objects[i].type == TRAIN)
				objects[i].position.x += (objects[i].direction == LEFT ? -trainSpeed : trainSpeed);
			else objects[i].position.x += objects[i].moveSpeed;
		}
	}

	if (map[0][rows - 1].position.y > SCREEN_HEIGHT)
	{
		for (int y = rows - 1; y > 0; y--)
			for (int x = 0; x < columns; x++) map[x][y] = map[x][y - 1];

		generateTiles(0);
		deleteObjects();

		for (int i = 0; i < objects.size(); i++) objects[i].tile.y += 1;
		addObjects(0);
		Player.tile.y += 1;
	}

	Player.position.y += cameraSpeed;

	checkPlayerStatus();
}

void checkPlayerStatus()
{
	if (state != PLAY) return;

	if (Player.position.y + 5 >= SCREEN_HEIGHT)
	{
		state = OUT;
		Eagle.position.x = Player.position.x - (Eagle.position.w / 2);
		Eagle.position.y = -Eagle.position.h;
		eagleIntersect = false;
		return;
	}

	if (Player.position.x <= -TILE_SIZE || Player.position.x >= SCREEN_WIDTH)
		state = GAME_OVER;

	bool onLog = false;
	SDL_Rect temp = { Player.position.x, Player.position.y, Player.position.w, Player.position.h };

	for (int i = 0; i < objects.size(); i++)
	{
		if (SDL_HasIntersection(&temp, &objects[i].position) == SDL_TRUE)
		{
			if (objects[i].type == CAR || objects[i].type == TRAIN)
			{
				state = GAME_OVER;
				playSfx(Player.sfx, 0);
			}
			else if (objects[i].type == LOG)
			{
				onLog = true;
				if (!Player.isMoving)
				{
					if (objects[i].isMoving) Player.position.x += objects[i].moveSpeed;
					if (Player.position.x >= map[Player.tile.x][0].position.x + TILE_SIZE) Player.tile.x++;
					else if (Player.position.x <= map[Player.tile.x][0].position.x - TILE_SIZE) Player.tile.x--;
					if (Player.tile.x >= columns || Player.tile.x < 0) state = GAME_OVER;
				}
			}
			else if (objects[i].type == COIN)
			{
				coins++;
				playSfx(Coin.sfx, 0);
				updateScore();
				objects.erase(objects.begin() + i);
				i--;
				continue;
			}
		}
	}
	if (!Player.isMoving && !onLog && map[Player.tile.x][Player.tile.y].type == WATER)
		state = GAME_OVER;
}

void adjustCameraSpeed()
{
	if (state == OUT)
	{
		cameraSpeed = -2;
		return;
	}

	if (state != PLAY)
	{
		cameraSpeed = 0;
		return;
	}

	cameraSpeed = cameraBaseSpeed;
	switch (Player.tile.y)
	{
		case 4:
			cameraSpeed += 1;
			break;
		case 3:
			cameraSpeed += 3;
			break;
		case 2:
			cameraSpeed += 6;
			break;
		case 1:
			cameraSpeed = playerSpeed;
			break;
	}
}

void generateTiles(int row)
{
	TileType rowType = (TileType)(rand() % 4);
	int rowChance = rand() % 100 + 1;
	int Trees = 0;
	for (int x = 0; x < columns; x++)
	{
		if (rowChance <= 50 /*rowType == GRASS*/)
		{
			int chance = rand() % 100 + 1;
			if (x == 0 || x == columns - 1)
				map[x][row] = bush;
			else
			{
				if (chance >= 80 && Trees < maxBushes)
				{
					map[x][row] = bush;
					Trees++;
				}
				else map[x][row] = grass;
			}
		}
		else if (rowChance <= 70) map[x][row] = road;		//rowType == ROAD
		else if (rowChance <= 75) map[x][row] = rail;		//rowType == RAIL
		else if (rowChance <= 100) map[x][row] = water;		//rowType == WATER

		map[x][row].position.x = x * TILE_SIZE;
		map[x][row].position.y = map[x][row + 1].position.y - TILE_SIZE;
	}
}

void addObjects(int row)
{
	if (map[0][row].type != WATER) addCoins(row);
	switch (map[0][row].type)
	{
		case ROAD:
			addCar(row);
			break;
		case WATER:
			addStick(row);
			break;
		case RAIL:
			addTrain(row);
			break;
	}
}

void addCar(int row) {
	Direction dir = (Direction)((rand() % 2) + 2);
	Car.direction = dir;
	Car.position.y = map[0][row].position.y + 6;
	Car.tile.y = row;
	Car.moveSpeed = (rand() % 5 + 2) * (dir == RIGHT ? 1 : -1);
	int num = (rand() % 3) + 1;
	int space = (SCREEN_WIDTH - ((num - 1) * Car.position.w)) / num;
	int randPos = rand() % SCREEN_WIDTH;
	for (int i = 0; i < num; i++)
	{
		objects.push_back(Car);
		if (dir == LEFT)
			objects.back().position.x = SCREEN_WIDTH + (i * (space + Car.position.w)) - randPos;
		else
			objects.back().position.x = -Car.position.w - (i * (space + Car.position.w)) + randPos;
		short int tex = rand() % 3;
		switch (tex)
		{
			case 1:
				objects.back().texture = car2;
				break;
			case 2:
				objects.back().texture = car3;
				break;
		}
	}
}

void addStick(int row)
{
	Log.position.y = map[0][row].position.y;
	Log.tile.y = row;
	if (map[0][row + 1].type == WATER)			// Direction of two rivers should be diffrent.
	{
		for (int i = objects.size() - 1; i >= 0; i--)
		{
			if (objects[i].tile.y == row + 1 && objects[i].type == LOG)
			{
				Log.direction = (objects[i].direction == LEFT ? RIGHT : LEFT);
				Log.isMoving = (objects[i].isMoving ? rand() % 2 : true); //We Cant Have Two Stopped Rivers
				break;
			}
		}
	}
	else
	{
		Log.isMoving = rand() % 2;
		Log.direction = (Direction)((rand() % 2) + 2);
	}

	if (Log.isMoving)
	{
		Log.moveSpeed = (rand() % 3 + 1) * (Log.direction == RIGHT ? 1 : -1);
		int num = (rand() % 4) + 3;
		int space = (SCREEN_WIDTH - ((num - 1) * Log.position.w)) / num;
		int randPos = rand() % 200;
		for (int i = 0; i < num; i++)
		{
			objects.push_back(Log);
			if (Log.direction == LEFT)
				objects.back().position.x = randPos + (i * (space + Log.position.w));
			else
				objects.back().position.x = SCREEN_WIDTH - randPos - (i * (space + Log.position.w));
		}
	}
	else
	{
		int num = 0;
		do
		{
			for (int i = 0; i < columns; i++)
			{
				if (map[i][row + 1].type != BUSH)
				{
					int chance = rand() % 100 + 1;
					if (chance >= 50 && num < maxLogs)
					{
						num++;
						Log.position.x = map[i][row].position.x;
						objects.push_back(Log);
					}
				}
			}
		} while (num < minLogs);
	}
}

void addTrain(int row)
{
	Direction dir = (Direction)((rand() % 2) + 2);
	Train.direction = dir;
	Train.position.y = map[0][row].position.y;
	Train.tile.y = row;
	Train.timer = ((rand() % 5) + 2) * FPS;

	objects.push_back(Train);
	if (dir == LEFT)
		objects.back().position.x = SCREEN_WIDTH + Train.position.w;
	else
		objects.back().position.x = -Train.position.w;

	Light.tile.y = row;
	Light.position.y = map[0][row].position.y + TILE_SIZE - Light.position.h;
	Light.position.x = map[0][row].position.x + 20;
	objects.push_back(Light);
}

void addCoins(int row)
{
	int num = 0;
	Coin.position.y = map[0][row].position.y;
	Coin.position.w = Coin.position.h = TILE_SIZE;
	Coin.tile.y = row;

	for (int i = 0; i < columns; i++)
	{
		if (map[i][row].type != BUSH)
		{
			int chance = rand() % 101;
			if (chance >= 90 && num < maxCoins)
			{
				num++;
				Coin.position.x = map[i][row].position.x;
				objects.push_back(Coin);
			}
		}
	}
}

void deleteObjects()
{
	while (!objects.empty() && objects.front().tile.y == rows - 1)
	{
		objects.pop_front();
	}
}

void draw()
{
	drawTiles();
	if (state == GAME_OVER) draw(Player.texture, &Player.position);		// If player lose, Draw it Under Objects!!
	drawObjects();

	if (state != GAME_OVER) draw(Player.texture, &Player.position);		// But If It is alive , Draw It top of Objects!
	draw(ScoreText.texture, &ScoreText.position);

	Coin.position = { SCREEN_WIDTH - 50,0,50,50 };
	draw(Coin.texture, &Coin.position);
	draw(CoinText.texture, &CoinText.position);
}

void start()
{
	draw(Logo.texture, &Logo.position);
	draw(ClickButton.texture, &ClickButton.position);
	draw(PlayerChooseButton.texture, &PlayerChooseButton.position);

	if (clickOnButton(&PlayerChooseButton.position)) state = CHOOSE_PLAYER;
	else if (g_event.type == SDL_MOUSEBUTTONDOWN && g_event.button.button == SDL_BUTTON_LEFT)
		state = PLAY;
}

void choose_player()
{
	int num = 3;
	PlayerButton.position = { (SCREEN_WIDTH - (num * 150 - 50)) / 2,(SCREEN_HEIGHT - 100) / 2,100,100 };

	for (int i = 0; i < num; i++)
	{
		switch (i)
		{
			case 0:
				PlayerButton.texture = sheep;
				break;

			case 1:
				PlayerButton.texture = cow;
				break;

			case 2:
				PlayerButton.texture = pig;
				break;
		}

		if (clickOnButton(&PlayerButton.position))
		{
			Player.texture = PlayerButton.texture;
			state = START;
			break;
		}

		SDL_SetRenderDrawColor(g_renderer, 0, 196, 255, 255);
		SDL_RenderFillRect(g_renderer, &PlayerButton.position);
		SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
		SDL_RenderDrawRect(g_renderer, &PlayerButton.position);
		draw(PlayerButton.texture, &PlayerButton.position);
		PlayerButton.position.x += 150;
	}
}

void play() {
	if (Player.isMoving)
	{
		switch (Player.direction)
		{
			case UP:
				Player.position.y -= playerSpeed;
				if (Player.position.y <= map[Player.tile.x][Player.tile.y - 1].position.y)
				{
					Player.isMoving = false;
					score++;
					Player.tile.y--;
					Player.position.y = map[Player.tile.x][Player.tile.y].position.y;
					//Player.position.x = map[Player.tile.x][Player.tile.y].position.x;
					if (map[Player.tile.x][Player.tile.y].type == ROAD) playSfx(Car.sfx, 0);
					else if (map[Player.tile.x][Player.tile.y].type == WATER) playSfx(Log.sfx, 0);
				}
				break;

			case RIGHT:
				Player.position.x += playerSpeed;
				if (Player.position.x >= map[Player.tile.x + 1][Player.tile.y].position.x)
				{
					Player.isMoving = false;
					Player.tile.x++;
					Player.position.x = map[Player.tile.x][Player.tile.y].position.x;
				}
				break;

			case LEFT:
				Player.position.x -= playerSpeed;
				if (Player.position.x <= map[Player.tile.x - 1][Player.tile.y].position.x)
				{
					Player.isMoving = false;
					Player.tile.x--;
					Player.position.x = map[Player.tile.x][Player.tile.y].position.x;
				}
				break;

			case DOWN:
				Player.position.y += playerSpeed;
				if (Player.position.y >= map[Player.tile.x][Player.tile.y + 1].position.y)
				{
					Player.isMoving = false;
					score--;
					Player.tile.y++;
					Player.position.y = map[Player.tile.x][Player.tile.y].position.y;
				}
				break;
		}
	}

	if (gameEvent == SDL_KEYDOWN && !Player.isMoving)
	{
		switch (g_event.key.keysym.sym)
		{
			case SDLK_UP:
				if (map[Player.tile.x][Player.tile.y - 1].type != BUSH)
				{
					Player.isMoving = true;
					Player.direction = UP;
					//Player.position.y -= playerMoveSpeed;
				}
				break;
			case SDLK_RIGHT:
				if (Player.tile.x + 1 < columns && map[Player.tile.x + 1][Player.tile.y].type != BUSH)
				{
					Player.isMoving = true;
					Player.direction = RIGHT;
					//Player.position.x += playerMoveSpeed;
				}
				break;
			case SDLK_LEFT:
				if (Player.tile.x - 1 >= 0 && map[Player.tile.x - 1][Player.tile.y].type != BUSH)
				{
					Player.isMoving = true;
					Player.direction = LEFT;
					//Player.position.x -= playerMoveSpeed;
				}
				break;
			case SDLK_DOWN:
				if (Player.tile.y + 1 < rows && map[Player.tile.x][Player.tile.y + 1].type != BUSH)
				{
					Player.isMoving = true;
					Player.direction = DOWN;
					//Player.position.y += playerMoveSpeed;
				}
				break;
		}
	}
	draw(PauseButton.texture, &PauseButton.position);
	if (clickOnButton(&PauseButton.position) || (gameEvent == SDL_KEYDOWN && g_event.key.keysym.sym == SDLK_SPACE))
		state = PAUSE;
		
	updateScore();
}

void updateScore()
{
	if (score > maxScore) maxScore = score;
	string all = to_string(maxScore);
	strcpy_s(chars, 10, all.c_str());

	//Destroy Perivious Texture And Make A New
	SDL_DestroyTexture(ScoreText.texture);
	ScoreText.texture = loadFont(font, chars, 255, 255, 255);

	all = to_string(coins);
	strcpy_s(chars, 10, all.c_str());

	//Destroy Perivious Texture And Make A New
	SDL_DestroyTexture(CoinText.texture);
	CoinText.texture = loadFont(font, chars, 253, 230, 75);
}

void pause() {
	SDL_Rect pauseRect = { (SCREEN_WIDTH - 300) / 2, (SCREEN_HEIGHT - 490) / 2, 305, 448 };
	draw(PauseButton.texture, &pauseRect);

	if (g_event.type == SDL_MOUSEBUTTONDOWN && g_event.button.button == SDL_BUTTON_LEFT
		|| (gameEvent == SDL_KEYDOWN && g_event.key.keysym.sym == SDLK_SPACE))
		state = PLAY;
}

void eagle()
{
	Eagle.position.y += Eagle.moveSpeed;
	draw(Eagle.texture, &Eagle.position);

	if (!eagleIntersect && SDL_HasIntersection(&Player.position, &Eagle.position))
	{
		Player.position.x = SCREEN_WIDTH;			//Move it to a hidden Area
		playSfx(Eagle.sfx, 0);
		eagleIntersect = true;
	}

	if (Eagle.position.y > SCREEN_HEIGHT) state = GAME_OVER;
}

void game_over()
{
	SDL_Rect gameOverRect = { 0,(SCREEN_HEIGHT - 100) / 2, SCREEN_WIDTH, 100 };
	SDL_SetRenderDrawColor(g_renderer, 0, 200, 255, 255);
	SDL_RenderFillRect(g_renderer, &gameOverRect);
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	draw(GameOverText.texture, &GameOverText.position);
	draw(TryAgainButton.texture, &TryAgainButton.position);

	if (maxScore > topScore) topScore = maxScore;
	string all = "HIGH SCORE: " + to_string(topScore);
	SDL_DestroyTexture(TopScoreText.texture);
	TopScoreText.texture = loadFont(font, all, 255, 255, 255);
	draw(TopScoreText.texture, &TopScoreText.position);

	if (clickOnButton(&TryAgainButton.position))
	{
		destroyTiles();
		objects.clear();				//Destroy Objects!
		maxScore = score = coins = 0;
		updateScore();
		initTiles();					//ReGenerate The Envirement!
		Player.tile = { columns / 2 , rows - 2 };
		Player.position = map[Player.tile.x][Player.tile.y].position;
		state = START;
	}
}

void destroyTiles() {
	for (int i = 0; i < rows; i++)
		delete[] map[i];

	delete[] map;
}

bool clickOnButton(SDL_Rect* r)
{
	SDL_Point mouse_point = { g_event.motion.x , g_event.motion.y };
	if (g_event.type == SDL_MOUSEBUTTONDOWN && g_event.button.button == SDL_BUTTON_LEFT && SDL_PointInRect(&mouse_point, r))
	{
		playSfx(clickSound, 0);
		return true;
	}
	return false;
}