Project Description:

This program is intended to be run from the command line and does all of its activity in the terminal.
It will demonstrate various search algorithms and their relative efficiency.
The algorithms explored will be depth first search, breadth first search, and astar search.
The efficiency of the algorithms will be determined by:
    - path found
    - computational time spent searching
    - amount of memory used

TODO:
1. Build container grid for game in which to run algorithms.
    - Generate grid (of size ?)
    - Generate grid with exterior walls
    - Generate grid with exterior walls, Agent location, and Goal location
    - Generate grid with exterior walls, interior walls, Agent location, and Goal location
2. Build logic for moving agent / advancing game state
    - Function to determine legal moves (accepts Agent loc, direction)
    - Function to actually move Agent (change val at new loc, change val at former loc)
        -> Accepts a direction and Agent location
    - Agent move advances game one tick
    - Agent moves fed as an array of directions
    - Random functions required:
        -> check for end game
        -> find the agent
        -> find the squares adjacent to agent
        -> find the goal
3. Build logic for exploring hypothetical game states (getSuccessorState, getSuccessorNode)
    - Gamestate consists of full grid? ACTUALLY, maybe we just need the agent's location?! 
    - This will be the hard part. A LOT more detail is required.
4. Much more, I have enough to work on for now. 
    - Building the Grid and Game mechanics is first priority and plenty for now.

CS188 structure:
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
