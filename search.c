#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "list.h"
#include "util.h"
#include "hashtable.h"
#include "fringenode.h"
#include "stack.h"
#include "queue.h"
#include "gamemodel.h"

/*
 * DEPTH FIRST SEARCH
 * returns a path to the goal.
 * does not consider movement costs.
 * explores deepest gamestates in the tree (characterized by use of stack)
 * supposedly very memory efficient
 */

char *dfs (Game *game)
{
    // create our fringe as a FILO Stack
    List *fringe = newStack();
    
    // closed will store all the states we've already visited to avoid repeats
    HashTable *closed = newHashTable();

    // prepare state and values for first fringe node
    StateNode *startState = malloc(sizeof(StateNode));
    startState->loc = malloc(sizeof(Location));
    startState->loc->x = game->start->x; // <-Here
    startState->loc->y = game->start->y; // <-Here
    startState->action = 0;
    startState->cost = 0;
   
    char *startPath = "\0";
    int startCost = 0;
    
    // build fringe node and push it to the fringe
    FringeNode *first = newFringeNode(startState, startPath, startCost);
    pushToStack(first, fringe);

    // variables for book-keeping
    int expanded = 0;
    int max_in_fringe = 1; // for first Node we just added
    
    // let's get goin!
    while(true)
    {
        // book-keeping
        max_in_fringe = max(max_in_fringe, fringe->n_items);

        // get the most recently added FringeNode
        FringeNode *fn = popFromStack(fringe);

        // if there was nothing there, we failed :/
        if (fn == NULL)
        {
            printf("No Solution found :(\n");

            // clean up
            deleteStack(fringe);
            deleteHashTable(closed);

            return NULL;
        } 

        // book-keeping
        expanded += 1;

        // if this state's location is the winning state we win!
        if (sameLocation(fn->state->loc->x, fn->state->loc->y, game->goal->x, game->goal->y))
        {
            // take the path, and nullify reference to it from the FringeNode
            char *pathToVictory = fn->path;
            fn->path = NULL;

            // report stats
            printf("Total cost of solution: %d\n", fn->totalCost);
            printf("Total gamestates considered: %d\n", expanded);
            printf("Maximum bytes in fringe during search: %lu\n", max_in_fringe * sizeof(FringeNode));
            printf("Bytes in fringe at solution: %lu\n", fringe->n_items * sizeof(FringeNode));

            // clean up
            deleteFringeNode(fn);
            deleteStack(fringe);
            deleteHashTable(closed);

            // return the glorious path to victory!
            return pathToVictory;

        } else { // if it wasn't the winning state we must keep searching
            
            // get a list of the neighboring gamestates
            List *successors = getSuccessorStateNodes(fn->state, game->board);

            // show actual type of list's items
            StateNode **items = successors->items;

            // create a new FringeNode for each appropriate state in the list
            for (int i = 0; i < successors->n_items; i += 1)
            {
                StateNode *successor = items[i];
                
                // a state is "appropriate if it hasn't already been explored
                if (!stateInHashTable(successor, closed))
                {
                    // add to state to closed list
                    addStateToHashTable(successor, closed);

                    // create a new FringeNode with new state and old FringeNode's path and totalCost
                    FringeNode *new = newFringeNode(successor, fn->path, fn->totalCost);

                    // add it to the fringe
                    pushToStack(new, fringe);

                } else {

                    // the StateNode must be freed - it's useless now
                    free(successor->loc);
                    free(successor);
                }
            }

            // clean up our list that had contained the successors
            free(items); // successors->items
            free(successors);

            // we no longer need the old FringeNode  
            deleteFringeNode(fn);
        }
    } 
}

/*
 * BREADTH FIRST SEARCH
 * returns a direct path to goal.
 * does not consider movement costs.
 * explores outwards gradually (characterized by use of a queue)
 * supposedly very memory expensive
 */

