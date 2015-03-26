#include <stdlib.h>
#include "grid.h"

int main (void) {

    Grid *grid = malloc(sizeof(Grid));

    buildLayout(grid);
    
    printGrid(grid);
    printGridAsChars(grid);

    free(grid);
} 
