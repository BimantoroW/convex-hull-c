#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include "convex_hull.h"
#include "fast_convex_hull.h"
#include "window.h"
#include "point.h"
#include "point_renderer.h"

#define N_POINT 30

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

    SDL_Texture *points_texture = create_texture(renderer);

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
        render_texture(renderer, points_texture, points, N_POINT, ch, n_ch, color);
        render(renderer, points_texture);
    }

    free(points);
    free(ch);
    destroy_window(window, renderer);
    SDL_DestroyTexture(points_texture);
    return EXIT_SUCCESS;
}