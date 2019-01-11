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
	static HeavenHug* create(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyHeavenHug;

protected:
	HeavenHug(cocos2d::ValueMap* initProperties);
	~HeavenHug();

	cocos2d::Vec2 getButtonOffset() override;

private:
	typedef HackableObject super;
	void registerHackables();
	void onEnter() override;
	void initializePositions() override;
	void updateHeavenHug();
	float getTravelHeight();
	cocos2d::PhysicsBody* createSpikeCollision();

	volatile float travelDistance;
	cocos2d::Node* heavenHugContainer;
	cocos2d::Sprite* heavenHug;
	CollisionObject* spikeCollision;

	static const float SpeedPer480Px;
};
