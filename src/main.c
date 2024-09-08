#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include "convex_hull.h"
#include "fast_convex_hull.h"
#include "window.h"
#include "point.h"

#define N_POINT 20
#define POINT_SIZE 4
#define TEXTURE_W 800
#define TEXTURE_H 600

typedef struct color {
    uint8_t r, g, b;
} color_t;

void render_texture(SDL_Renderer *renderer, SDL_Texture *texture, point_t *points, point_t *ch, int n_ch, color_t color) {
    SDL_SetRenderTarget(renderer, texture);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 0; i < N_POINT; i++) {
        SDL_FRect rect = {
            points[i].x - POINT_SIZE / 2.0f,
            points[i].y - POINT_SIZE / 2.0f,
            POINT_SIZE,
            POINT_SIZE
        };
        SDL_RenderFillRectF(renderer, &rect);
    }

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
    SDL_RenderDrawLinesF(renderer, (SDL_FPoint *)ch, n_ch);
}

void render(SDL_Renderer *renderer, SDL_Texture *texture) {
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

int main(void) {
    srand(time(NULL));

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    int quit = 0;

    init_window(&window, &renderer);

    SDL_Texture *points_texture = SDL_CreateTexture(
        renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, TEXTURE_W, TEXTURE_H
    );

    point_t *points = point_rand(N_POINT, TEXTURE_W, TEXTURE_H);
    int n_ch = 0;
    // point_t *ch = convex_hull(points, N_POINT, &n_ch);
    point_t *ch = fast_convex_hull(points, N_POINT, &n_ch);
    color_t color = {0, 255, 0};

    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = 1;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            quit = 1;
                            break;
                        case SDLK_SPACE:
                            points = point_rand(N_POINT, TEXTURE_W, TEXTURE_H);
                            // ch = convex_hull(points, N_POINT, &n_ch);
                            ch = fast_convex_hull(points, N_POINT, &n_ch);
                            color = (color_t){rand() % 256, rand() % 256, rand() % 256};
                            break;
                    }
                    break;
            }
        }
        render_texture(renderer, points_texture, points, ch, n_ch, color);
        render(renderer, points_texture);
    }

    free(points);
    free(ch);
    destroy_window(window, renderer);
    SDL_DestroyTexture(points_texture);
    return EXIT_SUCCESS;
}