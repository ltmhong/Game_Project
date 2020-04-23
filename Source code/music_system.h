#pragma once

#include "global.h"



//GAME'S BACK MUSIC


Mix_Music* loadMusic(const char* file)
{
	return Mix_LoadMUS(file);
}

void playMusic(Mix_Music* music, int loop = -1)
{
	Mix_PlayMusic(music, loop);
}

void pauseMusic()
{
	Mix_PauseMusic();
}

void resumeMusic()
{
	Mix_ResumeMusic();
}

void stopMusic()
{
	Mix_HaltMusic();
}

void freeMusic(Mix_Music* music)
{
	Mix_FreeMusic(music);
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