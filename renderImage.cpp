#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <sstream>
#include "snake.h"
#include "renderImage.h"

positition SnakeA[10000], SnakeB[10000], foodA, foodB, Direct[4];

SDL_Texture* Head_Snake_A[4]; SDL_Texture* Head_Snake_B[4];
SDL_Texture* Tail_Snake_A[4]; SDL_Texture* Tail_Snake_B[4];
SDL_Texture* Body_Snake_A;  SDL_Texture* Body_Snake_B;
SDL_Texture* Bomb_A; SDL_Texture* Bomb_B;
SDL_Texture* Food;
SDL_Texture* result_text;
SDL_Texture* Background; SDL_Texture* StartScreen; SDL_Texture* PlayScreen; SDL_Texture* HowToPlayScreen;
SDL_Texture* Win; SDL_Texture* Lose;
SDL_Texture* pauseButton;
SDL_Texture* playButton;
SDL_Texture* startButton;
SDL_Texture* howToPlayButton;
SDL_Texture* restartButton;
SDL_Texture* exitButton;

SDL_Rect snakeRectA[100]; SDL_Rect snakeRectB[100];
SDL_Rect bombRectA[10000]; SDL_Rect bombRectB[10000];
SDL_Rect foodRectA; SDL_Rect foodRectB;
SDL_Rect Screen_rect = {0,0,1300,700};
SDL_Rect ResultA = {25, 580, 300, 120};
SDL_Rect ResultB = {990, 580, 300, 120};

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
    Head_Snake_A[0] = LoadTexture("Image/Snake/Head/UpA.png");
    Head_Snake_A[1] = LoadTexture("Image/Snake/Head/DownA.png");
    Head_Snake_A[2] = LoadTexture("Image/Snake/Head/LeftA.png");
    Head_Snake_A[3] = LoadTexture("Image/Snake/Head/RightA.png");
    Head_Snake_B[0] = LoadTexture("Image/Snake/Head/UpB.png");
    Head_Snake_B[1] = LoadTexture("Image/Snake/Head/DownB.png");
    Head_Snake_B[2] = LoadTexture("Image/Snake/Head/LeftB.png");
    Head_Snake_B[3] = LoadTexture("Image/Snake/Head/RightB.png");

    Body_Snake_A = LoadTexture("Image/Snake/Body/BodyA.png");
    Body_Snake_B = LoadTexture("Image/Snake/Body/BodyB.png");

    Tail_Snake_A[0] = LoadTexture("Image/Snake/Tail/UpA.png");
    Tail_Snake_A[1] = LoadTexture("Image/Snake/Tail/DownA.png");
    Tail_Snake_A[2] = LoadTexture("Image/Snake/Tail/LeftA.png");
    Tail_Snake_A[3] = LoadTexture("Image/Snake/Tail/RightA.png");
    Tail_Snake_B[0] = LoadTexture("Image/Snake/Tail/UpB.png");
    Tail_Snake_B[1] = LoadTexture("Image/Snake/Tail/DownB.png");
    Tail_Snake_B[2] = LoadTexture("Image/Snake/Tail/LeftB.png");
    Tail_Snake_B[3] = LoadTexture("Image/Snake/Tail/RightB.png");
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
    SDL_Rect ScoreRectA = {1050, 300, 200, 350};
    SDL_Rect ScoreRectB = {75, 300, 200, 350};
    result_text = SDL_CreateTextureFromSurface(renderer, ScoreSurA);
    SDL_RenderCopy(renderer, result_text, NULL, &ScoreRectA);
    result_text = SDL_CreateTextureFromSurface(renderer, ScoreSurB);
    SDL_RenderCopy(renderer, result_text, NULL, &ScoreRectB);
}

void loadBackground()
{
    PlayScreen = LoadTexture("Image/Background/PlayScreen.png");
    HowToPlayScreen = LoadTexture("Image/Background/HowToPlayScreen.png");
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
    howToPlayButton = LoadTexture("Image/Rectangle2.png");
    restartButton = LoadTexture("Image/Button/restart.png");
    exitButton = LoadTexture("Image/Button/exit.png");
}

void drawStartScreen()
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, StartScreen, NULL, &Screen_rect);
    SDL_RenderPresent(renderer);
}

void drawHowToPlayScreen()
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, HowToPlayScreen, NULL, &Screen_rect);
    SDL_RenderPresent(renderer);
}

void drawStartButton()
{
    SDL_RenderCopy(renderer, startButton, NULL, &Rectangle);
    SDL_RenderPresent(renderer);
}

void drawStartButtonInHowToPlay()
{
    SDL_RenderCopy(renderer, startButton, NULL, &Rectangle3);
    SDL_RenderPresent(renderer);
}

void drawHowToPlayButton()
{
    SDL_RenderCopy(renderer, startButton, NULL, &Rectangle2);
    SDL_RenderPresent(renderer);
}

void drawButton()
{
    if(start == false) SDL_Delay(1000);
    if(pause == false) SDL_RenderCopy(renderer, pauseButton, NULL, &pauseButtonRect);
    else if(pause == true) SDL_RenderCopy(renderer, playButton, NULL, &pauseButtonRect);
    SDL_RenderCopy(renderer, restartButton, NULL, &restartButtonRect);
    SDL_RenderCopy(renderer, exitButton, NULL, &exitButtonRect);
    SDL_RenderPresent(renderer);
}

