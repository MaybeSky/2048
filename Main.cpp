#include <stdio.h>
#include <vector>
#include "SDLUtils.h"
#include "Tile.h"
#include "ScoreAddition.h"
#include "Render.h"
#include "Game.h"
#include "Button.h"

#include <algorithm>
#include <math.h>

Game g;
Button *newGameBtn;

void Frame(int delta_ms)
{
	g_render.setDrawColor(WHITE);
	g_render.clear();

	g.render();
	newGameBtn->render();

	g_render.present();

	g.update(delta_ms);
	newGameBtn->update(delta_ms);
}

int main(int argc, char *argv[])
{
	if (!InitSDL())
		return 1;

	Tile_LoadMetaData();
	TileBoard_loadMetaData();
	ScoreAddition_loadMetaData();
	Button_loadMetaData();

	newGameBtn = new Button("New Game", [] { g.restart(); });
	newGameBtn->setXY(480, 200);

	g.init(4);

	g.curScoreBoard()->setXY(480, 20);
	g.bestScoreBoard()->setXY(480, 100);
	g.tileBoard()->setXY(2, 2);

	SDL_Event e;
	Uint32 ticks = SDL_GetTicks();
	for(;;) {
		while(SDL_PollEvent(&e)) {
			newGameBtn->handleEvent(e);

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

	g.quit();

	free(newGameBtn);

	Button_unloadMetaData();
	ScoreAddition_unloadMetaData();
	TileBoard_unloadMetaData();
	Tile_UnloadMetaData();

	CloseSDL();

	return 0;
}
