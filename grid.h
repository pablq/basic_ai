#ifndef LOCATION
#define LOCATION
#include "location.h"
#endif

#ifndef WH
#define WH
#define WIDTH 50
#define HEIGHT 25
#endif

typedef char Grid[WIDTH][HEIGHT]; 

void buildLayout(Grid* grid);

void printGrid(Grid *grid);

void placeGoal(Location *goal, Grid *grid);

void placeAgent(Location *agent, Grid *grid);
