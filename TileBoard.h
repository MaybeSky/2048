#ifndef TileBoard_h
#define TileBoard_h

#include "Tile.h"

class Game;
class TileBoard
{
public:
	explicit TileBoard(Game *pGame);
	void render();

	void setXY(int x, int y) { m_x = x; m_y = y; }

private:
	Game *m_pGame;
	int m_x;
	int m_y;
};

#endif
