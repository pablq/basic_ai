#ifndef SEARCH
#define SEARCH

#include "searchhelper.h"
#include "game.h"

typedef struct FringeNode
{
    StateNode *state;
    char *allActions;
    int costOfActions;
} FringeNode;

char *dfs(Game *game);

#endif /* SEARCH */