char *bfs(Game *game)
{
    // create our fringe as a FIFO Queue
    FringeNode *fringe = newQueue();
    
    // closed will store all the states we've already visited to avoid repeats
    HashTable *closed = newHashTable();

    // prepare state and values for first fringe node
    StateNode *startState = malloc(sizeof(StateNode));
    startState->loc = malloc(sizeof(Location));
    startState->loc->x = game->start->x; // <-Here
    startState->loc->y = game->start->y; // <-Here
    startState->action = 0;
    startState->cost = 0;
   
    char *startPath = "\0";
    int startCost = 0;
    
    // build fringe node and push it to the fringe
    FringeNode *first = newFringeNode(startState, startPath, startCost);
    pushToQueue(first, &fringe);

    // variables for book-keeping
    int expanded = 0;
    int n_items = 1; // for the first FringeNode
    int max_in_fringe = 1;
    
    // let's get goin!
    while(true)
    {
        // book-keeping
        max_in_fringe = max(max_in_fringe, n_items);

        // get the next FringeNode in the queue
        FringeNode *fn = nextInQueue(&fringe);

        // if there was nothing there, we failed :/
        if (fn == NULL)
        {
            printf("No Solution found :(\n");

            // clean up
            deleteQueue(&fringe);
            deleteHashTable(closed);

            return NULL;
        } 

        // book-keeping
        expanded += 1;
        n_items -= 1;

        // if this state's location is the winning state we win!
        if (sameLocation(fn->state->loc->x, fn->state->loc->y, game->goal->x, game->goal->y))
        {
            // take the path, and nullify reference to it from the FringeNode
            char *pathToVictory = fn->path;
            fn->path = NULL;

            // report stats
            printf("Total cost of solution: %d\n", fn->totalCost);
            printf("Total gamestates considered: %d\n", expanded);
            printf("Maximum bytes in fringe during search: %lu\n", max_in_fringe * sizeof(FringeNode));
            printf("Bytes in fringe at solution: %lu\n", n_items * sizeof(FringeNode));

            // clean up
            deleteFringeNode(fn);
            deleteQueue(&fringe);
            deleteHashTable(closed);

            // return the glorious path to victory!
            return pathToVictory;

        } else { // if it wasn't the winning state we must keep searching
            
            // get a list of the neighboring gamestates
            List *successors = getSuccessorStateNodes(fn->state, game->board);

            // show actual type of list's items
            StateNode **items = successors->items;

            // create a new FringeNode for each appropriate state in the list
            for (int i = 0; i < successors->n_items; i += 1)
            {
                StateNode *successor = items[i];
                
                // a state is "appropriate if it hasn't already been explored
                if (!stateInHashTable(successor, closed))
                {
                    // add to state to closed list
                    addStateToHashTable(successor, closed);

                    // create a new FringeNode with new state and old FringeNode's path and totalCost
                    FringeNode *new = newFringeNode(successor, fn->path, fn->totalCost);

                    // add it to the fringe
                    pushToQueue(new, &fringe);
                   
                    // book-keeping 
                    n_items += 1;

                } else {

                    // the StateNode must be freed - it's useless now
                    free(successor->loc);
                    free(successor);
                }
            }

            // clean up our list that had contained the successors
            free(items); // successors->items
            free(successors);

            // we no longer need the old FringeNode  
            deleteFringeNode(fn);
        }
    } 
}

/*
 * UNIFORM COST SEARCH
 * returns optimal path to goal.
 * does consider movement costs.
 * explores outwards gradually with preference for least expensive action (characterized by use of a priority queue)
 * supposedly very memory expensive
 */

