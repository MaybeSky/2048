#ifndef Game_h
#define Game_h

#include "Tile.h"
#include <vector>
#include <functional>
#include <random>

enum Dir
{
	/* do not change the order here */
	UP, DOWN, LEFT, RIGHT
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

	std::vector<int> getAvailableCells();
	void fill(Dir dir, int a, int b, int *pRow, int *pCol);
	void reduce(const std::vector<int> &mapping, bool *pMoved);
	void moveTile(Tile *tile, Vector pos) { /* todo */ }
};

#endif
