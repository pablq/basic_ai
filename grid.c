#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "grid.h"

void buildLayout(Grid grid);
bool inBounds(int x, int y);

Grid newBlankGrid(void)
{
    Grid blank = malloc(sizeof(int *) * GRID_WIDTH);
    for (int i = 0; i < GRID_WIDTH; i += 1)
    {
        int *column = malloc(sizeof(int) * GRID_HEIGHT);
        blank[i] = column; 
    }
    return blank;
}

Grid newGrid(void)
{
    Grid grid = newBlankGrid();
    buildLayout(grid);
    return grid;
}

void setCostAreas(Grid grid);

Grid newWeightedGrid(void)
{
    Grid grid = newBlankGrid();
    buildLayout(grid);
    setCostAreas(grid);
    return grid;
}

// sets 9 sections with cost of either 1, 2, or 4
void setCostAreas(Grid grid)
{
    int thirdWidth = GRID_WIDTH / 3;
    int thirdHeight = GRID_HEIGHT / 3;

    int vals[] = { 1, 1, 1, 2, 2, 4 };
    int sectionVals[9];
    for (int i = 0; i < 9; i += 1)
    {
        int valIndex = randInRange(0,5);
        sectionVals[i] = vals[valIndex];
    }

    bool is1, is2, is3, is4, is5, is6, is7, is8, is9;

    int thisVal;
    for (int x = 0; x < GRID_WIDTH; x += 1)
    {
        for (int y = 0; y < GRID_HEIGHT; y += 1)
        {
            is1 = (x <= thirdWidth && y <= thirdHeight);
            is2 = ((x > thirdWidth && x <= thirdWidth * 2) && y <= thirdHeight);
            is3 = (x > thirdWidth * 2 && y <= thirdHeight);
            is4 = (x <= thirdWidth && (y > thirdHeight && y <= thirdHeight * 2));
            is5 = ((x > thirdWidth && x <= thirdWidth * 2) && (y > thirdHeight && y <= thirdHeight * 2));
            is6 = (x > thirdWidth * 2 && (y > thirdHeight && y <= thirdHeight * 2));
            is7 = (x <= thirdWidth && y > thirdHeight * 2);
            is8 = ((x > thirdWidth && x <= thirdWidth * 2) && y > thirdHeight * 2);
            is9 = (x > thirdWidth * 2 && y > thirdHeight * 2);
            if (is1)
                thisVal = sectionVals[0];
            if (is2)
                thisVal = sectionVals[1];
            if (is3)
                thisVal = sectionVals[2];
            if (is4)
                thisVal = sectionVals[3];
            if (is5)
                thisVal = sectionVals[4];
            if (is6)
                thisVal = sectionVals[5];
            if (is7)
                thisVal = sectionVals[6];
            if (is8)
                thisVal = sectionVals[7];
            if (is9)
                thisVal = sectionVals[8];
            if (isLegal(x,y,grid))
                grid[x][y] = thisVal;
        }
    }
}

void deleteGrid(Grid grid)
{
    for (int i = 0; i < GRID_WIDTH; i += 1)
    {
        free(grid[i]);
    }
    free(grid);
}

Grid copyGrid(Grid original)
{
    Grid copy = newBlankGrid();

    for (int y = 0; y < GRID_HEIGHT; y += 1) 
    {
        for (int x = 0; x < GRID_WIDTH; x += 1) 
        {
            copy[x][y] = original[x][y];
        }
    }
    return copy;
}

bool inBounds(int x, int y)
{
    return (x >= 0 && x < GRID_WIDTH && y>= 0 && y < GRID_HEIGHT);
}

bool isLegal(int x, int y, Grid grid) // mega important method. used throughout program (especially game)
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

void buildLayout(Grid grid)
{
    // Create outside walls and open locations.
    for (int x = 0; x < GRID_WIDTH; x += 1) 
    {
        for (int y = 0; y < GRID_HEIGHT; y += 1) 
        {
            bool leftBorder = (x == 0);
            bool rightBorder = (x == GRID_WIDTH - 1);
            bool topBorder = (y == 0);
            bool bottomBorder = (y == GRID_HEIGHT - 1);

            if (leftBorder || rightBorder || topBorder || bottomBorder)
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
    int numWalls = randInRange(15,30);
    for (int i = 0; i < numWalls; i += 1)
    {
        // give walls varied lengths
        int len = randInRange(3,10);
        int x, y;

        // decide whether wall will be horizontal or vertical.
        int isHoriz = randInRange(0,1);

        // pick the starting point of the wall:
        // horizontal =  left->right, vertical = top->down 
        if(isHoriz) 
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
            if (isHoriz) {

                // if you're in the middle of a wall and the next space is already a wall
                // or there is already a wall directly above or below - stop
                if ((!isFirst && !isLast) && (!rightIsOpen || !aboveIsOpen || !belowIsOpen))
                    break;
                else
                    x += 1;

            } else {

                // if you're in the middle of a wall and the next space is already a wall
                // or there is already a wall directly left or right - stop
                if ((!isFirst && !isLast) && (!belowIsOpen || !rightIsOpen || !leftIsOpen))
                    break;
                else
                    y += 1;
            }
        }
    }
}

bool writeCharToGrid(char c, int x, int y, Grid grid)
{
    if (isLegal(x, y, grid))
    {
        grid[x][y] = c;
        return true;
    }
    return false;
}
