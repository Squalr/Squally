#pragma once
#include "cocos2d.h"

#include "Engine/Physics/CollisionObject.h"
#include "Entities/Platformer/PlatformerEntity.h"

using namespace cocos2d;

class Hover : public CollisionObject
{
public:
	static Hover * create(PlatformerEntity* initParent);

	void setHeight(float height);
	void setMaxHeight(float maxHeight);
	void setFloatDelta(float delta);

private:
	Hover(PlatformerEntity* initParent);
	~Hover();

	void update(float) override;

	PlatformerEntity* parent;

	const float hoverHeight = 96.0f;
};
