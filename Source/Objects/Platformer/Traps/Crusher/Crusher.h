#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class SmartClippingNode;
class Squally;

class Crusher : public HackableObject
{
public:
	static Crusher* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	Crusher(cocos2d::ValueMap& properties);
	virtual ~Crusher();

	void onEnter() override;
	void initializePositions() override;
	void update(float dt) override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;

private:
	typedef HackableObject super;

	bool isPlayerDetected();
	float getSpeed();

	volatile float travelDistance = 0.0f;
	SmartClippingNode* poleClip = nullptr;
	cocos2d::Sprite* base = nullptr;
	cocos2d::Sprite* pole = nullptr;
	cocos2d::Sprite* crusher = nullptr;
	CollisionObject* spikeCollision = nullptr;
	Squally* squally = nullptr;
	bool isMovingUp = true;

	static const float SpeedPer480Px;
};
