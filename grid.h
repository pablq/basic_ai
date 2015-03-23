#ifndef BOOL
#define BOOL
#include <stdbool.h>
#endif

#ifndef GRID_DIMS
#define GRID_DIMS
#define GRID_WIDTH 50
#define GRID_HEIGHT 25
#endif

typedef char Grid[GRID_WIDTH][GRID_HEIGHT]; 

void buildLayout(Grid* grid);

bool drawCharToGrid(char c, int x, int y, Grid* grid);

void printGrid(Grid *grid);

bool isLegal(int x, int y, Grid *grid);
