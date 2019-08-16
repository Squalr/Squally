#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class ClippingNode;
	class Sprite;
}

class CollisionObject;
class HackableData;

class TrapDoor : public HackableObject
{
public:
	static TrapDoor* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyTrapDoor;

protected:
	TrapDoor(cocos2d::ValueMap& properties);
	virtual ~TrapDoor();

	void onEnter() override;
	void initializeListeners() override;
	void initializePositions() override;
	void update(float) override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;

private:
	typedef HackableObject super;

	void onDoorEventTriggered(cocos2d::ValueMap args);

	bool isFlipped;
	float doorClosedPosition;
	std::string doorOpenEventName;
	cocos2d::ClippingNode* doorClip;
	cocos2d::Sprite* door;
	CollisionObject* doorCollision;

	static const float DoorOpenDelta;
};
