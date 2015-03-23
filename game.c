#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grid.h"
#include "location.h"
#include "util.h"
#include "game.h"

bool moveAgent(char action, Game *game);

bool sameLocation(Location *a, Location *b);

bool isWin(Game *game);

void drawMove(char move, Location *agent, Grid *grid);

void drawWinner(Location *winner, Grid *grid);

void placeStart(Location *start, Grid *grid);

void placeGoal(Location *goal, Grid *grid);

Game *newGame(void)
{
    Grid *grid = malloc(sizeof(Grid));
    buildLayout(grid);

    Location *start = malloc(sizeof(Location));
    placeStart(start, grid);

    Location *goal = malloc(sizeof(Location));
    placeGoal(goal, grid);

    Location *agent = malloc(sizeof(Location));
    *agent = *start;

    Game *game = malloc(sizeof(Game));
    game->grid = grid;
    game->start = start;
    game->agent = agent;
    game->goal = goal;

    return game;
}

void playGame(char *actions, Game *game)
{
    bool winner = false;
    int i = 0;
    while(actions[i] != '\0')
    {
        char action = actions[i];

        if (!moveAgent(action, game))
        {
            break;
        }

        drawMove(action, game->agent, game->grid);

        if (isWin(game)) 
        {
            winner = true;
            break;
        }

        i += 1;
    }

    if (winner)
    {
        drawWinner(game->agent, game->grid);
        printf("WINNER!\n");
    } else {
        printf("GAME OVER.\n");
    }
}

void deleteGame(Game *game)
{
    free(game->grid);
    free(game->start);
    free(game->goal);
    free(game->agent);
    free(game);
}

bool moveAgent(char action, Game *game)
{
    int new_x, new_y;
    int x = game->agent->x;
    int y = game->agent->y;

    switch (action) 
    {
        case 'N':
            new_x = x;
            new_y = y - 1;
            break;
        case 'S':
            new_x = x;
            new_y = y + 1;
            break;
        case 'E':
            new_x = x + 1;
            new_y = y;
            break;
        case 'W':
            new_x = x - 1;
            new_y = y;
            break;
        default:
            printf("UNRECOGNIZED ACTION: %c\n", action);
            return false;
    }

    if (!isLegal(new_x, new_y, game->grid)) 
    {
        printf("ILLEGAL MOVE: (%d,%d)->(%d,%d) with action %c\n",x,y,new_x,new_y,action);
        return false;
    }

    game->agent->x = new_x;
    game->agent->y = new_y;

    printf("SUCCESSFUL MOVE: (%d,%d)->(%d,%d) with action %c\n",x,y,new_x,new_y,action);
    return true;
}

bool sameLocation(Location *a, Location *b)
{
    return (a->x == b->x && a->y == b->y);
}

bool isWin(Game *game)
{
    return sameLocation(game->agent, game->goal);
}

// the below functions all use the grid api's drawCharToGrid function to actually draw on the grid

void drawMove(char move, Location *agent, Grid *grid)
{
    int x = agent->x;
    int y = agent->y;
    char mark = '?';
    switch (move)
    {
        case 'N':
            mark = '^';
            break;
        case 'S':
            mark = 'v';
            break;
        case 'E':
            mark = '>';
            break;
        case 'W':
            mark = '<';
            break;
    }

    if (isLegal(x,y,grid))
    {
        drawCharToGrid(mark,x,y,grid);
    }
}

void drawWinner(Location *winner, Grid *grid)
{
    int x = winner->x;
    int y = winner->y;
    if (isLegal(x,y,grid))
    {
        drawCharToGrid('W',x,y,grid);
    }
}

// these two are special because they draw to the grid AND populate Location structs
        
void placeStart(Location *start, Grid *grid)
{
    bool placed = false;
    while (!placed)
    {
        int x = randInRange(0,GRID_WIDTH - 1);
        int y = randInRange(0,GRID_HEIGHT - 1);

        if (isLegal(x,y,grid) && *grid[x][y] != 'G')
        {
            drawCharToGrid('S',x,y,grid);
            start->x = x;
            start->y = y;
            placed = true;
        }
    }
}

void placeGoal(Location *goal, Grid *grid)
{
    bool placed = false;
    while (!placed)
    {
        int x = randInRange(0,GRID_WIDTH - 1);
        int y = randInRange(0,GRID_HEIGHT - 1);

        if (isLegal(x,y, grid) && *grid[x][y] != 'S')
        {
            drawCharToGrid('G',x,y,grid);
            goal->x = x;
            goal->y = y;
            placed = true;
        }
    }
}