void drawPlayScreen()
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, PlayScreen, NULL, &Screen_rect);
    loadScore();

    //DRAW SNAKE
    for (int i = displaySnakeLengthA - 1; i >= 0; i--)
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
            if(directionA == UP) SDL_RenderCopy(renderer, Head_Snake_A[0], NULL, &snakeRectA[i]);
            if(directionA == DOWN) SDL_RenderCopy(renderer, Head_Snake_A[1], NULL, &snakeRectA[i]);
            if(directionA == LEFT) SDL_RenderCopy(renderer, Head_Snake_A[2], NULL, &snakeRectA[i]);
            if(directionA == RIGHT) SDL_RenderCopy(renderer, Head_Snake_A[3], NULL, &snakeRectA[i]);
        }
        else
        {
            if(directionA == UP) SDL_RenderCopy(renderer, Tail_Snake_A[0], NULL, &snakeRectA[i]);
            if(directionA == DOWN) SDL_RenderCopy(renderer, Tail_Snake_A[1], NULL, &snakeRectA[i]);
            if(directionA == LEFT) SDL_RenderCopy(renderer, Tail_Snake_A[2], NULL, &snakeRectA[i]);
            if(directionA == RIGHT) SDL_RenderCopy(renderer, Tail_Snake_A[3], NULL, &snakeRectA[i]);
        }
    }
    for (int i = displaySnakeLengthB - 1; i >= 0; i--)
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
            if(directionB == UP) SDL_RenderCopy(renderer, Head_Snake_B[0], NULL, &snakeRectB[i]);
            if(directionB == DOWN) SDL_RenderCopy(renderer, Head_Snake_B[1], NULL, &snakeRectB[i]);
            if(directionB == LEFT) SDL_RenderCopy(renderer, Head_Snake_B[2], NULL, &snakeRectB[i]);
            if(directionB == RIGHT) SDL_RenderCopy(renderer, Head_Snake_B[3], NULL, &snakeRectB[i]);
        }
        else
        {
            if(directionB == UP) SDL_RenderCopy(renderer, Tail_Snake_B[0], NULL, &snakeRectB[i]);
            if(directionB == DOWN) SDL_RenderCopy(renderer, Tail_Snake_B[1], NULL, &snakeRectB[i]);
            if(directionB == LEFT) SDL_RenderCopy(renderer, Tail_Snake_B[2], NULL, &snakeRectB[i]);
            if(directionB == RIGHT) SDL_RenderCopy(renderer, Tail_Snake_B[3], NULL, &snakeRectB[i]);
        }
    }

    //DRAW FOOD
    foodRectA.x = foodA.x; foodRectA.y = foodA.y; foodRectA.h = foodA.height; foodRectA.w = foodA.width;
    SDL_RenderCopy(renderer, Food, NULL, &foodRectA);
    foodRectB.x = foodB.x; foodRectB.y = foodB.y; foodRectB.h = foodB.height; foodRectB.w = foodB.width;
    SDL_RenderCopy(renderer, Food, NULL, &foodRectB);

    //DRAW BOMB
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

    //DRAW RESULT
    if(gameOver == true)
    {
        if(Result == -1)
        {
            SDL_RenderCopy(renderer, Lose, NULL, &ResultA);
            SDL_RenderCopy(renderer, Win, NULL, &ResultB);
        }
        else
        {
            SDL_RenderCopy(renderer, Lose, NULL, &ResultB);
            SDL_RenderCopy(renderer, Win, NULL, &ResultA);
        }
    }
    SDL_RenderPresent(renderer);
}


void loadImage()
{
    loadBackground();
    loadSnake();
    loadBomb();
    loadFood();
    loadResult();
    loadButton();
}

void quitImage()
{
    SDL_DestroyTexture(Head_Snake_A[4]);
    SDL_DestroyTexture(Head_Snake_B[4]);
    SDL_DestroyTexture(Tail_Snake_A[4]);
    SDL_DestroyTexture(Tail_Snake_B[4]);
    SDL_DestroyTexture(Body_Snake_A);
    SDL_DestroyTexture(Body_Snake_B);
    SDL_DestroyTexture(Bomb_A);
    SDL_DestroyTexture(Bomb_B);
    SDL_DestroyTexture(Food);
    SDL_DestroyTexture(result_text);
    SDL_DestroyTexture(Background);
    SDL_DestroyTexture(StartScreen);
    SDL_DestroyTexture(PlayScreen);
    SDL_DestroyTexture(HowToPlayScreen);
    SDL_DestroyTexture(Win);
    SDL_DestroyTexture(Lose);
    SDL_DestroyTexture(pauseButton);
    SDL_DestroyTexture(playButton);
    SDL_DestroyTexture(startButton);
    SDL_DestroyTexture(howToPlayButton);
    SDL_DestroyTexture(restartButton);
    SDL_DestroyTexture(exitButton);
    IMG_Quit();
}
