#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

#define SCREEN_W 800
#define SCREEN_H 600

void init_window(SDL_Window **window, SDL_Renderer **renderer);
void destroy_window(SDL_Window *window, SDL_Renderer *renderer);

#endif