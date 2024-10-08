#include <SDL.h>
#include <SDL_ttf.h>
#include <time.h>
#include "filepaths.h"
#include "game.h"
#include "render.h"
#include "menu.h"

int main(int argc, char *argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! TTF_Error: %s\n", TTF_GetError());
        return 1;
    }

    TTF_Font *font = TTF_OpenFont(FONT_PATH, 24);
    if (font == NULL) {
        printf("Failed to load font! TTF_Error: %s\n", TTF_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH * 30, HEIGHT * 30, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    allocateMemory();
    loadTextures(renderer);

    mainMenu(renderer, font);
    if (!gameOver) {
        setup();
    }

    SDL_Event e;
    while (!gameOver) {
        handleInput(&e);
        move();
        generateSpecialFruit();
        renderGame(renderer, font);
        SDL_Delay(delay);
    }

    gameOverScreen(renderer, font);

    freeMemory();
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
