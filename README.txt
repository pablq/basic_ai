Project Description: 
This program is intended to be run from the command line and does all of its activity in the terminal.
It will demonstrate various search algorithms and their relative efficiency.
The algorithms explored will be depth first search, breadth first search, uniform cost search, and astar search.
The efficiency of the algorithms will be determined by:
    - path found
    - computational time spent searching
    - amount of memory used

TODO:
1. VALGRIND THE SHIT OUT OF THE PROGRAM -> FIX ERRORS AND LEAKS
    ^ this includes cleaning up the mess you made tonight with unneccessary functions.
2. Implement the other search algorithms
    ^ this includes activating the movement costs
    ^ brush up on heuristic functions (make it a simple one)
3. CREATE A MAKEFILE YOU LAZY SLAG
4. Show all your friends.

SINCE I'M STILL SLACKING ON MAKEFILE (omit the -g if you don't want to debug):
gcc -std=c99 -g -o exe/basic_ai basic_ai.c game.c grid.c util.c searchhelper.c search.c list.c location.c hashtable.c
