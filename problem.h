#ifndef LOCATION 
#define LOCATION
#include "location.h"
#endif

#ifndef GRID
#define GRID
#include "grid.h"
#endif

char *getLegalActions(Location *agent, Grid *grid);

bool checkForWin(Location *location, Grid *grid);

// the char * actions will always be null terminated
// the length value does not count the null terminator
typedef struct Path
{
    char *actions;
    int length;
} Path;

typedef struct Node
{
    Location *loc;
    Path *path;
} Node;