char *ucs(Game *game)
{
    // we'll use our fringe as a priority queue
    FringeNode *fringe = newQueue();
    
    // closed will store all the states we've already visited to avoid repeats
    HashTable *closed = newHashTable();

    // prepare state and values for first fringe node
    StateNode *startState = malloc(sizeof(StateNode));
    startState->loc = malloc(sizeof(Location));
    startState->loc->x = game->start->x; // <-Here
    startState->loc->y = game->start->y; // <-Here
    startState->action = 0;
    startState->cost = 0;
   
    char *startPath = "\0";
    int startCost = 0;
    
    // build fringe node and push it to the fringe by cost
    FringeNode *first = newFringeNode(startState, startPath, startCost);
    pushToQueueByCost(first, &fringe);

    // for book-keeping
    int expanded = 0;
    int n_items = 1; // for the first FringeNode
    int max_in_fringe = 1;
    
    // let's get goin!
    while(true)
    {
        // book-keeping
        max_in_fringe = max(max_in_fringe, n_items);

        // get the next fringenode in queue
        FringeNode *fn = nextInQueue(&fringe);

        // if there was nothing there, we failed :/
        if (fn == NULL)
        {
            printf("No Solution found :(\n");

            // clean up
            deleteQueue(&fringe);
            deleteHashTable(closed);

            return NULL;
        } 

        // book-keeping
        expanded += 1;
        n_items -= 1;

        // if this state's location is the winning state we win!
        if (sameLocation(fn->state->loc->x, fn->state->loc->y, game->goal->x, game->goal->y))
        {
            // take the path, and nullify reference to it from the FringeNode
            char *pathToVictory = fn->path;
            fn->path = NULL;

            // report stats
            printf("Total cost of solution: %d\n", fn->totalCost);
            printf("Total gamestates considered: %d\n", expanded);
            printf("Maximum bytes in fringe during search: %lu\n", max_in_fringe * sizeof(FringeNode));
            printf("Bytes in fringe at solution: %lu\n", n_items * sizeof(FringeNode));

            // clean up
            deleteFringeNode(fn);
            deleteQueue(&fringe);
            deleteHashTable(closed);

            // return the glorious path to victory!
            return pathToVictory;

        } else { // if it wasn't the winning state we must keep searching
            
            // get a list of the neighboring gamestates
            List *successors = getSuccessorStateNodes(fn->state, game->board);

            // show actual type of list's items
            StateNode **items = successors->items;

            // create a new FringeNode for each appropriate state in the list
            for (int i = 0; i < successors->n_items; i += 1)
            {
                StateNode *successor = items[i];
                
                // a state is "appropriate if it hasn't already been explored
                if (!stateInHashTable(successor, closed))
                {
                    // add to state to closed list
                    addStateToHashTable(successor, closed);

                    // create a new FringeNode with new state and old FringeNode's path and totalCost
                    FringeNode *new = newFringeNode(successor, fn->path, fn->totalCost);

                    // add it to the fringe by cost
                    pushToQueueByCost(new, &fringe);
                   
                    // book-keeping 
                    n_items += 1;

                } else {

                    // the StateNode must be freed - it's useless now
                    free(successor->loc);
                    free(successor);
                }
            }

            // clean up our list that had contained the successors
            free(items); // successors->items
            free(successors);

            // we no longer need the old FringeNode  
            deleteFringeNode(fn);
        }
    } 
}

/*
 * GREEDY SEARCH
 * quickly returns a path to goal.
 * does not consider movement costs.
 * exploration is guided by a heuristic function (characterized by use of a priority queue with heuristic)
 * can have funny behavior sometimes.
 */

int greedyHeuristic(FringeNode *fn, void *data);

