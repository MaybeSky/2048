#include "SDLUtils.h"
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

extern const int SCREEN_WIDTH = 640;
extern const int SCREEN_HEIGHT = 480;

static SDL_Window *g_window = NULL;
static SDL_Renderer *g_renderer = NULL;

bool InitSDL()
{
	bool success = true;
	
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf("Warning: Linear texture filtering not enabled!\n");
		}

		g_window = SDL_CreateWindow(
			"SDL Tutorial",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		if(g_window == NULL) {
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
			if(g_renderer == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			}
			g_render.init(g_renderer);

			int imgFlags = IMG_INIT_PNG;
			if(!(IMG_Init(imgFlags) & imgFlags)) {
				printf("SDL_image could not initialize! SDL Error: %s\n", SDL_GetError());
				success = false;
			}

			if(TTF_Init() == -1) {
				printf("SDL_ttf could not initialize! TTF Error: %s\n", TTF_GetError());
				success = false;
			}
		}
	}

	return success;
}

void CloseSDL()
{
	SDL_DestroyRenderer(g_renderer);
	g_renderer = NULL;
	SDL_DestroyWindow(g_window);
	g_window = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

Render g_render;

const SDL_Color BLACK = { 0, 0, 0, 0 };
const SDL_Color WHITE = { 255, 255, 255, 255 };
