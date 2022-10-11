#pragma once

#include "Objects/Platformer/Interactables/Doors/Portal.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class SmartClippingNode;
class WorldSound;

class Portcullus : public Portal
{
public:
	static Portcullus* create(cocos2d::ValueMap& properties);

	void lock(bool animate = true) override;
	void unlock(bool animate = true) override;

	static const std::string MapKey;

protected:
	Portcullus(cocos2d::ValueMap& properties);
	virtual ~Portcullus();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef Portal super;

	cocos2d::Sprite* top = nullptr;
	cocos2d::Sprite* bars = nullptr;
	cocos2d::Sprite* spikes = nullptr;

	WorldSound* doorOpenSound = nullptr;

	static const float DoorOpenDelta;
	static const std::string UnlockedSaveKey;
};
