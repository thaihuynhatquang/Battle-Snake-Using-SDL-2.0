#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <stdlib.h>
#include "renderImage.h"
#include "renderSound.h"
#include "renderSnake.h"

extern bool pause, gameOver, start, restart, showHowToPlayScreen, mute;
const int UP = 0, DOWN = 2, LEFT = 3, RIGHT = 1;
int speed = 45, bombA_num = 0, bombB_num = 0, size = 35, Result = 0;
int preDirectionA = RIGHT, directionA = LEFT, preDirectionB = LEFT, directionB = RIGHT;
bool bombAStatus[10000], bombBStatus[10000];
SDL_Rect Arena = {352, 29, 630, 630};
TTF_Font* comic;
SDL_Window *windows;
SDL_Renderer *renderer;
void Init()
{
    SDL_Init(SDL_INIT_VIDEO || SDL_INIT_AUDIO);
	SDL_VideoInit(NULL);
	TTF_Init();
	IMG_Init(IMG_INIT_PNG);
	windows = SDL_CreateWindow("Battle Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1300, 700, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(windows, -1, SDL_RENDERER_ACCELERATED);

	comic = TTF_OpenFont("Font/comic.ttf", 175);
	if (comic == NULL)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERRR", SDL_GetError(), windows);
	}
}

void Quit()
{
    quitImage();
    quitSound();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(windows);
	renderer = NULL;
	windows = NULL;
	SDL_Quit();
    TTF_CloseFont(comic);
	TTF_Quit();
}

void CreateGame()
{
    drawStartScreen();
    drawMuteButton();
    SnakeA[0].x = Arena.x; SnakeA[0].y = Arena.y;
    for(int i = 1; i < displaySnakeLengthA; i++)
    {
        SnakeA[i].x = Arena.x + size*i;
        SnakeA[i].y = Arena.y;
    }

    SnakeB[0].x = Arena.x + Arena.w - size; SnakeB[0].y = Arena.y + Arena.h - size;
    for(int i = 1; i < displaySnakeLengthB; i++)
    {
        SnakeB[i].x = Arena.x + Arena.w - size*i;
        SnakeB[i].y = Arena.y + Arena.h - size;
    }

    Direct[0].x = 0; Direct[0].y = -size;
    Direct[1].x = size; Direct[1].y = 0;
    Direct[2].x = 0; Direct[2].y = size;
    Direct[3].x = -size; Direct[3].y = 0;

    foodA.x = Arena.x; foodA.y = Arena.y + Arena.h/2 ;
    foodB.x = Arena.x + Arena.w - size; foodB.y = Arena.y + Arena.h/2;
}

void reCreateGame()
{
    CreateGame();
    scoreA = 0; scoreB = 0;
    displaySnakeLengthA = 2; displaySnakeLengthB = 2;
    realSnakeLengthA = 3; realSnakeLengthB = 3;
    restart = false; start = false; pause = false; gameOver = false;
    showHowToPlayScreen = false;
    for(int i =0; i < bombA_num; i++)
    {
        bombAStatus[i] = false;
    }
    for(int i =0; i < bombB_num; i++)
    {
        bombBStatus[i] = false;
    }
    preDirectionA = RIGHT, directionA = LEFT, preDirectionB = LEFT, directionB = RIGHT;
}
