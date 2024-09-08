#ifndef POINT_RENDERER_H
#define POINT_RENDERER_H

#define TEXTURE_W 800
#define TEXTURE_H 600

#include "point.h"

typedef struct color {
    uint8_t r, g, b;
} color_t;

SDL_Texture *create_texture(SDL_Renderer *renderer);

void render_texture(
    SDL_Renderer *renderer,
    SDL_Texture *texture,
    point_t *points, int n_points,
    point_t *ch, int n_ch,
    color_t color
);

#endif