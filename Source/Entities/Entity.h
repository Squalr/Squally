#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Collision/CollisionObject.h"

using namespace cocos2d;

class Entity : public Node
{
public:
	float GetWidth();
	float GetHeight();

protected:
	Entity();
	~Entity();

	void onEnter() override;
	void update(float) override;

	CollisionObject * collisionObject;
	Sprite * sprite;
};

