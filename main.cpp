#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include "snake.h"
#include "render.h"

const int UP = 0, DOWN = 2, LEFT = 3, RIGHT = 1;
int speed = 35, bombA_num = 0, bombB_num = 0, size = 35, Result = 0;
int preDirectionA = RIGHT, directionA = LEFT, preDirectionB = LEFT, directionB = RIGHT;
bool bombAStatus[10000], bombBStatus[10000];
bool running = true, pause = false, gameOver = false, start = false, restart = false;
SDL_Rect Arena = {352, 29, 630, 630};
SDL_Rect ButtonRect = {649.5, 662, 35, 35};
SDL_Rect Rectangle = {518, 520, 300, 110};
TTF_Font* comic;
SDL_Window *windows;
SDL_Renderer *renderer;

void mouseEvent();
void checkResult();
void logic();
void Init();
void waitEvent();
void CreateGame();
void reCreateGame();
void Quit();

int main(int argc, char* argv[])
{
	Init();
	srand(time(NULL));
    CreateGame();
	while (running == true)
	{
		waitEvent();
        if(start == true) drawButton();
        if(pause == false && gameOver == false && start == true)
        {
            logic();
        }
        if(restart == true)
        {
            reCreateGame();
            restart = false;
        }
	}
    return 0;
}

void waitEvent()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_QUIT:
            {
                Quit();
                break;
            }
        case SDL_MOUSEMOTION:
            {
                int mouseX = event.motion.x;
                int mouseY = event.motion.y;
                //std::cout << mouseX << "\t" << mouseY << std::endl;
                if((mouseX >= Rectangle.x) && (mouseX <= Rectangle.x + Rectangle.w) && (mouseY >= Rectangle.y) && (mouseY <= Rectangle.y + Rectangle.h) && start == false)
                {
                    drawStartButton();
                }

                break;
            }
        case SDL_MOUSEBUTTONDOWN:
            {
                switch(event.button.button)
                {
                case SDL_BUTTON_LEFT:
                    {
                        int mouseClickX = event.motion.x;
                        int mouseClickY = event.motion.y;
                        if((mouseClickX >= Rectangle.x) && (mouseClickX <= Rectangle.x + Rectangle.w) && (mouseClickY >= Rectangle.y) && (mouseClickY <= Rectangle.y + Rectangle.h) && start == false)
                        {
                            drawStartButton();
                            start = true;
                        }
                        else if(mouseClickX >= ButtonRect.x && mouseClickX <= ButtonRect.x + ButtonRect.w && mouseClickY >= ButtonRect.y && mouseClickY <= ButtonRect.y + ButtonRect.h && pause == false && gameOver == false)
                        {
                            pause = true;
                        }
                        else if(mouseClickX >= ButtonRect.x && mouseClickX <= ButtonRect.x + ButtonRect.w && mouseClickY >= ButtonRect.y && mouseClickY <= ButtonRect.y + ButtonRect.h && pause == true && gameOver == false)
                        {
                            pause = false;
                        }
                        else if(mouseClickX >= ButtonRect.x && mouseClickX <= ButtonRect.x + ButtonRect.w && mouseClickY >= ButtonRect.y && mouseClickY <= ButtonRect.y + ButtonRect.h && gameOver == true)
                        {
                            restart = true;
                        }
                        break;
                    }
                default:
                    break;
                }
            }
		case SDL_KEYDOWN:
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    {
                        Quit();
                        break;
                    }
                case SDLK_p:
                    {
                        pause = true;
                        break;
                    }
                case SDLK_r:
                    {
                        pause = false;
                        break;
                    }
                case SDLK_m:
                    {
                        restart = true;
                        break;
                    }
                default:
                    break;
                }
            }
        default:
            break;
        }
        break;
    }
}

void checkResult()
{
    if(scoreA == 50)
    {
        Result = -1;
        gameOver = true;
        return;
    }
    if(scoreB == 50)
    {
        Result = 1;
        gameOver = true;
        return;
    }
    if(displaySnakeLengthA < 2)
    {
        Result = 1;
        gameOver = true;
        return;
    }
    if(displaySnakeLengthB < 2)
    {
        Result  = -1;
        gameOver = true;
        return;
    }
    gameOver = false;
}

void logic()
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

void Init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
	SDL_VideoInit(NULL);
	TTF_Init();
	IMG_Init(IMG_INIT_PNG);
	windows = SDL_CreateWindow("Battle Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1300, 700, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(windows, -1, SDL_RENDERER_ACCELERATED);

	comic = TTF_OpenFont("Font/comic.ttf", 75);
	if (comic == NULL)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERRR", SDL_GetError(), windows);
	}
}

void CreateGame()
{
    loadBackground();
	loadSnake();
    loadBomb();
    loadFood();
    drawStartScreen();
    loadResult();
    loadButton();
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
    scoreA = 0;
    scoreB = 0;
    displaySnakeLengthA = 2; displaySnakeLengthB = 2;
    realSnakeLengthA = 3; realSnakeLengthB = 3;
    restart = false;
    start = false;
    pause = false;
    gameOver = false;
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

void Quit()
{
    TTF_CloseFont(comic);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(windows);
	renderer = NULL;
	windows = NULL;
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
}
