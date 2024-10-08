#ifndef GAME_H
#define GAME_H

#include <SDL.h>

// Constants
#define WIDTH 20
#define HEIGHT 20
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define INITIAL_DELAY 200

// Global Variables
extern int gameOver;
extern int score;
extern int snakeLength;
extern int *snakeX, *snakeY;
extern int fruitX, fruitY;
extern int direction;
extern int gameMode;
extern int specialFruitX, specialFruitY;
extern int specialFruitActive;
extern int **obstacles;
extern int delay;

// Function Prototypes
void allocateMemory();
void freeMemory();
void setup();
void handleInput(SDL_Event *e);
void move();
void generateSpecialFruit();

#endif // GAME_H
