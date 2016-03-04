#ifndef ScoreBoard_h
#define ScoreBoard_h

#include "Texture.h"
#include "Font.h"

class ScoreBoard
{
public:
	explicit ScoreBoard(const char *title, int score);
	void render(int x, int y);
	void updateScore(int newScore) { m_score = newScore; }

	int width() { return 130; }
	int height() { return 70; }

private:
	const char *m_title;
	int m_score;
	Font m_numberFont;
	Font m_titleFont;
};

#endif
