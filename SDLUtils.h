#ifndef SdlUtils_h
#define SdlUtils_h

#include <SDL.h>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

extern bool InitSDL();
extern void CloseSDL();

extern const SDL_Color BLACK;
extern const SDL_Color WHITE;

class Render
{
public:
	void init(SDL_Renderer *renderer) { m_renderer = renderer; }

	void setDrawColor(int r, int g, int b, int a = 255)
	{
		SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
	}
	void setDrawColor(const SDL_Color &color)
	{
		SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	}

	void clear() { SDL_RenderClear(m_renderer); }

	void drawRect(int x, int y, int w, int h)
	{
		SDL_Rect rect = { x, y, w, h };
		SDL_RenderDrawRect(m_renderer, &rect);
	}

	void present() { SDL_RenderPresent(m_renderer); }

private:
	SDL_Renderer *m_renderer;
};
extern Render g_render;

#endif
