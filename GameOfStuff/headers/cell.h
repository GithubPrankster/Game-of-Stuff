struct Cell {
	bool living;
	char neighbors;

	Cell();
	Cell(char livNeighbors);

	void setLife(bool state);
};