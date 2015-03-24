#ifndef GRID
#define GRID

#include <stdbool.h>

#define GRID_WIDTH 50
#define GRID_HEIGHT 25

typedef int Grid[GRID_WIDTH][GRID_HEIGHT]; 

void buildLayout(Grid* grid);

void copyGrid(Grid* original, Grid *copy);

void printGrid(Grid *grid);

void printGridAsChars(Grid *grid);

bool drawCharToGrid(char c, int x, int y, Grid* grid);

bool isLegal(int x, int y, Grid *grid);

bool isAvailable(int x, int y, Grid *grid);

#endif /* GRID */
