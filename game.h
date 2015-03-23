#ifndef GRID
#define GRID
#include "grid.h"
#endif

#ifndef LOCATION
#define LOCATION
#include "location.h"
#endif

#ifndef BOOL
#define BOOL
#include <stdbool.h>
#endif

typedef struct Game {
    Grid *grid;
    Location *start;
    Location *goal;
    Location *agent;
} Game;

Game *newGame(void);

void play(char *actions, Game *game);

void deleteGame(Game *game);
