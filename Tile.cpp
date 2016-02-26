#include "Tile.h"
#include "SDLUtils.h"
#include <iostream>

void Tile::render()
{
	g_render.setDrawColor(255, 127, 0);
	g_render.fillRect(m_x, m_y, 100, 100);
}

void Tile::setProperty(int propertyID, double value)
{
	switch(propertyID) {
	case 1:
		m_x = value;
		break;
	}
}

void Tile::update(int delta_ms)
{
	if(m_animationExecutor) {
		m_animationExecutor->progress(delta_ms);
	}
}
