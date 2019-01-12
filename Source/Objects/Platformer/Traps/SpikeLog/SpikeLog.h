#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class HackableData;

class SpikeLog : public HackableObject
{
public:
	static SpikeLog* create(cocos2d::ValueMap* initProperties);

	static const std::string MapKeySpikeLog;

protected:
	SpikeLog(cocos2d::ValueMap* initProperties);
	~SpikeLog();

	cocos2d::Vec2 getButtonOffset() override;

private:
	typedef HackableObject super;
	void registerHackables();
	void onEnter() override;
	void initializePositions() override;
	void updateSpikeLog();
	float getTravelHeight();
	cocos2d::PhysicsBody* createSpikeCollision();

	volatile float travelDistance;
	cocos2d::Node* heavenHugContainer;
	cocos2d::Sprite* heavenHug;
	CollisionObject* spikeCollision;

	static const float SpeedPer480Px;
};
