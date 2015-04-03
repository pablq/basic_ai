Project Description: 

This program presents five basic search algorithms and provides basic data from each one.

The algorithms explored are:
1. Depth First Search
2. Breadth First Search
3. Uniform Cost Search
4. Greedy Search
5. A* Search.

The following information is presented for each algorithm:
1. Movement cost of path found.
2. Approximate computational time spent.
3. Approximate memory usage.

*All algorithm implementations make use of a closed set to avoid re-checking gamestates

to build: make
to run: ./basic_ai [-fn <dfs> <bfs> <ucs> <greedy> <astar>] [-w]

-w flag tells the program to use a weighted grid which creates varied movement costs. this is recommended. (default is no)
-fn followed by function names tells the program to only use the specified functions (default is all)