char *greedy(Game *game)
{
    // we'll have our fringe act as a priority queue
    FringeNode *fringe = newQueue();
    
    // closed will store all the states we've already visited to avoid repeats
    HashTable *closed = newHashTable();

    // prepare state and values for first fringe node
    StateNode *startState = malloc(sizeof(StateNode));
    startState->loc = malloc(sizeof(Location));
    startState->loc->x = game->start->x; // <-Here
    startState->loc->y = game->start->y; // <-Here
    startState->action = 0;
    startState->cost = 0;
   
    char *startPath = "\0";
    int startCost = 0;
    
    // build fringe node and push it to the fringe
    FringeNode *first = newFringeNode(startState, startPath, startCost);

    // heuristic is a container that holds a reference to the game and a function.
    // the function returns a node's totalCost plus a computed 'heuristic' value for its state.
    // it is used to determine the priority of a node in the queue. this is the source of A*'s power.
    Heuristic *heur = malloc(sizeof(Heuristic));
    heur->heurfn = &greedyHeuristic;
    heur->data = game;

    pushToQueueByHeuristic(first, heur, &fringe);

    // variables for book-keeping
    int expanded = 0;
    int n_items = 1; // for the first FringeNode
    int max_in_fringe = 1;
    
    // let's get goin!
    while(true)
    {
        // book-keeping
        max_in_fringe = max(max_in_fringe, n_items);

        // get next FringeNode in the queue
        FringeNode *fn = nextInQueue(&fringe);

        // if there was nothing there, we failed :/
        if (fn == NULL)
        {
            printf("No Solution found :(\n");

            // clean up
            free(heur);
            deleteQueue(&fringe);
            deleteHashTable(closed);

            return NULL;
        } 

        // book-keeping
        expanded += 1;
        n_items -= 1;

        // if this state's location is the winning state we win!
        if (sameLocation(fn->state->loc->x, fn->state->loc->y, game->goal->x, game->goal->y))
        {
            // take the path, and nullify reference to it from the FringeNode
            char *pathToVictory = fn->path;
            fn->path = NULL;

            // report stats
            printf("Total cost of solution: %d\n", fn->totalCost);
            printf("Total gamestates considered: %d\n", expanded);
            printf("Maximum bytes in fringe during search: %lu\n", max_in_fringe * sizeof(FringeNode));
            printf("Bytes in fringe at solution: %lu\n", n_items * sizeof(FringeNode));

            // clean up
            free(heur);
            deleteFringeNode(fn);
            deleteQueue(&fringe);
            deleteHashTable(closed);

            // return the glorious path to victory!
            return pathToVictory;

        } else { // if it wasn't the winning state we must keep searching
            
            // get a list of the neighboring gamestates
            List *successors = getSuccessorStateNodes(fn->state, game->board);

            // show actual type of list's items
            StateNode **items = successors->items;

            // create a new FringeNode for each appropriate state in the list
            for (int i = 0; i < successors->n_items; i += 1)
            {
                StateNode *successor = items[i];
                
                // a state is "appropriate if it hasn't already been explored
                if (!stateInHashTable(successor, closed))
                {
                    // add to state to closed list
                    addStateToHashTable(successor, closed);

                    // create a new FringeNode with new state and old FringeNode's path and totalCost
                    FringeNode *new = newFringeNode(successor, fn->path, fn->totalCost);

                    // add it to the fringe by heuristic
                    pushToQueueByHeuristic(new, heur, &fringe);
                   
                    // book-keeping 
                    n_items += 1;

                } else {

                    // the StateNode must be freed - it's useless now
                    free(successor->loc);
                    free(successor);
                }
            }

            // clean up our list that had contained the successors
            free(items); // successors->items
            free(successors);

            // we no longer need the old FringeNode  
            deleteFringeNode(fn);
        }
    } 
}

int greedyHeuristic(FringeNode *fn, void *data)
{
    Game *game = data;
    return manhattanDistance(fn->state->loc->x, fn->state->loc->y, game->goal->x, game->goal->y);
}

/*
 * ASTAR SEARCH
 * returns optimal path to goal.
 * does consider movement costs.
 * exploration is guided by a heuristic function (characterized by use of a priority queue with heuristic)
 * with a good heuristic it can be VERY efficient.
 */

int astarHeuristic(FringeNode *fn, void *data);

