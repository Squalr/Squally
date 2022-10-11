#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class HackableData;
class SmartAnimationSequenceNode;

class FireBird : public HackableObject
{
public:
	static FireBird* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	FireBird(cocos2d::ValueMap& properties);
	virtual ~FireBird();

	void onEnter() override;
	void update(float dt) override;
	void initializePositions() override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;

private:
	typedef HackableObject super;

	void updateSpikes(float dt);

	SmartAnimationSequenceNode* spikes = nullptr;
	CollisionObject* spikeCollision = nullptr;
	float currentElapsedTimeForSpikeTrigger = 0.0f;
	float totalTimeUntilSpikesTrigger = 0.0f;
	bool isRunningAnimation = false;
	bool isFlippedY = false;

	static const cocos2d::Vec2 SpikesUpPosition;
	static const cocos2d::Vec2 SpikesDownPosition;
};
