#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "grid.h"
#include "location.h"
#include "util.h"
#include "game.h"

bool moveAgent(char action, Game *game);

bool isWin(Game *game);

void drawMove(char move, Game *game);

void placeStart(Location *start, Game *game);

void placeGoal(Location *goal, Game *game);

Grid newDisplay(Grid board);

Grid newBoard(void);

Game *newGame(bool weighted)
{
    Game *game = malloc(sizeof(Game));

    Grid board;
    if (weighted)
        board = newWeightedGrid();
    else
        board = newGrid();
    game->board = board;

    Grid display = newDisplay(board);
    game->display = display;

    Location *start = malloc(sizeof(Location)); // placeStart populates
    placeStart(start, game);
    game->start = start;

    Location *goal = malloc(sizeof(Location)); // placeGoal populates 
    placeGoal(goal, game);

    Location *agent = malloc(sizeof(Location));
    *agent = *start;
    game->agent = agent;
    
    return game;
}

void playGame(char *actions, Game *game)
{
    bool winner = false;
    int i = 0;
    while(actions != NULL && actions[i] != '\0')
    {
        char action = actions[i];

        if (!moveAgent(action, game))
            break;

        if (isWin(game)) 
        {
            winner = true;
            break;
        }
        
        drawMove(action, game);

        i += 1;
    }

    printGridAsChars(game->display);

    if (winner)
        printf("WIN\n");
    else
        printf("FAIL\n");
}

Game *resetGame(Game *game) // agh this function is a bit rushed.
{
    // get us a new display and draw start/goal
    deleteGrid(game->display);
    game->display = newDisplay(game->board);
    writeCharToGrid('G',game->goal->x,game->goal->y,game->display);
    writeCharToGrid('S',game->start->x,game->start->y,game->display);

    // reset agent
    game->agent->x = game->start->x;
    game->agent->y = game->start->y;
    
    return game;
}

void deleteGame(Game *game)
{
    deleteGrid(game->board);
    deleteGrid(game->display);
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
        case 'n':
            new_x = x;
            new_y = y - 1;
            break;
        case 's':
            new_x = x;
            new_y = y + 1;
            break;
        case 'e':
            new_x = x + 1;
            new_y = y;
            break;
        case 'w':
            new_x = x - 1;
            new_y = y;
            break;
        default:
            printf("UNRECOGNIZED ACTION: %c\n", action);
            return false;
    }

    if (!isLegal(new_x, new_y, game->board)) 
    {
        printf("ILLEGAL MOVE: (%d,%d)->(%d,%d) with action '%c'.\n",x,y,new_x,new_y,action);
        return false;
    }

    game->agent->x = new_x;
    game->agent->y = new_y;

    return true;
}

bool isWin(Game *game)
{
    return sameLocation(game->agent->x, game->agent->y, game->goal->x, game->goal->y);
}

// returns a new grid that will be the game's display (the thing printed);
Grid newDisplay(Grid board)
{
    Grid display = copyGrid(board);

    for (int y = 0; y < GRID_HEIGHT; y += 1) 
    {
        for (int x = 0; x < GRID_WIDTH; x += 1) 
        {
            char c;
            switch (board[x][y])
            {
                case 0:
                    c = 'X';
                    break;
                case 1:
                    c = '.';
                    break;
                case 2:
                    c = ':';
                    break;
                case 3:
                    c = '~';
                    break;
                case 4:
                    c = '+';
                    break;
                default:
                    c = display[x][y];
            }
            display[x][y] = c;
        }
    }
    return display;
}

// draws a char on the display representing an agent's location and
// action taken to arrive there.
void drawMove(char move, Game *game)
{
    int x = game->agent->x;
    int y = game->agent->y;

    char mark;
    switch (move)
    {
        case 'n':
            mark = '^';
            break;
        case 's':
            mark = 'v';
            break;
        case 'e':
            mark = '>';
            break;
        case 'w':
            mark = '<';
            break;
        default: // default should never be reached, but i have it as a fail-safe
            mark = 'x';
            break;
    }

    if (isLegal(x,y,game->board))
    {
        writeCharToGrid(mark,x,y,game->display);
    }
}

// placeStart and placeGoal are special because they draw to the grid AND populate Locations
void placeStart(Location *start, Game *game)
{
    bool placed = false;
    while (!placed)
    {
        int x = randInRange(0,GRID_WIDTH - 1);
        int y = randInRange(0,GRID_HEIGHT - 1);

        if (isLegal(x,y,game->board) && game->display[x][y] != 'G')
        {
            writeCharToGrid('S',x,y,game->display);
            start->x = x;
            start->y = y;
            placed = true;
        }
    }
    game->start = start;
}

void placeGoal(Location *goal, Game *game)
{
    bool placed = false;
    while (!placed)
    {
        int x = randInRange(0,GRID_WIDTH - 1);
        int y = randInRange(0,GRID_HEIGHT - 1);

        if (isLegal(x,y, game->board) && game->display[x][y] != 'S')
        {
            writeCharToGrid('G',x,y,game->display);
            goal->x = x;
            goal->y = y;
            placed = true;
        }
    }
    game->goal = goal;
}
