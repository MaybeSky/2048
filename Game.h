#ifndef Game_h
#define Game_h

#include "Tile.h"
#include <vector>
#include <functional>
#include <random>
#include <memory>
#include "ScoreBoard.h"
#include "ScoreAddition.h"

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
	void quit();
	void addRandomTile();
	void forEachTile(std::function<void (Tile *)> callback);
	void move(Dir dir);

	void render();
	void renderTileBoard(int x, int y);
	void update(int delta_ms);

	friend void debugPrintGrids(Game *g);

	void test1();
	void test2();

	bool gameOver() { return m_gameOver; }

	ScoreBoard *m_curScoreBoard;
	ScoreBoard *m_bestScoreBoard;
	std::shared_ptr<ScoreAddition> m_scoreAddition;
private:
	std::default_random_engine m_random_engine;
	int m_size;
	Tile **m_cells;
	bool m_gameOver;
	int m_score;
	int m_bestScore;

	std::vector<int> getAvailableCells();
	bool movesAvailable();
	void fill(Dir dir, int a, int b, int *pRow, int *pCol);
	void reduce(const std::vector<int> &mapping, bool *pMoved, int *pDeltaScore);
};

#endif
