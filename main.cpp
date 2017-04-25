#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include "snake.h"
#include "renderSound.h"
#include "renderImage.h"


const int UP = 0, DOWN = 2, LEFT = 3, RIGHT = 1;
int speed = 40, bombA_num = 0, bombB_num = 0, size = 35, Result = 0;
int preDirectionA = RIGHT, directionA = LEFT, preDirectionB = LEFT, directionB = RIGHT;
bool bombAStatus[10000], bombBStatus[10000];
bool running = true, pause = false, gameOver = false, start = false, restart = false, showHowToPlayScreen = false;
SDL_Rect Arena = {352, 29, 630, 630};
SDL_Rect pauseButtonRect = {510, 662, 35, 35};
SDL_Rect restartButtonRect = {650, 662, 35, 35};
SDL_Rect exitButtonRect = {790, 662, 35, 35};
SDL_Rect Rectangle = {522, 418, 300, 110};
SDL_Rect Rectangle2 = {400, 545, 530, 110};
SDL_Rect Rectangle3 = {525, 585, 310, 110};
TTF_Font* comic;
SDL_Window *windows;
SDL_Renderer *renderer;

void mouseEvent();
void checkResult();
void playGame();
void Init();
void loadImage();
void waitEvent();
void CreateGame();
void reCreateGame();
void Quit();

int main(int argc, char* argv[])
{
	Init();
	loadImage();
	loadSound();
	srand(time(NULL));
    CreateGame();
	while (running == true)
	{
        playStartSound();
		waitEvent();
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
                exit(0);
            }
        case SDL_MOUSEMOTION:
            {
                int mouseX = event.motion.x;
                int mouseY = event.motion.y;
                if(start == false && showHowToPlayScreen == false)
                {
                    if((mouseX >= Rectangle.x) && (mouseX <= Rectangle.x + Rectangle.w) && (mouseY >= Rectangle.y) && (mouseY <= Rectangle.y + Rectangle.h))
                    {
                        drawStartButton();
                    }
                    else if((mouseX >= Rectangle2.x) && (mouseX <= Rectangle2.x + Rectangle2.w) && (mouseY >= Rectangle2.y) && (mouseY <= Rectangle2.y + Rectangle2.h) && start == false && showHowToPlayScreen == false)
                    {
                        drawHowToPlayButton();
                    }
                    else drawStartScreen();
                }
                else if(start == false && showHowToPlayScreen == true)
                {
                    if((mouseX >= Rectangle3.x) && (mouseX <= Rectangle3.x + Rectangle3.w) && (mouseY >= Rectangle3.y) && (mouseY <= Rectangle3.y + Rectangle3.h) && start == false && showHowToPlayScreen == true)
                    {
                        drawStartButtonInHowToPlay();
                    }
                    else drawHowToPlayScreen();
                }
                break;
            }
        case SDL_MOUSEBUTTONDOWN:
            {
                int mouseClickX = event.motion.x;
                int mouseClickY = event.motion.y;
                if(start == false && showHowToPlayScreen == false)
                {
                    if((mouseClickX >= Rectangle.x) && (mouseClickX <= Rectangle.x + Rectangle.w) && (mouseClickY >= Rectangle.y) && (mouseClickY <= Rectangle.y + Rectangle.h))
                    {
                        playClickSound();
                        drawStartButton();
                        start = true;
                    }
                    else if((mouseClickX >= Rectangle2.x) && (mouseClickX <= Rectangle2.x + Rectangle2.w) && (mouseClickY >= Rectangle2.y) && (mouseClickY <= Rectangle2.y + Rectangle2.h))
                    {
                        playClickSound();
                        drawHowToPlayScreen();
                        showHowToPlayScreen = true;
                    }
                }
                else if(start == false && showHowToPlayScreen == true)
                {
                    if((mouseClickX >= Rectangle3.x) && (mouseClickX <= Rectangle3.x + Rectangle3.w) && (mouseClickY >= Rectangle3.y) && (mouseClickY <= Rectangle3.y + Rectangle3.h) && start == false && showHowToPlayScreen == true)
                    {
                        playClickSound();
                        drawStartButtonInHowToPlay();
                        start = true;
                        showHowToPlayScreen = false;
                    }
                }
                else if(start == true && showHowToPlayScreen == false)
                {
                    if(mouseClickX >= pauseButtonRect.x && mouseClickX <= pauseButtonRect.x + pauseButtonRect.w && mouseClickY >= pauseButtonRect.y && mouseClickY <= pauseButtonRect.y + pauseButtonRect.h && pause == false && gameOver == false)
                    {
                        playClickSound();
                        pause = true;
                    }
                    else if(mouseClickX >= pauseButtonRect.x && mouseClickX <= pauseButtonRect.x + pauseButtonRect.w && mouseClickY >= pauseButtonRect.y && mouseClickY <= pauseButtonRect.y + pauseButtonRect.h && pause == true && gameOver == false)
                    {
                        playClickSound();
                        pause = false;
                    }
                    else if(mouseClickX >= restartButtonRect.x && mouseClickX <= restartButtonRect.x + restartButtonRect.w && mouseClickY >= restartButtonRect.y && mouseClickY <= restartButtonRect.y + restartButtonRect.h && start == true)
                    {
                        playClickSound();
                        restart = true;
                    }
                    else if(mouseClickX >= exitButtonRect.x && mouseClickX <= exitButtonRect.x + exitButtonRect.w && mouseClickY >= exitButtonRect.y && mouseClickY <= exitButtonRect.y + exitButtonRect.h && start == true)
                    {
                        playClickSound();
                        Quit();
                        exit(0);
                    }
                }
                break;
            }
		case SDL_KEYDOWN:
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    {
                        Quit();
                        exit(0);
                    }
                case SDLK_p:
                    {
                        if(pause == true)
                            pause = false;
                        else pause = true;
                        break;
                    }
                case SDLK_r:
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

void CreateGame()
{
    drawStartScreen();
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
    showHowToPlayScreen == false;
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
