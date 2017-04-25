#ifndef RENDERIMAGE_H
#define RENDERIMAGE_H

extern bool gameOver;
extern int Result;
extern TTF_Font* comic;
extern SDL_Window *windows;
extern SDL_Renderer *renderer;
extern SDL_Rect pauseButtonRect;
extern SDL_Rect restartButtonRect;
extern SDL_Rect exitButtonRect;
extern SDL_Rect Rectangle;
extern SDL_Rect Rectangle2;
extern SDL_Rect Rectangle3;

extern bool pause, start;
SDL_Texture* LoadTexture(const std::string &str);
void loadImage();
void loadSnake();
void loadBomb();
void loadFood();
void loadScore();
void drawStartScreen();
void drawHowToPlayScreen();
void loadBackground();
void loadResult();
void loadButton();
void drawStartButton();
void drawStartButtonInHowToPlay();
void drawHowToPlayButton();
void drawButton();
void drawOverButton();
void drawPlayScreen();
void quitImage();

#endif // RENDERIMAGE_H
