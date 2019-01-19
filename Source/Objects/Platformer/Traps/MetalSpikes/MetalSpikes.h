#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class HackableData;
class SmartAnimationSequenceNode;

class MetalSpikes : public HackableObject
{
public:
	static MetalSpikes* create(cocos2d::ValueMap* initProperties);

	static const std::string MapKeyMetalSpikes;

protected:
	MetalSpikes(cocos2d::ValueMap* initProperties);
	~MetalSpikes();

	cocos2d::Vec2 getButtonOffset() override;

private:
	typedef HackableObject super;
	void registerHackables();
	void onEnter() override;
	void update(float dt) override;
	void initializePositions() override;
	void updateSpikes(float dt);

	SmartAnimationSequenceNode* spikes;
	CollisionObject* spikeCollision;
	float currentElapsedTimeForSpikeTrigger;
	float totalTimeUntilSpikesTrigger;
	bool isRunningAnimation;
};
