#ifndef GRID
#define GRID
#include "grid.h"
#endif

#ifndef LOCATION
#define LOCATION
#include "location.h"
#endif

void drawPath(char *actions, Location *start, Grid *grid);

bool checkForWin(Location *location, Grid *grid);

Location *getNextLocation(char action, Location *start, Grid *grid);

typedef struct Game {
    Grid *grid;
    Location *start;
    Location *agent;
} Game;
