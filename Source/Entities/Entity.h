#pragma once
#include "cocos2d.h"
#include "Resources.h"

using namespace cocos2d;

class Entity : public Node
{
public:
	Entity();
	~Entity();

	float GetWidth();
	float GetHeight();

	void onEnter() override;
	void update(float) override;

protected:
	PhysicsBody * physicsBody;
	Sprite * sprite;
};

