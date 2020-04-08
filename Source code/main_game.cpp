#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

using namespace std;

//GLOBAL VARIABLES

SDL_Window* g_window = NULL;								//The window we'll be rendering to
SDL_Renderer* g_renderer = NULL;							//The window renderer

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 700;

//PROTOTYPE

bool init();											//Starts up SDL and creates window
bool loadMedia();										//Loads media
void close();											//Frees media and shuts down SDL

class Texture						//Texture wrapper class
{
private:
	SDL_Texture* texture;			//The actual hardware texture

	//Image dimensions
	int width;
	int height;

public:
	Texture();								//Initializes variables
	~Texture();								//Deallocates memory
	bool loadFromFile(string path);			//Loads image at specified path
	void free();							//Deallocates texture
	void render(int x, int y);				//Renders texture at given point

	//Gets image dimensions
	int getWidth();
	int getHeight();
};

//SCENE TEXTURES

Texture player;
Texture background;

//CLASS Texture's (CONSTRUCTORS + FUNCTIONS) DEFINITIONS

Texture::Texture()
{
	//Initialize
	texture = NULL;
	width = 0;
	height = 0;
}

Texture::~Texture()
{
	free();			//Deallocate
}

bool Texture::loadFromFile(string path)
{
	free();							//Get rid of pre-existing texture
	SDL_Texture* final = NULL;		//The final texture

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) cout << "Unable to load image " << path.c_str() << "SDL_image Error: " << IMG_GetError() << endl;
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

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

void Texture::free()
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

void Texture::render(int x, int y)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, width, height };
	SDL_RenderCopy(g_renderer, texture, NULL, &renderQuad);
}

int Texture::getWidth()
{
	return width;
}

int Texture::getHeight()
{
	return height;
}

//main() FUNCTION

int main(int argc, char* argv[])
{
	//Start up SDL and create window
	if (!init())
	{
		cout << "Failed to initialize!" << endl;
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			cout << "Failed to load media!" << endl;
		}
		else
		{
			bool quit = false;                      //Main loop flag
			SDL_Event e;                            //Event handler
			while (!quit)                           //while application is running
			{
				while (SDL_PollEvent(&e) != 0)      //Handle events on queue
					if (e.type == SDL_QUIT) quit = true;

				SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(g_renderer);          //Clear screen

				background.render(0, 0);									//Render background texture to screen
				player.render(SCREEN_WIDTH / 2 - 70, SCREEN_HEIGHT - 140);			//Render man to the screen

				SDL_RenderPresent(g_renderer);		//Update screen
			}
		}
	}
	close();			//Free and close SDL

	return 0;
}

//FUNCTIONS DEFINITIONS

bool init()
{
	bool success = true;			//Initialization flag

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) cout << "Warning: Linear texture filtering not enabled!";

		//Create window
		g_window = SDL_CreateWindow("JiLL being STUPID", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (g_window == NULL)
		{
			cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
			success = false;
		}
		else
		{
			g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);        //Create renderer for window
			if (g_renderer == NULL)
			{
				cout << "Renderer could not be create! SDL Error: " << SDL_GetError() << endl;
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF);           //Initialize renderer color
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	bool success = true;			//Loading success flag

	if (!player.loadFromFile("Photo/tempo_player.png"))
	{
		cout << "Failed to load character!" << endl;
		success = false;
	}

	//Load background texture
	if (!background.loadFromFile("Photo/tempo_back.png"))
	{
		cout << "Failed to load background!" << endl;
		success = false;
	}

	return success;
}

void close()
{
	//Free loaded images
	player.free();
	background.free();

	//Destroy window
	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);
	g_renderer = NULL;
	g_window = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}