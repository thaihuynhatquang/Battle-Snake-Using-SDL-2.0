#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <sstream>
#include "snake.h"
#include "render.h"

SDL_Texture* Head_Snake_A_Up; SDL_Texture* Head_Snake_A_Down; SDL_Texture* Head_Snake_A_Left; SDL_Texture* Head_Snake_A_Right;
SDL_Texture* Head_Snake_B_Up; SDL_Texture* Head_Snake_B_Down; SDL_Texture* Head_Snake_B_Left; SDL_Texture* Head_Snake_B_Right;

SDL_Texture* Tail_Snake_A_Up; SDL_Texture* Tail_Snake_A_Down; SDL_Texture* Tail_Snake_A_Left; SDL_Texture* Tail_Snake_A_Right;
SDL_Texture* Tail_Snake_B_Up; SDL_Texture* Tail_Snake_B_Down; SDL_Texture* Tail_Snake_B_Left; SDL_Texture* Tail_Snake_B_Right;

SDL_Texture* Body_Snake_A; SDL_Texture* Body_Snake_B;
SDL_Texture* Bomb_A; SDL_Texture* Bomb_B; SDL_Texture* Food;
SDL_Texture* result_text;
SDL_Texture* Background; SDL_Texture* StartScreen; SDL_Texture* PlayScreen;
SDL_Texture* Win; SDL_Texture* Lose;
SDL_Texture* pauseButton;
SDL_Texture* playButton;
SDL_Texture* startButton;
SDL_Texture* restartButton;

SDL_Rect snakeRectA[100]; SDL_Rect snakeRectB[100];
SDL_Rect bombRectA[10000]; SDL_Rect bombRectB[10000];
SDL_Rect foodRectA; SDL_Rect foodRectB;

SDL_Rect Screen_rect = {0,0,1300,700};
SDL_Rect ResultA = {25, 540, 300, 120};
SDL_Rect ResultB = {990, 540, 300, 120};

positition SnakeA[10000], SnakeB[10000], foodA, foodB, Direct[4];
int scoreA = 0, scoreB = 0, displaySnakeLengthA = 2, displaySnakeLengthB = 2, realSnakeLengthB = 2, realSnakeLengthA = 2;

SDL_Texture* LoadTexture(const std::string &str)
{
	SDL_Surface* surface = IMG_Load(str.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}

void loadSnake()
{
    Head_Snake_A_Up = LoadTexture("Image/Snake/Head/UpA.png");
    Head_Snake_A_Down = LoadTexture("Image/Snake/Head/DownA.png");
    Head_Snake_A_Left = LoadTexture("Image/Snake/Head/LeftA.png");
    Head_Snake_A_Right = LoadTexture("Image/Snake/Head/RightA.png");
    Head_Snake_B_Up = LoadTexture("Image/Snake/Head/UpB.png");
    Head_Snake_B_Down = LoadTexture("Image/Snake/Head/DownB.png");
    Head_Snake_B_Left = LoadTexture("Image/Snake/Head/LeftB.png");
    Head_Snake_B_Right = LoadTexture("Image/Snake/Head/RightB.png");

    Body_Snake_A = LoadTexture("Image/Snake/Body/BodyA.png");
    Body_Snake_B = LoadTexture("Image/Snake/Body/BodyB.png");

    Tail_Snake_A_Up = LoadTexture("Image/Snake/Tail/UpA.png");
    Tail_Snake_A_Down = LoadTexture("Image/Snake/Tail/DownA.png");
    Tail_Snake_A_Left = LoadTexture("Image/Snake/Tail/LeftA.png");
    Tail_Snake_A_Right = LoadTexture("Image/Snake/Tail/RightA.png");
    Tail_Snake_B_Up = LoadTexture("Image/Snake/Tail/UpB.png");
    Tail_Snake_B_Down = LoadTexture("Image/Snake/Tail/DownB.png");
    Tail_Snake_B_Left = LoadTexture("Image/Snake/Tail/LeftB.png");
    Tail_Snake_B_Right = LoadTexture("Image/Snake/Tail/RightB.png");
}

void loadBomb()
{
    Bomb_A = LoadTexture("Image/Bomb/1.png");
    Bomb_B = LoadTexture("Image/Bomb/2.png");
}

void loadFood()
{
    Food = LoadTexture("Image/Food/food.png");
}

void loadScore()
{
    std::stringstream score1, score2;
    score1 << scoreA;
    std::string strA = score1.str();
    score2 << scoreB;
    std::string strB = score2.str();
    SDL_Color WHITE = {255,255,255};
    SDL_Surface* ScoreSurA = TTF_RenderText_Solid(comic, strA.c_str(), WHITE);
    SDL_Surface* ScoreSurB = TTF_RenderText_Solid(comic, strB.c_str(), WHITE);
    SDL_Rect ScoreRectA = {75, 270, 200, 350};
    SDL_Rect ScoreRectB = {1050, 270, 200, 350};
    result_text = SDL_CreateTextureFromSurface(renderer, ScoreSurA);
    SDL_RenderCopy(renderer, result_text, NULL, &ScoreRectA);
    result_text = SDL_CreateTextureFromSurface(renderer, ScoreSurB);
    SDL_RenderCopy(renderer, result_text, NULL, &ScoreRectB);
}

void drawStartScreen()
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, StartScreen, NULL, &Screen_rect);
    SDL_RenderPresent(renderer);
}

void loadBackground()
{
    PlayScreen = LoadTexture("Image/Background/PlayScreen.png");
    StartScreen = LoadTexture("Image/Background/StartScreen.png");
}

void loadResult()
{
    Win = LoadTexture("Image/Result/Win.png");
    Lose = LoadTexture("Image/Result/Lose.png");
}

