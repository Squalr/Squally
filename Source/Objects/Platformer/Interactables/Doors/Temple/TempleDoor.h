#pragma once

#include "Objects/Platformer/Interactables/Doors/Portal.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class SmartClippingNode;
class WorldSound;

class TempleDoor : public Portal
{
public:
	static TempleDoor* create(cocos2d::ValueMap& properties);

	void lock(bool animate = true) override;
	void unlock(bool animate = true) override;

	static const std::string MapKey;

protected:
	TempleDoor(cocos2d::ValueMap& properties);
	virtual ~TempleDoor();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef Portal super;

	cocos2d::Sprite* back = nullptr;
	SmartClippingNode* doorClip = nullptr;
	cocos2d::Sprite* door = nullptr;
	cocos2d::Sprite* emblem = nullptr;
	CollisionObject* topCollision = nullptr;

	cocos2d::Vec2 emblemOffset = cocos2d::Vec2::ZERO;

	WorldSound* doorOpenSound = nullptr;

	static const std::string PropertyColor;
	static const float DoorOpenDelta;
	static const std::string UnlockedSaveKey;
};
