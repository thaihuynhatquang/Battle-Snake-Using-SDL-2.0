#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <stdlib.h>
#include "renderImage.h"
#include "renderSound.h"
#include "handleEvent.h"
#include "controlGame.h"

SDL_Rect pauseButtonRect = {510, 662, 35, 35};
SDL_Rect restartButtonRect = {650, 662, 35, 35};
SDL_Rect muteButtonRect = {1170, 30, 110, 110};
SDL_Rect exitButtonRect = {790, 662, 35, 35};
SDL_Rect Rectangle = {522, 418, 300, 110};
SDL_Rect Rectangle2 = {400, 545, 530, 110};
SDL_Rect Rectangle3 = {525, 585, 310, 110};
extern bool start, showHowToPlayScreen, restart;

void waitEvent(SDL_Event event)
{
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
                handleLocationOfMouse(event.motion.x, event.motion.y);
                break;
            }
        case SDL_MOUSEBUTTONDOWN:
            {
                handleActionOfMouse(event.motion.x, event.motion.y);
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

void handleLocationOfMouse(int mouseX, int mouseY)
{
    if(start == false && showHowToPlayScreen == false)
    {
        if(mouseInStartButton(mouseX, mouseY) == true)
            drawStartButton();
        else if (mouseInHowToPlayButton(mouseX, mouseY) == true && start == false && showHowToPlayScreen == false)
            drawHowToPlayButton();
        else drawStartScreen();
    }

    else if(start == false && showHowToPlayScreen == true)
    {
        if(mouseInStartButton(mouseX, mouseY) == true)
            drawStartButtonInHowToPlay();
        else drawHowToPlayScreen();
    }
}

void handleActionOfMouse(int mouseX, int mouseY)
{
    if(start == false && showHowToPlayScreen == false)
    {
        if(mouseInStartButton(mouseX, mouseY) == true)
        {
            playClickSound();
            drawStartButton();
            start = true;
        }
        else if(mouseInHowToPlayButton(mouseX, mouseY) == true)
        {
            playClickSound();
            drawHowToPlayScreen();
            showHowToPlayScreen = true;
        }
        else if(mouseInMuteButton(mouseX, mouseY) == true)
        {
            playClickSound();
            if(mute == false)
            {
                mute = true;
                Mix_PauseMusic();
            }
            else
            {
                mute = false;
                Mix_ResumeMusic();
            }
            drawStartScreen();
        }
    }

    else if(start == false && showHowToPlayScreen == true)
    {
        if(mouseInStartButton(mouseX, mouseY) == true)
        {
            playClickSound();
            drawStartButtonInHowToPlay();
            start = true;
            showHowToPlayScreen = false;
        }
    }

    else if(start == true && showHowToPlayScreen == false)
    {
        if(mouseInPauseButton(mouseX, mouseY) == true && pause == false && gameOver == false)
        {
            playClickSound();
            pause = true;
        }
        else if(mouseInPauseButton(mouseX, mouseY) == true && pause == true && gameOver == false)
        {
            playClickSound();
            pause = false;
        }
        else if(mouseInRestartButton(mouseX, mouseY) == true && start == true)
        {
            playClickSound();
            restart = true;
        }
        else if(mouseInExitButton(mouseX, mouseY) == true && start == true)
        {
            playClickSound();
            Quit();
            exit(0);
        }
    }
}

bool mouseInStartButton(int mouseX, int mouseY)
{
    if((mouseX >= Rectangle.x) && (mouseX <= Rectangle.x + Rectangle.w) && (mouseY >= Rectangle.y) && (mouseY <= Rectangle.y + Rectangle.h))
        return true;
    else if((mouseX >= Rectangle3.x) && (mouseX <= Rectangle3.x + Rectangle3.w) && (mouseY >= Rectangle3.y) && (mouseY <= Rectangle3.y + Rectangle3.h) && start == false && showHowToPlayScreen == true)
        return true;
    else return false;
}

bool mouseInHowToPlayButton(int mouseX, int mouseY)
{
     if((mouseX >= Rectangle2.x) && (mouseX <= Rectangle2.x + Rectangle2.w) && (mouseY >= Rectangle2.y) && (mouseY <= Rectangle2.y + Rectangle2.h))
        return true;
     else return false;
}

bool mouseInMuteButton(int mouseX, int mouseY)
{
    if((mouseX >= muteButtonRect.x) && (mouseX <= muteButtonRect.x + muteButtonRect.w) &&
       (mouseY >= muteButtonRect.y) && (mouseY <= muteButtonRect.y + muteButtonRect.h))
        return true;
    else return false;
}

bool mouseInPauseButton(int mouseX, int mouseY)
{
    if(mouseX >= pauseButtonRect.x && mouseX <= pauseButtonRect.x + pauseButtonRect.w &&
       mouseY >= pauseButtonRect.y && mouseY <= pauseButtonRect.y + pauseButtonRect.h)
        return true;
    else return false;
}

bool mouseInRestartButton(int mouseX, int mouseY)
{
    if(mouseX >= restartButtonRect.x && mouseX <= restartButtonRect.x + restartButtonRect.w &&
       mouseY >= restartButtonRect.y && mouseY <= restartButtonRect.y + restartButtonRect.h)
        return true;
    else return false;
}

bool mouseInExitButton(int mouseX, int mouseY)
{
    if(mouseX >= exitButtonRect.x && mouseX <= exitButtonRect.x + exitButtonRect.w &&
       mouseY >= exitButtonRect.y && mouseY <= exitButtonRect.y + exitButtonRect.h)
        return true;
    else return false;
}

