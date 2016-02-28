#include <stdio.h>
#include "SDLUtils.h"
#include "Tile.h"
#include "Render.h"

Tile *one;

void Frame(int delta_ms)
{
	g_render.setDrawColor(WHITE);
	g_render.clear();

	g_render.setDrawColor(BLACK);
	g_render.drawRect(0, 10, 100, 100);
	g_render.drawRect(400, 10, 100, 100);

	one->render();

	g_render.present();

	one->update(delta_ms);
}

int main(int argc, char *argv[])
{
	auto anim1 = std::make_shared<Animation>(500, TMFUNC_EASE);
	auto t1 = anim1->createTransition(1);
	t1->add(0, 0.0);
	t1->add(50, 1.2 * 400);
	t1->add(100, 400.0);

	if (!InitSDL())
		return 1;

	Tile_LoadMetaData();

	one = new Tile(64);

	SDL_Event e;
	Uint32 ticks = SDL_GetTicks();
	for(;;) {
		while(SDL_PollEvent(&e)) {
			if(e.type == SDL_QUIT)
				goto quit;
			else if(e.type == SDL_KEYDOWN)
				one->attachAnimation(anim1);
		}

		Uint32 new_ticks = SDL_GetTicks();
		int delta = new_ticks - ticks;
		ticks = new_ticks;
		Frame(delta);
	}

quit:
	Tile_UnloadMetaData();

	CloseSDL();

	return 0;
}
