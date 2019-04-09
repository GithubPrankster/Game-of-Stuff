#include "simulation.h"
#include <random>

Simulation::Simulation(int xSize, int ySize) {
	board = new Cell[xSize * ySize];
	
	boardSizeX = xSize;
	boardSizeY = ySize;

	std::random_device device;
	std::mt19937 twister(device());
	std::uniform_int_distribution<int> distribution(0, 3);
	for (int x = 0; x < xSize; x++) {
		for (int y = 0; y < ySize; y++) {
			Cell& chosenOne = board[y * boardSizeX + x];

			int randomFlip = distribution(twister);
			bool coinFlip = randomFlip == 1 ? true : false;

			chosenOne.setLife(coinFlip);
		}
	}
}

Simulation::~Simulation() {
	delete board;
}

bool Simulation::boundCheck(int x, int y) {
	return (x > boardSizeX || y > boardSizeY || x < 0 || y < 0);
}

void Simulation::getNeighbors(Cell& chosenOne, int x, int y) {
	struct Vec2 {
		int x;
		int y;
		Vec2(int z, int w) : x(z), y(w){}
	};

	Vec2 dirs[]{
		Vec2((x - 1), y),
		Vec2((x + 1), y),
		Vec2(x, (y - 1)),
		Vec2(x, (y + 1)),
		Vec2((x + 1), (y - 1)),
		Vec2((x - 1), (y + 1)),
		Vec2((x - 1), (y - 1)),
		Vec2((x + 1), (y + 1))
	};

	for(Vec2 dir : dirs) {
		if (boundCheck(dir.x, dir.y) && board[dir.y * boardSizeX + dir.x].living) {
			chosenOne.neighbors++;
		}
		else if (boundCheck(dir.x, dir.y) && !board[dir.y * boardSizeX + dir.x].living) {
			chosenOne.neighbors--;
			if (chosenOne.neighbors < 0)
				chosenOne.neighbors = 0;
		}
	}
}

void Simulation::executeTurn() {
	Cell* nextBoard = board;
	for (int x = 0; x < boardSizeX; x++) {
		for (int y = 0; y < boardSizeY; y++) {
			Cell& chosenOne = nextBoard[y * boardSizeX + x];
			getNeighbors(chosenOne, x, y);

			if (chosenOne.neighbors < 2 || chosenOne.neighbors > 3) {
				chosenOne.setLife(false);
			}

			if (chosenOne.living == false && chosenOne.neighbors == 3) {
				chosenOne.setLife(true);
			}
		}
	}
	board = nextBoard;
}