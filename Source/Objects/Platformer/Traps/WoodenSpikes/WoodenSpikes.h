#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class HackableData;
class SmartAnimationSequenceNode;

class WoodenSpikes : public HackableObject
{
public:
	static WoodenSpikes* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyWoodenSpikes;

protected:
	WoodenSpikes(cocos2d::ValueMap& initProperties);
	virtual ~WoodenSpikes();

	void onEnter() override;
	void update(float dt) override;
	void initializePositions() override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;

private:
	typedef HackableObject super;
	void updateSpikes(float dt);

	SmartAnimationSequenceNode* spikes;
	CollisionObject* spikeCollision;
	float currentElapsedTimeForSpikeTrigger;
	float totalTimeUntilSpikesTrigger;
	bool isRunningAnimation;

	static const cocos2d::Vec2 SpikesDownPosition;
};
