#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "grid.h"

void printGridAsChars(Grid grid);

void printGrid(Grid grid);

bool isLegal(int x, int y, Grid grid);

Grid copyGrid(Grid original);

void buildLayout(Grid grid);

bool inBounds(int x, int y);

Grid newGrid(void)
{
    Grid myGrid = malloc(sizeof(int *) * GRID_WIDTH);
    for (int i = 0; i < GRID_WIDTH; i += 1)
    {
        int *column = malloc(sizeof(int) * GRID_HEIGHT);
        myGrid[i] = column; 
    }
    return myGrid;
}

void deleteGrid(Grid grid)
{
    for (int i = 0; i < GRID_WIDTH; i += 1)
    {
        free(grid[i]);
    }
    free(grid);
}

void buildLayout(Grid grid)
{
    // Create outside walls and open locations.
    for (int x = 0; x < GRID_WIDTH; x += 1) 
    {
        for (int y = 0; y < GRID_HEIGHT; y += 1) 
        {
            bool left_border = (x == 0);
            bool right_border = (x == GRID_WIDTH - 1);
            bool top_border = (y == 0);
            bool bottom_border = (y == GRID_HEIGHT - 1);

            if (left_border || right_border || top_border || bottom_border)
            {
                // 0 is the value for walls
                grid[x][y] = 0;

            } else {

                // 1 is the base value for acceptable locations
                grid[x][y] = 1;
            }
        }
    }

    // Now add some interior walls
    int num_walls = randInRange(15,30);
    for (int i = 0; i < num_walls; i += 1)
    {
        // give walls varied lengths
        int len = randInRange(2,5);
        int x, y;

        // decide whether wall will be horizontal or vertical.
        int is_horiz = randInRange(0,1);

        // pick the starting point of the wall:
        // horizontal =  left->right
        // vertical = top->down 
        if(is_horiz) 
        {
            x = randInRange(0, (GRID_WIDTH - 1) - len);
            y = randInRange(0, GRID_HEIGHT - 1);
    
        } else {
            x = randInRange(0, GRID_WIDTH -1);
            y = randInRange(0, (GRID_HEIGHT - 1) - len);
        }

        // here we actually draw the wall
        for (int w = 0; w < len; w += 1)
        {
            bool isFirst = (w == 0);
            bool isLast = (w == len - 1);
            bool rightIsOpen = isLegal(x+1, y, grid);
            bool leftIsOpen = isLegal(x-1, y, grid);
            bool aboveIsOpen = isLegal(x, y-1, grid);
            bool belowIsOpen = isLegal(x, y+1, grid); 

            grid[x][y] = 0;
            if (is_horiz) {
                // if you're in the middle of a wall and the next space is already a wall
                // or there is already a wall directly above or below - stop
                if ((!isFirst && !isLast) && (!rightIsOpen || !aboveIsOpen || !belowIsOpen))
                {
                    break;
                } else {
                    x += 1;
                }
            } else {
                // if you're in the middle of a wall and the next space is already a wall
                // or there is already a wall directly left or right - stop
                if ((!isFirst && !isLast) && (!belowIsOpen || !rightIsOpen || !leftIsOpen))
                {
                    break;
                } else { // otherwise, advance to the next block
                    y += 1;
                }
            }
        }
    }
}

void drawWall(int x1, int x2, int len, bool horiz, Grid grid)
{
    for (int i = 0; i < len; i += 1)
    {
        
    }
}


Grid copyGrid(Grid original)
{
    Grid copy = newGrid();

    for (int y = 0; y < GRID_HEIGHT; y += 1) 
    {
        for (int x = 0; x < GRID_WIDTH; x += 1) 
        {
            copy[x][y] = original[x][y];
        }
    }
    return copy;
}

bool sameGrid(Grid model, Grid check)
{
    for (int y = 0; y < GRID_HEIGHT; y += 1) 
    {
        for (int x = 0; x < GRID_WIDTH; x += 1) 
        {
            if (model[x][y] != check[x][y]) 
            {
                return false;
            }
        }
    }
    return true;
}

void printGrid(Grid grid)
{
    for (int y = 0; y < GRID_HEIGHT; y += 1) 
    {
        for (int x = 0; x < GRID_WIDTH; x += 1) 
        {
            printf("%d", grid[x][y]);
        }
        printf("\n");
    }
}

void printGridAsChars(Grid grid)
{
    for (int y = 0; y < GRID_HEIGHT; y += 1) 
    {
        for (int x = 0; x < GRID_WIDTH; x += 1) 
        {
            printf("%c", grid[x][y]);
        }
        printf("\n");
    }
}

bool inBounds(int x, int y)
{
    return (x >= 0 && x < GRID_WIDTH && y>= 0 && y < GRID_HEIGHT);
}

bool isLegal(int x, int y, Grid grid)
{
    if (!inBounds(x,y))
    {
        return false;
    }
    if (grid[x][y] == 0) 
    {
        return false;
    }
    return true;
}
