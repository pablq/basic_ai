#include <stdio.h>

#include "grid.h"

int main (void) {
    
    Grid grid = newWeightedGrid();

    printGrid(grid);

    return 0;
} 
