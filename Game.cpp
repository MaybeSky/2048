#include "Game.h"
#include <ctime>
#include <utility> // move
#include <algorithm> // fill

Game::Game()
{
	m_cells = nullptr;
}

Game::~Game()
{
	if(m_cells)
		delete m_cells;
}

void Game::init(int size)
{
	m_size = size;

	int len = size * size;
	m_cells = new Tile*[len];
	std::fill(m_cells, m_cells + len, nullptr);

	m_random_engine.seed(static_cast<unsigned long>(time(nullptr)));
}

std::vector<int> Game::getAvailableCells()
{
	std::vector<int> availableCells;
	for(int i = 0; i < m_size * m_size; i++)
		if(m_cells[i] == nullptr)
			availableCells.push_back(i);

	return std::move(availableCells);
}

void Game::addRandomTile()
{
	auto availableCells = getAvailableCells();
	if(availableCells.empty())
		return;

	std::uniform_int_distribution<int> u1(0, availableCells.size() - 1);
	auto cell = availableCells[u1(m_random_engine)];

	std::bernoulli_distribution u2(0.9);
	int value = u2(m_random_engine) ? 2 : 4;

	Tile *tile = new Tile(cell / m_size, cell % m_size, value);
	tile->attachAnimation(tileAppearAnimation);
	m_cells[cell] = tile;
}

void Game::forEachTile(std::function<void (Tile *)> callback)
{
	for(int i = 0; i < m_size * m_size; i++)
		if(m_cells[i] != nullptr)
			callback(m_cells[i]);
}

void debugPrintGrids(Game *g)
{
	for(int row = 0; row < g->m_size; row++) {
		for(int col = 0; col < g->m_size; col++) {
			Tile *t = g->m_cells[row * g->m_size + col];
			printf(" %d", t ? t->value() : 0);
		}
		putchar('\n');
	}
}

void Game::fill(Dir dir, int a, int b, int *pRow, int *pCol)
{
	if(dir % 2 == 1)
		b = m_size - 1 - b;

	if(dir / 2 == 1)
		*pRow = a, *pCol = b;
	else
		*pRow = b, *pCol = a;
}

void Game::reduce(const std::vector<int> &mapping, bool *pMoved)
{
	bool moved = false;
	int n = -1; // fill pointer
	int first = -1; // search pointer
	bool prevMerged = false;

	for(;;) {
		while(++first < m_size)
			if(m_cells[mapping[first]] != nullptr)
				break;

		if(first == m_size)
			break;

		if(!prevMerged && n >= 0 && m_cells[mapping[n]] != nullptr
			&& m_cells[mapping[n]]->value() == m_cells[mapping[first]]->value())
		{
			Tile *a = m_cells[mapping[n]];
			Tile *b = m_cells[mapping[first]];

			// add move animation to B
			b->planMovement(Vector(mapping[n] / m_size, mapping[n] % m_size));

			// pop the merged tile
			Tile *m = new Tile(a->row(), a->col(), a->value() * 2);
			m->setMergedFrom(a, b);
			m->attachAnimation(tilePopAnimation);
			m_cells[mapping[n]] = m;

			// remove A, B
			m_cells[mapping[first]] = nullptr;
			prevMerged = true;
			moved = true;
		}
		else
		{
			if(++n < first)
			{
				Tile *t = m_cells[mapping[first]];
				t->planMovement(Vector(mapping[n] / m_size, mapping[n] % m_size));
				m_cells[mapping[first]] = nullptr;
				m_cells[mapping[n]] = t;
				moved = true;
			}
			prevMerged = false;
		}
	}
	*pMoved = moved;
}

void Game::move(Dir dir)
{
	// [FIXED] ensure their animation have ended
	forEachTile([] (Tile *tile) { tile->clearMergedFrom(); });

	bool moved = false;

	std::vector<int> mapping;

	for(int i = 0; i < m_size; i++) {
		mapping.clear();
		for(int j = 0; j < m_size; j++) {
			int row, col;
			fill(dir, i, j, &row, &col);
			mapping.push_back(row * m_size + col);
		}
		bool m;
		reduce(mapping, &m);
		moved |= m;
	}

	if(moved) {
		addRandomTile();
	}
}

void Game::test1()
{
}

void Game::test2()
{

}