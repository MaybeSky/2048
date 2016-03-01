#ifndef Game_h
#define Game_h

#include "Tile.h"
#include <vector>
#include <functional>
#include <random>

enum Dir
{
	UP, RIGHT, DOWN, LEFT
};

class Game
{
public:
	Game();
	~Game();
	void init(int size);
	void addRandomTile();
	void forEachTile(std::function<void (Tile *)> callback);
	void move(Dir dir);

	friend void debugPrintGrids(Game *g);

	void test1();
	void test2();

private:
	std::default_random_engine m_random_engine;
	int m_size;
	Tile **m_cells;

	Tile *&refCell(int row, int col) { return m_cells[row * m_size + col]; }
	bool withInBounds(int row, int col) {
		return row >= 0 && col >= 0 && row < m_size && col < m_size;
	}
	std::vector<Vector> getAvailableCells();
	Vector getVector(Dir dir);
	void buildTraversals(Vector vec, std::vector<int> &rowTraversals, std::vector<int> &colTraversals);
	void findFarthestPosition(int rowFrom, int colFrom, Vector dirVec,
		Vector &farthest, Vector &next);
	void moveTile(Tile *tile, Vector pos) { /* todo */ }
};

#endif
