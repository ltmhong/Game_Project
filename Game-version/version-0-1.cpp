#include <iostream>
#include <deque>
#include <vector>
#include <conio.h>
#include <time.h>

using namespace std;

//Declare global variables



//Functions Definitions

class Player
{
public:
	int x, y;
	Player(int width) { x = width / 2; y = 0; }
};

class roadLane
{
private:
	deque<bool> cars;
	bool right;
public:
	roadLane(int width)
	{
		for (int i = 0; i < width; i++) cars.push_front(true);
		right = rand() % 2;
	}

	void move()
	{
		if (right)
		{
			if (rand() % 10 == 1) cars.push_front(true);
			else cars.push_front(false);
			cars.pop_back();
		}
		else
		{
			if (rand() % 10 == 1) cars.push_back(true);
			else cars.push_back(false);
			cars.pop_front();
		}
	}
	bool checkPosition(int pos) { return cars[pos]; }
};

class Game
{
private:
	bool quit;
	int laneNumbers;
	int width;
	int score;
	Player* player;
	vector<roadLane*> map;
public:
	Game(int w = 20, int h = 10)
	{
		laneNumbers = h;
		width = w;
		quit = false;
		for (int i = 0; i < laneNumbers; i++) map.push_back(new roadLane(width));
		player = new Player(width);
	}
	~Game()
	{
		delete player;
		for (int i = 0; i < map.size(); i++)
		{
			roadLane* current = map.back();
			map.pop_back();
			delete current;
		}
	}
	void Draw()
	{
		system("cls");
		for (int i = 0; i < laneNumbers; i++)
		{
			for (int j = 0; j < width; j++)
			{
				
				if (map[i]->checkPosition(j) && i != 0 && i != (laneNumbers - 1)) cout << "###";
				else if (player->x == j && player->y == i) cout << "O-O";
				else cout << "   ";
			}
			cout << endl;
		}
		cout << "Your score: " << score << endl;
	}

	void Input()
	{
		if (_kbhit())
		{
			char current = _getch();
			if (current == 'a')
				player->x--;
			if (current == 'd')
				player->x++;
			if (current == 'w')
				player->y--;
			if (current == 's')
				player->y++;
			if (current == 'q')
				quit = true;
		}
	}

	void Logic()
	{
		for (int i = 1; i < laneNumbers - 1; i++)
		{
			if (rand() % 10 == 1) map[i]->move();
			if (map[i]->checkPosition(player->x) && player->y == i) quit = true;
		}
		if (player->y == laneNumbers - 1)
		{
			score++;
			player->y = 0;
			cout << "\x07";
		}
	}

	void Run()
	{
		while (!quit)
		{
			Input();
			Draw();
			Logic();
		}
	}
};

//main() function

int main()
{
	srand(time(NULL));
	Game game(20, 10);
	game.Run();

	cout << "Game Over! Yor BIG LOSER!" << endl;

	getchar();
	
	return 0;
}