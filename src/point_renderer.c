#include <SDL2/SDL.h>
#include "point_renderer.h"
#include "point.h"

#define POINT_SIZE 4

SDL_Texture *create_texture(SDL_Renderer *renderer) {
    return SDL_CreateTexture(
        renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, TEXTURE_W, TEXTURE_H
    );
}

void render_texture(
    SDL_Renderer *renderer,
    SDL_Texture *texture,
    point_t *points, int n_points,
    point_t *ch, int n_ch,
    color_t color
) {
    SDL_SetRenderTarget(renderer, texture);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 0; i < n_points; i++) {
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