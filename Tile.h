#ifndef Tile_h
#define Tile_h

#include "Animation.h"
#include <memory>
#include "Texture.h"

extern void Tile_LoadMetaData();
extern void Tile_UnloadMetaData();

class Tile : public AnimationTarget
{
public:
	explicit Tile(int row, int col, int value);
	void render();
	void update(int delta_ms);
	virtual void setProperty(int propertyID, double value) override;
	void attachAnimation(std::shared_ptr<Animation> animation);

	int row() { return m_row; }
	int col() { return m_col; }

private:
	int m_x;
	int m_y;
	int m_row;
	int m_col;
	double m_opacity;
	double m_scale;
	std::shared_ptr<AnimationExecutor> m_animationExecutor;
	Texture m_texture;
};

#endif
