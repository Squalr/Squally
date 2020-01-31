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

	static const std::string MapKeyTempleDoor;

protected:
	TempleDoor(cocos2d::ValueMap& properties);
	virtual ~TempleDoor();

	void initializePositions() override;
	void onObjectStateLoaded() override;

private:
	typedef Portal super;

	cocos2d::Sprite* back;
	SmartClippingNode* doorClip;
	cocos2d::Sprite* door;
	cocos2d::Sprite* emblem;
	CollisionObject* topCollision;

	cocos2d::Vec2 emblemOffset;

	WorldSound* doorOpenSound;

	static const std::string MapKeyColor;
	static const float DoorOpenDelta;
	static const std::string UnlockedSaveKey;
};
