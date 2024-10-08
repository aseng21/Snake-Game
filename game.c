#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "filepaths.h"

int gameOver;
int score;
int snakeLength;
int *snakeX, *snakeY;
int fruitX, fruitY;
int direction;
int gameMode;
int specialFruitX, specialFruitY;
int specialFruitActive;
int **obstacles;
int delay;

void allocateMemory() {
    snakeX = (int *)malloc(100 * sizeof(int));
    snakeY = (int *)malloc(100 * sizeof(int));
    obstacles = (int **)malloc(WIDTH * sizeof(int *));
    for (int i = 0; i < WIDTH; i++) {
        obstacles[i] = (int *)malloc(HEIGHT * sizeof(int));
    }
}

void freeMemory() {
    free(snakeX);
    free(snakeY);
    for (int i = 0; i < WIDTH; i++) {
        free(obstacles[i]);
    }
    free(obstacles);
}

void setup() {
    gameOver = 0;
    score = 0;
    snakeLength = 1;
    snakeX[0] = WIDTH / 2;
    snakeY[0] = HEIGHT / 2;
    srand(time(NULL));
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
    specialFruitActive = 0;
    direction = RIGHT;
    delay = INITIAL_DELAY;

    if (gameMode == 1) {
        for (int i = 0; i < WIDTH * HEIGHT / 10; i++) {
            int obsX = rand() % WIDTH;
            int obsY = rand() % HEIGHT;
            if ((obsX != snakeX[0] || obsY != snakeY[0]) && (obsX != fruitX || obsY != fruitY)) {
                obstacles[obsX][obsY] = 1;
            }
        }
    }
}

void handleInput(SDL_Event *e) {
    while (SDL_PollEvent(e) != 0) {
        if (e->type == SDL_QUIT) {
            gameOver = 1;
        }
        if (e->type == SDL_KEYDOWN) {
            switch (e->key.keysym.sym) {
                case SDLK_w:
                    direction = UP;
                    break;
                case SDLK_s:
                    direction = DOWN;
                    break;
                case SDLK_a:
                    direction = LEFT;
                    break;
                case SDLK_d:
                    direction = RIGHT;
                    break;
            }
        }
    }
}

void move() {
    int prevX = snakeX[0];
    int prevY = snakeY[0];
    int prev2X, prev2Y;
    snakeX[0] = snakeX[0] + (direction == RIGHT ? 1 : (direction == LEFT ? -1 : 0));
    snakeY[0] = snakeY[0] + (direction == DOWN ? 1 : (direction == UP ? -1 : 0));
    for (int i = 1; i < snakeLength; i++) {
        prev2X = snakeX[i];
        prev2Y = snakeY[i];
        snakeX[i] = prevX;
        snakeY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    if (gameMode == 0) {
        if (snakeX[0] >= WIDTH) snakeX[0] = 0;
        else if (snakeX[0] < 0) snakeX[0] = WIDTH - 1;
        if (snakeY[0] >= HEIGHT) snakeY[0] = 0;
        else if (snakeY[0] < 0) snakeY[0] = HEIGHT - 1;
    } else if (gameMode == 1) {
        if (snakeX[0] >= WIDTH || snakeX[0] < 0 || snakeY[0] >= HEIGHT || snakeY[0] < 0) {
            gameOver = 1;
        }
    }

    if (snakeX[0] == fruitX && snakeY[0] == fruitY) {
        score += 10;
        snakeLength++;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
        delay = INITIAL_DELAY - score / 10;
    }

    if (specialFruitActive && snakeX[0] == specialFruitX && snakeY[0] == specialFruitY) {
        score += 20;
        snakeLength += 2;
        specialFruitActive = 0;
    }

    for (int i = 1; i < snakeLength; i++) {
        if (snakeX[i] == snakeX[0] && snakeY[i] == snakeY[0]) {
            gameOver = 1;
        }
    }

    if (obstacles[snakeX[0]][snakeY[0]] == 1) {
        gameOver = 1;
    }
}

void generateSpecialFruit() {
    if (!specialFruitActive && rand() % 20 == 0) {
        specialFruitX = rand() % WIDTH;
        specialFruitY = rand() % HEIGHT;
        specialFruitActive = 1;
    }
}
