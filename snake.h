#ifndef SNAKE_H
#define SNAKE_H

extern int size;
struct positition
{
    int x,y;
    int x0, y0;
    const int width = size;
    const int height = size;
};
extern const int UP, DOWN, LEFT, RIGHT;
extern int speed, bombA_num, bombB_num, scoreA, scoreB;
extern int displaySnakeLengthA, realSnakeLengthA, displaySnakeLengthB, realSnakeLengthB;
extern int preDirectionA, directionA, preDirectionB, directionB;
extern bool bombAStatus[10000], bombBStatus[10000];
extern SDL_Rect Arena;
extern positition SnakeA[10000], SnakeB[10000], foodA, foodB, Direct[4];
extern SDL_Rect bombRectA[10000];
extern SDL_Rect bombRectB[10000];
void snakeMove(int dir, positition Snake[], int realSnakeLength);
void moveA();
void moveB();
void eatBomb();
void increaseSnakeA(int n);
void increaseSnakeB(int n);
void decreaseSnakeA(int n);
void decreaseSnakeB(int n);
void eatFoodA();
void eatFoodB();
void dropBombA();
void dropBombB();
void throughBomb();

#endif // SNAKE_H
