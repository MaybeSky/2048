#include "TileBoard.h"
#include "Render.h"
#include "Game.h"

TileBoard::TileBoard(Game *pGame)
	: m_pGame(pGame)
{
}

void TileBoard::render()
{
	// [TODO] refactor
	int tileSize = 100;
	int gridSpacing = 15;

	const int gridsSize = tileSize * m_pGame->m_size + gridSpacing * (m_pGame->m_size + 1);
	g_render.setDrawColor(0xBB, 0xAD, 0xA0);
	g_render.fillRect(m_x, m_y, gridsSize, gridsSize);

	Texture holder;
	holder.createBlank(tileSize, tileSize, SDL_TEXTUREACCESS_TARGET);
	holder.enableAlpha();
	g_render.setTarget(holder.sdl_texture());
	g_render.setDrawColor(238, 228, 218, static_cast<int>(0.35 * 255));
	g_render.clear();
	g_render.setTarget(nullptr);

	for(int row = 0; row < m_pGame->m_size; row++) {
		for(int col = 0; col < m_pGame->m_size; col++) {
			holder.render(
				m_x + gridSpacing + col * (tileSize + gridSpacing),
				m_y + gridSpacing + row * (tileSize + gridSpacing));
		}
	}

	auto renderTile = [&] (Tile *t) { t->render(m_x + gridSpacing, m_x + gridSpacing); };
	m_pGame->forEachTile(renderTile);
}
