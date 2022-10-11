#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class HackableData;
class SmartClippingNode;

class WoodenGate : public HackableObject
{
public:
	static WoodenGate* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	WoodenGate(cocos2d::ValueMap& properties);
	virtual ~WoodenGate();

	void onEnter() override;
	void initializeListeners() override;
	void initializePositions() override;
	void update(float) override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;

private:
	typedef HackableObject super;

	void onDoorEventTriggered(cocos2d::ValueMap args);

	bool isFlipped = false;
	float doorClosedPosition = 0.0f;
	SmartClippingNode* doorClip = nullptr;
	cocos2d::Sprite* door = nullptr;
	cocos2d::Sprite* bridge2 = nullptr;
	CollisionObject* doorCollision = nullptr;

	static const float DoorOpenDelta;
};
