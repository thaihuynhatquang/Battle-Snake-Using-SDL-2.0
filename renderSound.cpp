#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "renderSound.h"

Mix_Music *startSound;
Mix_Chunk *eatSound;
Mix_Chunk *clickSound;
Mix_Chunk *dropBombSound;
Mix_Chunk *gameoverSound;

void loadSound()
{
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		std::cout << "Failed to load beat music! SDL_mixer Error: " << Mix_GetError() << std::endl;
	}
	startSound = Mix_LoadMUS("Sound/startSound.wav");
	eatSound = Mix_LoadWAV("Sound/eatSound.wav");
	clickSound = Mix_LoadWAV("Sound/clickSound.wav");
	dropBombSound = Mix_LoadWAV("Sound/dropBombSound.wav");
	gameoverSound = Mix_LoadWAV("Sound/gameoverSound.wav");
}

void playStartSound()
{
    if(Mix_PlayingMusic() == 0)
    {
       Mix_PlayMusic(startSound, -1);
    }
}

void playEatingSound()
{
    Mix_PlayChannel(-1, eatSound, 0);
}

void playClickSound()
{
    Mix_PlayChannel(-1, clickSound, 0);
}

void playDropBombSound()
{
    Mix_PlayChannel(-1, dropBombSound, 0);
}

void playGameoverSound()
{
    Mix_PlayChannel(-1, gameoverSound, 0);
}
