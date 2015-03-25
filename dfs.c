#include "game.h";
#include "grid.h";

char *dfs (Game *game)
{
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
