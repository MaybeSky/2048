#ifndef Tile_h
#define Tile_h

#include "Animation.h"
#include <memory>
#include <iostream>

class Tile : public AnimationTarget
{
public:
	Tile() : m_x(0), m_y(10) { }
	void render();
	void update(int delta_ms);
	virtual void setProperty(int propertyID, double value) override;
	void attachAnimation(std::shared_ptr<Animation> animation)
	{
		m_animationExecutor = std::make_shared<AnimationExecutor>(animation, this);
		m_animationExecutor->init();
	}

private:
	int m_x;
	int m_y;
	std::shared_ptr<AnimationExecutor> m_animationExecutor;
};

#endif
