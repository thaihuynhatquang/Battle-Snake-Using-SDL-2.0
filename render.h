#ifndef RENDER_H
#define RENDER_H

extern bool gameOver;
extern int Result;
extern TTF_Font* comic;
extern SDL_Window *windows;
extern SDL_Renderer *renderer;
extern SDL_Rect ButtonRect;
extern SDL_Rect Rectangle;
extern bool pause, start;
SDL_Texture* LoadTexture(const std::string &str);
void loadSnake();
void loadBomb();
void loadFood();
void loadScore();
void drawStartScreen();
void loadBackground();
void loadResult();
void loadButton();
void drawStartButton();
void drawButton();
void drawPlayScreen();
#endif // RENDER_H
