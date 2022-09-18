#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;

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

	float getTravelHeight();
	float getSpeed();

	volatile float travelDistance = 0.0f;
	cocos2d::Node* heavenHugContainer = nullptr;
	cocos2d::Sprite* heavenHug = nullptr;
	CollisionObject* spikeCollision = nullptr;
	bool isMovingUp = false;

	static const float SpeedPer480Px;
};