char *astar(Game *game)
{
    // we'll have our fringe act as a priority queue
    FringeNode *fringe = newQueue();
    
    // closed will store all the states we've already visited to avoid repeats
    HashTable *closed = newHashTable();

    // prepare state and values for first fringe node
    StateNode *startState = malloc(sizeof(StateNode));
    startState->loc = malloc(sizeof(Location));
    startState->loc->x = game->start->x; // <-Here
    startState->loc->y = game->start->y; // <-Here
    startState->action = 0;
    startState->cost = 0;
   
    char *startPath = "\0";
    int startCost = 0;
    
    // build fringe node and push it to the fringe
    FringeNode *first = newFringeNode(startState, startPath, startCost);

    // heuristic is a container that holds a reference to the game and a function.
    // the function returns a node's totalCost plus a computed 'heuristic' value for its state.
    // it is used to determine the priority of a node in the queue. this is the source of A*'s power.
    Heuristic *heur = malloc(sizeof(Heuristic));
    heur->heurfn = &astarHeuristic;
    heur->data = game;

    pushToQueueByHeuristic(first, heur, &fringe);

    // variables for book-keeping
    int expanded = 0;
    int n_items = 1; // for the first FringeNode
    int max_in_fringe = 1;
    
    // let's get goin!
    while(true)
    {
        // book-keeping
        max_in_fringe = max(max_in_fringe, n_items);

        // get next FringeNode in the queue
        FringeNode *fn = nextInQueue(&fringe);

        // if there was nothing there, we failed :/
        if (fn == NULL)
        {
            printf("No Solution found :(\n");

            // clean up
            free(heur);
            deleteQueue(&fringe);
            deleteHashTable(closed);

            return NULL;
        } 

        // book-keeping
        expanded += 1;
        n_items -= 1;

        // if this state's location is the winning state we win!
        if (sameLocation(fn->state->loc->x, fn->state->loc->y, game->goal->x, game->goal->y))
        {
            // take the path, and nullify reference to it from the FringeNode
            char *pathToVictory = fn->path;
            fn->path = NULL;

            // report stats
            printf("Total cost of solution: %d\n", fn->totalCost);
            printf("Total gamestates considered: %d\n", expanded);
            printf("Maximum bytes in fringe during search: %lu\n", max_in_fringe * sizeof(FringeNode));
            printf("Bytes in fringe at solution: %lu\n", n_items * sizeof(FringeNode));

            // clean up
            free(heur);
            deleteFringeNode(fn);
            deleteQueue(&fringe);
            deleteHashTable(closed);

            // return the glorious path to victory!
            return pathToVictory;

        } else { // if it wasn't the winning state we must keep searching
            
            // get a list of the neighboring gamestates
            List *successors = getSuccessorStateNodes(fn->state, game->board);

            // show actual type of list's items
            StateNode **items = successors->items;

            // create a new FringeNode for each appropriate state in the list
            for (int i = 0; i < successors->n_items; i += 1)
            {
                StateNode *successor = items[i];
                
                // a state is "appropriate if it hasn't already been explored
                if (!stateInHashTable(successor, closed))
                {
                    // add to state to closed list
                    addStateToHashTable(successor, closed);

                    // create a new FringeNode with new state and old FringeNode's path and totalCost
                    FringeNode *new = newFringeNode(successor, fn->path, fn->totalCost);

                    // add it to the fringe by heuristic
                    pushToQueueByHeuristic(new, heur, &fringe);
                   
                    // book-keeping 
                    n_items += 1;

                } else {

                    // the StateNode must be freed - it's useless now
                    free(successor->loc);
                    free(successor);
                }
            }

            // clean up our list that had contained the successors
            free(items); // successors->items
            free(successors);

            // we no longer need the old FringeNode  
            deleteFringeNode(fn);
        }
    } 
}

int astarHeuristic(FringeNode *fn, void *data)
{
    Game *game = data;
    return fn->totalCost + manhattanDistance(fn->state->loc->x, fn->state->loc->y, game->goal->x, game->goal->y);
}
