#include "cell.h"

Cell::Cell() {
	living = true;
	neighbors = 0;
}

Cell::Cell(char livNeighbors) {
	living = true;
	neighbors = livNeighbors;
}

void Cell::setLife(bool state) {
	living = state;
}