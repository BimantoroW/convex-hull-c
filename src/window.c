#include <SDL2/SDL.h>
#include <stdio.h>
#include <unistd.h>
#include "window.h"

void err_and_exit(char *func) {
    fprintf(stderr, "%s error: %s\n", func, SDL_GetError());
    exit(EXIT_FAILURE);
}

void init_window(SDL_Window **window, SDL_Renderer **renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        err_and_exit("SDL_Init");
    }

    *window = SDL_CreateWindow(
        "Convex Hull",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_W,
        SCREEN_H,
        0
    );
    if (!(*window)) {
        err_and_exit("SDL_CreateWindow");
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (!(*renderer)) {
        err_and_exit("SDL_CreateRenderer");
    }
}

void destroy_window(SDL_Window *window, SDL_Renderer *renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}