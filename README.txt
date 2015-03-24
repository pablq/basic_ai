Project Description:

This program is intended to be run from the command line and does all of its activity in the terminal.
It will demonstrate various search algorithms and their relative efficiency.
The algorithms explored will be depth first search, breadth first search, and astar search.
The efficiency of the algorithms will be determined by:
    - path found
    - computational time spent searching
    - amount of memory used

TODO:
1. Build logic for exploring hypothetical game states (getSuccessorState, getSuccessorNode)
    - Game has grid, start loc, goal loc, agent loc, (and will have isWin function?)
    - In this case it's feasible for my model to be an actual copy of the game.
        -> i can expose a few functions in the api to use in the problem.
    - But, what is the absolute minimum i can use for my gameState?
        -> i definitely need the grid, i need the agent's location, i need a goal check.
            ^ i should just use a copy of the game struct
        -> it would be helpful tto have the moveagent function too.
        -> i WONT need play.
    - I'll try to keep problem simple (i'll have access to a copy of the game that i can modify, but i won't duplicate it (i just care about walls and goal))
        -> getLegalActions(Location) returns [legal actions \0]
        -> getSuccessorState(action, this_node) returns NODE
        -> NODE consists of { Location, [actions taken to get here \0] }... what else? i don't think anything
            ^ i'd rather not have to copy the game for each successor state.
            ^ i just need to be able to check for legal moves and isWin per location.
    - if game->isWin() checks it's own member's, i can just modify my fake game's agent location and check it. that way i can use the game's
        actual mechanics without re-implementing.
    - the Problem might be able to just live in the search agent to keep things simpler.
2. build SearchAgent with logic to open gamestates and check if that gamestate == win.
    - I'll have to think up efficeint logic to extend char arrays by one char only. it might be worth creating a new struct that holds the 
        array's length and a pointer the array itself.
3. implement search functions that return a list of directions
    - they are given access to the problem? and the game? or the agent? (still to be determined)
    - WILL BE GRAPH SEARCH -> i'll store already explored states in a hash table (with linked list?)
4. implement in basic_ai.c a situation where an agent is given a game and plays it using a,b, or c search algorithm.
    this will be 'main'
5. DONT FORGET TO FREE MEMORY USED (bust out valgrind)

!!!!!!!!!!!!!!!

OH OH OH OH -> TO IMPLEMENT COST FOR LOCATIONS... I CAN HAVE THE GAME GRID HAVE ALL LEGAL SPACES ACTUALLY BE ONLY NUMBERS. THE PRINT GRID FUNCTION
CAN TRANSLATE ALL 0'S (WALLS TO X'S)

I'LL NEED A MORE ROBUST PRINT GRID FUNCTION THAT GAME WILL IMPLEMENT... IT'LL MODIFY A COPY OF IT'S GRID (DRAWING IN START, AGENT, GOAL, AND PATH)
THEN PASS THE ADDRESS OF THE COPY TO PRINTGRID. WHEN FUNCTION RETURNS. THE REAL GAME GRID WILL STILL BE JUST NUMBERS BUT THE USER SEES MEANINGFUL SYMBOLS
FOR THE GAME'S MEMBERS -> THEY'RE ALL STORED IN GAME ANYWAYS!!!

^ I implemented the above, BUT, instead of having a temporary grid, i just gave the game two grids -> one that is the board which does not change and
holds all of the movement costs... and 'display' which is drawn.

!!!!!!!!!!!!!

Rough CS188 structure: (FOR REFERENCE)
- There's a GAME which is the environment for the exercise, and is what will execute the movements of the AGENT
    -> provides a Start State
    -> provides and recognizes a Goal State
    -> provides mechanics for actually progressing game state
- There's a PROBLEM
    -> has a Model of the Game in which hypothetical states can be explored
    -> provides to the AGENT a function that returns a hypothetical state
    -> recognizes a Goal State
    -> recognizes and adheres to GAME mechanics
- There's an AGENT which makes use of a SEARCH ALGORITHM and acts within a GAME
- There's a SEARCH ALGORITHM makes use of the PROBLEM and returns a list of directions
    -> the directions bring the AGENT from the Start State to the Goal State
