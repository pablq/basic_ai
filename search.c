#include "game.h"
#include "grid.h"
#include "search.h"
#include "list.h"

/*

    List *fringe = malloc(sizeof(List));
    fringe->list = (FringeNode **) malloc(sizeof(FringeNode*) * 32);
    fringe->length = 32;
    
    StateNode *parent = PARENT NODE;

    List *successors = (List *) malloc(sizeof(List));
    successors->list = (StateNode **) malloc(sizeof(StateNode *) * 4);
    successors->length = 4;

    List *successors = getSuccessors(successors, parent, game);

    for (int i = 0; i < successors->length; i += 1)
    {
        FringeNode fringeNode = malloc(sizeof(FringeNode));

        Successor *successor = successors[i]; 

        fringeNode->StateNode = successor;
        fringeNode->allActions = lastFringeNode + successor->action;
        fringeNode->costOfActions = lastFringeNode->costOfActions + successor->cost;

        *** THIS IS WHERE CODE GOES TO RESIZE myList ***
        fringe->list[i] = fringeNode;
    }

    free(successors);

    typedef struct FringeNode
    {
        StateNode *state;
        char *allActions;
        int costOfActions;
    }
*/

char *dfs (Game *game)
{
    List *fringe = 
    Stack *fringe = newStack();

    Set *closed = newHashTable();
    Node *first = firstNode(game);
   
    addNodeToFringe((first, [first->action]));

    while(true)
    {
        Node* thisNode = fringe.pop();

        if thisNode = null {
            return NULL;
        } 
        if (isWin(thisNode->state->location)) {
            return thisNode->actions;
        }

        else {
            List *list = getSuccessorNodes(*thisNode, game);

            for each in list:

                if (each->location not in closed):
                    closed.add(each->location);
                    fringe.push((each, [thisNode->actions + each->action]));
        }
    } 
}
