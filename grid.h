typedef char Grid[WIDTH][HEIGHT]; 

void buildLayout(Grid* grid);

void printGrid(Grid *grid);

void placeGoal(Location *goal, Grid *grid);

void placeAgent(Location *agent, Grid *grid);