void loadButton()
{
    pauseButton = LoadTexture("Image/Button/pause.png");
    playButton = LoadTexture("Image/Button/play.png");
    startButton = LoadTexture("Image/Rectangle.png");
    restartButton = LoadTexture("Image/Button/restart.png");
}

void drawStartButton()
{
    SDL_RenderCopy(renderer, startButton, NULL, &Rectangle);
    SDL_RenderPresent(renderer);
}

void drawButton()
{
    if(start == false) SDL_Delay(1000);
    if(pause == false && gameOver == false) SDL_RenderCopy(renderer, pauseButton, NULL, &ButtonRect);
    else if(pause == true && gameOver == false) SDL_RenderCopy(renderer, playButton, NULL, &ButtonRect);
    else SDL_RenderCopy(renderer, restartButton, NULL, &ButtonRect);
    SDL_RenderPresent(renderer);
}

void drawPlayScreen()
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, PlayScreen, NULL, &Screen_rect);
    loadScore();

    for (int i = 0; i < displaySnakeLengthA; ++i)
    {
        snakeRectA[i].x = SnakeA[i].x;
        snakeRectA[i].y = SnakeA[i].y;
        snakeRectA[i].w = SnakeA[i].width;
        snakeRectA[i].h = SnakeA[i].height;
        if (i != 0 && i != displaySnakeLengthA - 1)
        {
            SDL_RenderCopy(renderer, Body_Snake_A, NULL, &snakeRectA[i]);
        }
        else if(i == 0)
        {
            if(directionA == UP) SDL_RenderCopy(renderer, Head_Snake_A_Up, NULL, &snakeRectA[i]);
            if(directionA == DOWN) SDL_RenderCopy(renderer, Head_Snake_A_Down, NULL, &snakeRectA[i]);
            if(directionA == LEFT) SDL_RenderCopy(renderer, Head_Snake_A_Left, NULL, &snakeRectA[i]);
            if(directionA == RIGHT) SDL_RenderCopy(renderer, Head_Snake_A_Right, NULL, &snakeRectA[i]);
        }
        else
        {
            if(directionA == UP) SDL_RenderCopy(renderer, Tail_Snake_A_Up, NULL, &snakeRectA[i]);
            if(directionA == DOWN) SDL_RenderCopy(renderer, Tail_Snake_A_Down, NULL, &snakeRectA[i]);
            if(directionA == LEFT) SDL_RenderCopy(renderer, Tail_Snake_A_Left, NULL, &snakeRectA[i]);
            if(directionA == RIGHT) SDL_RenderCopy(renderer, Tail_Snake_A_Right, NULL, &snakeRectA[i]);
        }
    }

    for (int i = 0; i < displaySnakeLengthB; ++i)
    {
        snakeRectB[i].x = SnakeB[i].x;
        snakeRectB[i].y = SnakeB[i].y;
        snakeRectB[i].w = SnakeB[i].width;
        snakeRectB[i].h = SnakeB[i].height;
        if (i != 0 && i != displaySnakeLengthB - 1)
        {
            SDL_RenderCopy(renderer, Body_Snake_B, NULL, &snakeRectB[i]);
        }
        else if(i == 0)
        {
            if(directionB == UP) SDL_RenderCopy(renderer, Head_Snake_B_Up, NULL, &snakeRectB[i]);
            if(directionB == DOWN) SDL_RenderCopy(renderer, Head_Snake_B_Down, NULL, &snakeRectB[i]);
            if(directionB == LEFT) SDL_RenderCopy(renderer, Head_Snake_B_Left, NULL, &snakeRectB[i]);
            if(directionB == RIGHT) SDL_RenderCopy(renderer, Head_Snake_B_Right, NULL, &snakeRectB[i]);
        }
        else
        {
            if(directionB == UP) SDL_RenderCopy(renderer, Tail_Snake_B_Up, NULL, &snakeRectB[i]);
            if(directionB == DOWN) SDL_RenderCopy(renderer, Tail_Snake_B_Down, NULL, &snakeRectB[i]);
            if(directionB == LEFT) SDL_RenderCopy(renderer, Tail_Snake_B_Left, NULL, &snakeRectB[i]);
            if(directionB == RIGHT) SDL_RenderCopy(renderer, Tail_Snake_B_Right, NULL, &snakeRectB[i]);
        }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        foodRectA.x = foodA.x; foodRectA.y = foodA.y; foodRectA.h = foodA.height; foodRectA.w = foodA.width;
            SDL_RenderCopy(renderer, Food, NULL, &foodRectA);
        foodRectB.x = foodB.x; foodRectB.y = foodB.y; foodRectB.h = foodB.height; foodRectB.w = foodB.width;
            SDL_RenderCopy(renderer, Food, NULL, &foodRectB);

    for(int i = 0; i < bombA_num; i++)
    {
        if(bombAStatus[i] == true)
        {
            SDL_RenderCopy(renderer, Bomb_A, NULL, &bombRectA[i]);
        }
    }

    for(int i = 0; i < bombB_num; i++)
    {
        if(bombBStatus[i] == true)
        {
            SDL_RenderCopy(renderer, Bomb_B, NULL, &bombRectB[i]);
        }
    }

    if(gameOver == true)
    {
        if(Result == -1)
        {
            SDL_RenderCopy(renderer, Win, NULL, &ResultA);
            SDL_RenderCopy(renderer, Lose, NULL, &ResultB);
        }
        else
        {
            SDL_RenderCopy(renderer, Win, NULL, &ResultB);
            SDL_RenderCopy(renderer, Lose, NULL, &ResultA);
        }
    }

    SDL_RenderPresent(renderer);
}
