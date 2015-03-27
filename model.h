#ifndef GAMEMODEL
#define GAMEMODEL

typedef struct StateNode
{
    Location *location;
    char action;
    int cost;
} StateNode;

List* getSuccessorStateNodes(StateNode *parent, Grid grid);

// note dif between generic board/location based items
// and items that return StateNode specific stuff

bool isGoalState(Location *location, Grid grid);

//costFn here

#endif /* GAMEMODEL */
