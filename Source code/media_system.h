#pragma once

#include "global.h"



//LOAD IMAGE FROM FILE

SDL_Texture* loadImage(const char* path)
{
	SDL_Surface* surface = IMG_Load(path);
	if (surface != NULL)
	{
		SDL_Texture* texture = SDL_CreateTextureFromSurface(g_renderer, surface);
		SDL_FreeSurface(surface);
		if (texture != NULL)
		{
			return texture;
		}
	}

	return NULL;
}



//DRAW FUNCTIONS

void draw(SDL_Texture* texture, SDL_Rect* destination, bool fullscreen = false)
{
	if (!fullscreen) SDL_RenderCopy(g_renderer, texture, 0, destination);
	else SDL_RenderCopy(g_renderer, texture, 0, 0);
}

void drawEx(SDL_Texture* texture, SDL_Rect* destination, SDL_RendererFlip flip, bool fullscreen = false)
{
	if (!fullscreen) SDL_RenderCopyEx(g_renderer, texture, 0, destination, 0, 0, flip);
	else SDL_RenderCopyEx(g_renderer, texture, 0, 0, 0, 0, flip);
}





//LOAD FONTS

SDL_Texture* loadFont(TTF_Font* font, string title, Uint8 r, Uint8 g, Uint8 b)
{
	SDL_Color color = { r, g, b, 255};
	SDL_Surface* surface = TTF_RenderText_Solid(font, title.c_str(), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(g_renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}




//GAME'S SFX SOUNDS

Mix_Chunk* loadSfx(const char* path)
{
	return Mix_LoadWAV(path);
}

void playSfx(Mix_Chunk* sfx, int loop)
{
	Mix_PlayChannel(-1, sfx, loop);
}

void pauseSfx()
{
	Mix_Pause(-1);
}