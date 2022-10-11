#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class HackableData;

class HeavenHug : public HackableObject
{
public:
	static HeavenHug* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	HeavenHug(cocos2d::ValueMap& properties);
	virtual ~HeavenHug();

	void onEnter() override;
	void initializePositions() override;
	void update(float dt) override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;

private:
	typedef HackableObject super;

	float getTravelHeight();
	float getSpeed();

	volatile float travelDistance = 0.0f;
	cocos2d::Node* heavenHugContainer = nullptr;
	cocos2d::Sprite* heavenHug = nullptr;
	CollisionObject* spikeCollision = nullptr;
	bool isMovingUp = false;

	static const float SpeedPer480Px;
};
