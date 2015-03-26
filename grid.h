#ifndef GRID
#define GRID

#include <stdbool.h>

#define GRID_WIDTH 50 
#define GRID_HEIGHT 25 

typedef int Grid[GRID_WIDTH][GRID_HEIGHT]; 

void buildLayout(Grid* grid);

Grid *copyGrid(Grid* original);

bool sameGrid(Grid *model, Grid *check);

void printGrid(Grid *grid);

void printGridAsChars(Grid *grid);

bool drawCharToGrid(char c, int x, int y, Grid* grid);

bool isLegal(int x, int y, Grid *grid);

bool sameLocation(int x1, int y1, int x2, int y2);

#endif /* GRID */
