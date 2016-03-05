#ifndef Game_h
#define Game_h

#include "Tile.h"
#include <vector>
#include <functional>
#include <random>
#include <memory>
#include "ScoreBoard.h"
#include "ScoreAddition.h"
#include "TileBoard.h"

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
	void restart();
	void move(Dir dir);

	void render();
	void update(int delta_ms);

	ScoreBoard *curScoreBoard() { return m_curScoreBoard; }
	ScoreBoard *bestScoreBoard() { return m_bestScoreBoard; }
	TileBoard *tileBoard() { return m_tileBoard; }

	bool gameOver() { return m_gameOver; }

	friend void debugPrintGrids(Game *g);
private:
	std::default_random_engine m_random_engine;
	int m_size;
	Tile **m_cells;
	bool m_gameOver;
	int m_score;
	int m_bestScore;
	
	ScoreBoard *m_curScoreBoard;
	ScoreBoard *m_bestScoreBoard;
	std::shared_ptr<ScoreAddition> m_scoreAddition;
	friend class TileBoard;
	TileBoard *m_tileBoard;

	std::vector<int> getAvailableCells();
	void addRandomTile();
	bool movesAvailable();
	void forEachTile(std::function<void (Tile *)> callback);
	void fill(Dir dir, int a, int b, int *pRow, int *pCol);
	void reduce(const std::vector<int> &mapping, bool *pMoved, int *pDeltaScore);
};

#endif
