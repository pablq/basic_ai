#ifndef GAMEMODEL
#define GAMEMODEL

typedef struct StateNode
{
    Location *location;
    char action;
    int cost;
} StateNode;

List* getSuccessorStateNodes(StateNode *parent, Grid grid);
char *stateToString(StateNode *state);

// note dif between generic board/location based items
// and items that return StateNode specific stuff

bool isGoalState(Location *location, Game *game); // <- utils sameLocation() does this

//costFn here

#endif /* GAMEMODEL */
