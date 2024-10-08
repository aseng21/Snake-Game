#ifndef RENDER_H
#define RENDER_H

#include <SDL.h>
#include <SDL_ttf.h>

// Function Prototypes
void loadTextures(SDL_Renderer *renderer);
void drawTexture(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int w, int h);
void renderText(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Color color, int x, int y);
void renderGame(SDL_Renderer *renderer, TTF_Font *font);

#endif // RENDER_H
