#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class ClippingNode;
	class Sprite;
}

class CollisionObject;
class HackableData;

class CastleDoor : public HackableObject
{
public:
	static CastleDoor* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyCastleDoor;

protected:
	CastleDoor(cocos2d::ValueMap& initProperties);
	virtual ~CastleDoor();

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
	cocos2d::Sprite* castleBack;
	cocos2d::ClippingNode* doorClip;
	cocos2d::Sprite* door;
	cocos2d::Sprite* bridge1;
	cocos2d::Sprite* bridge2;
	CollisionObject* doorCollision;

	static const float DoorOpenDelta;
};
