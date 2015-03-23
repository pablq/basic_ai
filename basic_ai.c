#ifndef GAME
#define GAME
#include "game.h"
#endif

#ifndef GRID
#define GRID
#include "grid.h"
#endif

#ifndef LOCATION
#define LOCATION
#include "location.h"
#endif

#ifndef STDLIB
#define STDLIB
#include <stdlib.h>
#endif

int main (void)
{
    Game *game = newGame();

    printGrid(game->grid);

    deleteGame(game);

    return 0;
}
