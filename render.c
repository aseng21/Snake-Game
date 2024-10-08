#include <SDL.h>
#include <SDL_ttf.h>
#include "filepaths.h"
#include "game.h"
#include "render.h"

SDL_Texture *snakeTexture, *fruitTexture, *specialFruitTexture, *obstacleTexture;

void loadTextures(SDL_Renderer *renderer) {
    SDL_Surface *loadedSurface = SDL_LoadBMP(SNAKE_TEXTURE_PATH);
    snakeTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);

    loadedSurface = SDL_LoadBMP(FRUIT_TEXTURE_PATH);
    fruitTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);

    loadedSurface = SDL_LoadBMP(SPECIAL_FRUIT_TEXTURE_PATH);
    specialFruitTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);

    loadedSurface = SDL_LoadBMP(OBSTACLE_TEXTURE_PATH);
    obstacleTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
}

void drawTexture(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int w, int h) {
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void renderText(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Color color, int x, int y) {
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect rect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void renderGame(SDL_Renderer *renderer, TTF_Font *font) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (int i = 0; i < snakeLength; i++) {
        drawTexture(renderer, snakeTexture, snakeX[i] * 30, snakeY[i] * 30, 30, 30);
    }

    SDL_Rect fruitRect = {fruitX * 30, fruitY * 30, 30, 30};
    SDL_RenderCopy(renderer, fruitTexture, NULL, &fruitRect);

    if (specialFruitActive) {
        SDL_Rect specialFruitRect = {specialFruitX * 30, specialFruitY * 30, 30, 30};
        SDL_RenderCopy(renderer, specialFruitTexture, NULL, &specialFruitRect);
    }

    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            if (obstacles[x][y] == 1) {
                SDL_Rect obstacleRect = {x * 30, y * 30, 30, 30};
                SDL_RenderCopy(renderer, obstacleTexture, NULL, &obstacleRect);
            }
        }
    }

    SDL_Color white = {255, 255, 255, 255};
    char scoreText[50];
    sprintf(scoreText, "Score: %d", score);
    renderText(renderer, font, scoreText, white, 10, 10);

    SDL_RenderPresent(renderer);
}
