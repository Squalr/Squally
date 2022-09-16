#pragma once

#include "Objects/Platformer/Interactables/Doors/Portal.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class SmartClippingNode;
class WorldSound;

class MineDoor : public Portal
{
public:
	static MineDoor* create(cocos2d::ValueMap& properties);

	void lock(bool animate = true) override;
	void unlock(bool animate = true) override;

	static const std::string MapKey;

protected:
	MineDoor(cocos2d::ValueMap& properties);
	virtual ~MineDoor();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef Portal super;

	cocos2d::Sprite* doorLocked = nullptr;
	cocos2d::Sprite* door = nullptr;

	static const std::string UnlockedSaveKey;
};
