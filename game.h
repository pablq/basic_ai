#ifndef GAME
#define GAME

#include <stdbool.h>
#include "grid.h"
#include "location.h"

typedef struct Game {
    Grid board;
    Grid display;
    Location *start;
    Location *goal;
    Location *agent;
} Game;

Game *newGame(bool weighted);

void playGame(char *actions, Game *game);

Game *resetGame(Game *game);

void deleteGame(Game *game);

#endif /*GAME*/
