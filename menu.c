#include <SDL.h>
#include <SDL_ttf.h>
#include "menu.h"

#include "game.h"
#include "render.h"

void mainMenu(SDL_Renderer *renderer, TTF_Font *font) {
    SDL_Color white = {255, 255, 255, 255};
    int menuSelection = 0;
    SDL_Event e;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                exit(0);
            }
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        menuSelection = (menuSelection - 1 + 3) % 3;
                        break;
                    case SDLK_DOWN:
                        menuSelection = (menuSelection + 1) % 3;
                        break;
                    case SDLK_RETURN:
                        quit = 1;
                        break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        renderText(renderer, font, "Snake Game", white, 150, 100);
        renderText(renderer, font, menuSelection == 0 ? "> Start" : "  Start", white, 150, 200);
        renderText(renderer, font, menuSelection == 1 ? "> Mode: Classic" : "  Mode: Classic", white, 150, 250);
        renderText(renderer, font, menuSelection == 2 ? "> Mode: Obstacles" : "  Mode: Obstacles", white, 150, 300);

        SDL_RenderPresent(renderer);
    }
    gameMode = menuSelection == 2 ? 1 : 0;
}

void gameOverScreen(SDL_Renderer *renderer, TTF_Font *font) {
    SDL_Color white = {255, 255, 255, 255};
    SDL_Event e;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                exit(0);
            }
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_RETURN) {
                    quit = 1;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        renderText(renderer, font, "Game Over", white, 150, 100);
        char scoreText[50];
        sprintf(scoreText, "Final Score: %d", score);
        renderText(renderer, font, scoreText, white, 150, 200);
        renderText(renderer, font, "Press Enter to Quit", white, 150, 300);

        SDL_RenderPresent(renderer);
    }
}
