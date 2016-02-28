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
	explicit Tile(int value);
	void render();
	void update(int delta_ms);
	virtual void setProperty(int propertyID, double value) override;
	void attachAnimation(std::shared_ptr<Animation> animation);

private:
	int m_x;
	int m_y;
	std::shared_ptr<AnimationExecutor> m_animationExecutor;
	Texture m_texture;
};

#endif
