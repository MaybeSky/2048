#include "Game.h"
#include <ctime>
#include <utility> // move
#include <algorithm> // for_each

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
	for(int i = 0; i < len; i++) {
		m_cells[i] = nullptr;
	}

	m_random_engine.seed(static_cast<unsigned long>(time(nullptr)));
}

std::vector<Vector> Game::getAvailableCells()
{
	std::vector<Vector> availableCells;
	for(int row = 0; row < m_size; row++) {
		for(int col = 0; col < m_size; col++) {
			if(refCell(row, col) == nullptr) {
				availableCells.push_back(Vector(row, col));
			}
		}
	}
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

	Tile *tile = new Tile(cell.row, cell.col, value);
	tile->attachAnimation(tileAppearAnimation);
	refCell(cell.row, cell.col) = tile;
}

void Game::forEachTile(std::function<void (Tile *)> callback)
{
	for(int row = 0; row < m_size; row++) {
		for(int col = 0; col < m_size; col++) {
			if(refCell(row, col) != nullptr) {
				callback(refCell(row, col));
			}
		}
	}
}

void debugPrintGrids(Game *g)
{
	for(int row = 0; row < g->m_size; row++) {
		for(int col = 0; col < g->m_size; col++) {
			Tile *t = g->refCell(row, col);
			printf(" %d", t ? t->value() : 0);
		}
		putchar('\n');
	}
}

void Game::move(Dir dir)
{
	forEachTile([] (Tile *tile) { tile->clearMergedFrom(); });

	Vector dirVec = getVector(dir);

	std::vector<int> rowTraversals, colTraversals;
	buildTraversals(dirVec, rowTraversals, colTraversals);

	bool moved = false;
	std::for_each(rowTraversals.begin(), rowTraversals.end(), [&] (int row) {
		std::for_each(colTraversals.begin(), colTraversals.end(), [&] (int col) {
			Tile *tile = refCell(row, col);
			if(tile != nullptr) {
				Vector lastBlankPos, nextPos;
				findFarthestPosition(tile->row(), tile->col(), dirVec, lastBlankPos, nextPos);

				Tile *nextTile = withInBounds(nextPos.row, nextPos.col)
					? refCell(nextPos.row, nextPos.col)
					: nullptr;
				if(nextTile != nullptr && nextTile->value() == tile->value()
					&& !nextTile->hasMergedFrom())
				{
					refCell(tile->row(), tile->col()) = nullptr;

					tile->planMovement(nextPos);

					Tile *newTile = new Tile(nextPos.row, nextPos.col, tile->value() * 2);
					newTile->setMergedFrom(tile, nextTile);
					newTile->attachAnimation(tilePopAnimation);

					refCell(newTile->row(), newTile->col()) = newTile;

					moved = true;
					printf("moved: row=%d col=%d\n", nextTile->row(), nextTile->col());
				}
				else
				{
					if(!lastBlankPos.equalsTo(Vector(row, col))) {
						refCell(tile->row(), tile->col()) = nullptr;
						tile->planMovement(lastBlankPos);
						refCell(lastBlankPos.row, lastBlankPos.col) = tile;
						moved = true;
					}
				}
			}
		});
	});

	if(moved) {
		addRandomTile();
	}
}

Vector Game::getVector(Dir dir)
{
	static Vector map[] = {
		Vector(-1, 0), // up
		Vector(0, 1),  // right
		Vector(1, 0),  // down
		Vector(0, -1)  // left
	};
	return map[dir];
}

void Game::buildTraversals(Vector vec, std::vector<int> &rowTraversals, std::vector<int> &colTraversals)
{
	for(int i = 0; i < m_size; i++) {
		colTraversals.push_back(i);
		rowTraversals.push_back(i);
	}
	if(vec.row == 1) { std::reverse(rowTraversals.begin(), rowTraversals.end()); }
	if(vec.col == 1) { std::reverse(colTraversals.begin(), colTraversals.end()); }
}

void Game::findFarthestPosition(int rowFrom, int colFrom, Vector dirVec,
	Vector &farthest, Vector &next)
{
	// Progress towards the vector direction until an obstacle is found
	Vector cell(rowFrom, colFrom);
	Vector prev;

	do {
		prev = cell;
		cell = prev.addNew(dirVec);
	} while(withInBounds(cell.row, cell.col) && refCell(cell.row, cell.col) == nullptr);

	farthest = prev;
	next = cell; // Used to check if a merge is required
}

void Game::test1()
{
	auto addTile = [&] (int row, int col, int value) { 
		Tile *tile = new Tile(row, col, value);
		tile->attachAnimation(tileAppearAnimation);
		refCell(row, col) = tile;
	};
	addTile(0, 0, 2);
	addTile(1, 0, 2);
	addTile(3, 0, 4);
}

void Game::test2()
{
	refCell(0, 0)->planMovement(Vector(3, 0));
	refCell(1, 0)->planMovement(Vector(3, 0));
}
