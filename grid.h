#ifndef LOCATION
#define LOCATION
#include "location.h"
#endif

#ifndef GRID_DIMS
#define GRID_DIMS
#define GRID_WIDTH 50
#define GRID_HEIGHT 25
#endif

typedef char Grid[GRID_WIDTH][GRID_HEIGHT]; 

void buildLayout(Grid* grid);

void drawCharToGrid(char c, Location *loc, Grid* grid);

void printGrid(Grid *grid);
