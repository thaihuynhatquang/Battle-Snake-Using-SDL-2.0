#ifndef HANDLEEVENT_H
#define HANDLEEVENT_H

void handleLocationOfMouse(int mouseX, int mouseY);
void handleActionOfMouse(int mouseX, int mouseY);
bool mouseInHowToPlayButton(int mouseX, int mouseY);
bool mouseInStartButton(int mouseX, int mouseY);
bool mouseInMuteButton(int mouseX, int mouseY);
bool mouseInStartButton(int mouseX, int mouseY);
bool mouseInPauseButton(int mouseX, int mouseY);
bool mouseInRestartButton(int mouseX, int mouseY);
bool mouseInExitButton(int mouseX, int mouseY);
void waitEvent(SDL_Event event);

#endif // HANDLEEVENT_H
