Project Description:

This program is intended to be run from the command line and does all of its activity in the terminal.
It will demonstrate various search algorithms and their relative efficiency.
The algorithms explored will be depth first search, breadth first search, and astar search.
The efficiency of the algorithms will be determined by:
    - path found
    - computational time spent searching
    - amount of memory used

TODO:
1. implement search algorithms (start with dfs);
    -> we have to implement hash table (closed set) and stack (fringe)
    -> otherwise, we should have all the tools we need.
1. build SearchAgent with logic to open gamestates and check if that gamestate == win.
    - I'll have to think up efficeint logic to extend char arrays by one char only. it might be worth creating a new struct that holds the 
        array's length and a pointer the array itself.
2. implement search functions that return a list of directions
    - they are given access to the problem? and the game? or the agent? (still to be determined)
    - WILL BE GRAPH SEARCH -> i'll store already explored states in a hash table (with linked list?)
3. implement in basic_ai.c a situation where an agent is given a game and plays it using a,b, or c search algorithm.
    this will be 'main' 
        -> we create game
        -> we pass to search function (char algorithm, Game *game)
        -> search function chooses it's algorithm based on the char passed in (algorithms live as pointers to functions);
        -> algorithm gets game and returns a string of actions.
        -> we then play game with the string of action
        -> we're happy
                            
4. DONT FORGET TO FREE MEMORY USED (bust out valgrind)

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
