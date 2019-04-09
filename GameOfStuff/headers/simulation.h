#include "cell.h"
struct Simulation {
	Cell* board;

	Simulation(int xSize, int ySize);
	~Simulation();

	bool boundCheck(int x, int y);
	void getNeighbors(Cell &chosenOne, int x, int y);
	void executeTurn();
private:
	int boardSizeX, boardSizeY;
};
