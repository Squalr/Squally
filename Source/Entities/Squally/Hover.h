#pragma once
#include "cocos2d.h"

#include "Engine/Input/InputManager.h"
#include "Entities/Entity.h"
#include "Objects/Hackables/HackableObject.h"
#include "Resources.h"

using namespace cocos2d;

class Hover : public HackableObject
{
public:
	static Hover * create(Entity* initParent);

	void setContactBeginCallback(std::function<bool(CollisionData)>);
	void setContactUpdateCallback(std::function<bool(CollisionData)>);
	void setContactEndCallback(std::function<bool(CollisionData)>);

	void setHeight(float height);
	void setMaxHeight(float maxHeight);
	void setFloatDelta(float delta);

protected:
	bool contactBegin(CollisionData data) override;
	bool contactUpdate(CollisionData data) override;
	bool contactEnd(CollisionData data) override;

private:
	Hover(Entity* initParent);
	~Hover();

	void update(float) override;

	std::function<bool(CollisionData)> contactBeginCallback;
	std::function<bool(CollisionData)> contactUpdateCallback;
	std::function<bool(CollisionData)> contactEndCallback;
	Entity* parent;

	const float hoverHeight = 96.0f;
};
