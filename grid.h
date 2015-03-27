#ifndef GRID
#define GRID

#include <stdbool.h>

#define GRID_WIDTH 50 
#define GRID_HEIGHT 25 

typedef int **Grid; 

Grid newGrid(void);

void deleteGrid(Grid grid);

Grid copyGrid(Grid original);

void printGrid(Grid grid);

void printGridAsChars(Grid grid);

bool isLegal(int x, int y, Grid grid);

bool writeCharToGrid(char c, int x, int y, Grid grid);

#endif /* GRID */
