#include <stdio.h>
#include <vector>
#include "SDLUtils.h"
#include "Tile.h"
#include "Render.h"
#include "Game.h"

#include <algorithm>
#include <math.h>

Game g;

void Frame(int delta_ms)
{
	g_render.setDrawColor(WHITE);
	g_render.clear();

	g.renderTileBoard(2, 2);
	g.m_curScoreBoard->render(480, 0);
	g.m_bestScoreBoard->render(480, 80);

	g_render.present();

	g.update(delta_ms);
}

int main(int argc, char *argv[])
{
	if (!InitSDL())
		return 1;

	g.init(4);

	Tile_LoadMetaData();

	g.addRandomTile();
	g.addRandomTile();

	SDL_Event e;
	Uint32 ticks = SDL_GetTicks();
	for(;;) {
		while(SDL_PollEvent(&e)) {
			if(e.type == SDL_QUIT)
				goto quit;
			else if(e.type == SDL_KEYDOWN) {
				switch(e.key.keysym.sym) {
				case SDLK_UP:
					g.move(UP);
					break;
				case SDLK_RIGHT:
					g.move(RIGHT);
					break;
				case SDLK_DOWN:
					g.move(DOWN);
					break;
				case SDLK_LEFT:
					g.move(LEFT);
					break;
				}
			}
		}

		Uint32 new_ticks = SDL_GetTicks();
		int delta = new_ticks - ticks;
		ticks = new_ticks;
		Frame(delta);
	}

quit:

	Tile_UnloadMetaData();

	g.quit();

	CloseSDL();

	return 0;
}
