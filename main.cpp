#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include "renderSnake.h"
#include "renderSound.h"
#include "renderImage.h"
#include "handleEvent.h"
#include "controlGame.h"
bool running = true, pause = false, gameOver = false, start = false, restart = false, showHowToPlayScreen = false, mute = false;

void checkResult();
void playGame();

int main(int argc, char* argv[])
{
    SDL_Event event;
	Init();
	loadImage();
	loadSound();
	srand(time(NULL));
    CreateGame();
	while (running == true)
	{
        playStartSound();
		waitEvent(event);
		if(restart == true)
        {
            reCreateGame();
            restart = false;
        }
        if(start == true) drawButton();
        if(pause == false && gameOver == false && start == true)
        {
            playGame();
        }
	}
    return 0;
}

void playGame()
{
    moveA();
    moveB();
    eatFoodA();
    eatFoodB();
    throughBomb();
    eatBomb();
    checkResult();
    drawPlayScreen();
}

void checkResult()
{
    if(scoreA == 50)
    {
        Result = -1;
        gameOver = true;
        playGameoverSound();
        return;
    }
    if(scoreB == 50)
    {
        Result = 1;
        gameOver = true;
        playGameoverSound();
        return;
    }
    if(displaySnakeLengthA < 2)
    {
        Result = 1;
        gameOver = true;
        playGameoverSound();
        return;
    }
    if(displaySnakeLengthB < 2)
    {
        Result  = -1;
        gameOver = true;
        playGameoverSound();
        return;
    }
    gameOver = false;
}
