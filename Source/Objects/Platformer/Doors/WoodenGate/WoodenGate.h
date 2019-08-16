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

	static const std::string MapKeyWoodenGate;

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

	bool isFlipped;
	float doorClosedPosition;
	std::string doorOpenEventName;
	cocos2d::Sprite* castleBack;
	SmartClippingNode* doorClip;
	cocos2d::Sprite* door;
	cocos2d::Sprite* bridge1;
	cocos2d::Sprite* bridge2;
	CollisionObject* doorCollision;
	cocos2d::Sprite* WoodenGateFront;
	cocos2d::Sprite* WoodenGateFront2;

	static const float DoorOpenDelta;
};
