#pragma once

#include "global.h"


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