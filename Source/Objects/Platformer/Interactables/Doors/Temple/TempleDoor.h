#pragma once

#include "Objects/Platformer/Interactables/Doors/Portal.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;

class TempleDoor : public Portal
{
public:
	static TempleDoor* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTempleDoor;

protected:
	TempleDoor(cocos2d::ValueMap& properties);
	virtual ~TempleDoor();

	void initializePositions() override;

private:
	typedef Portal super;

	cocos2d::Sprite* door;
	cocos2d::Sprite* emblem;
	CollisionObject* topCollision;

	cocos2d::Vec2 emblemOffset;

	static const std::string MapKeyColor;
};
