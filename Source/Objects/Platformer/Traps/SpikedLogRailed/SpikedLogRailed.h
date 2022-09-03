#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class HackableData;
class SmartAnimationSequenceNode;

class SpikedLogRailed : public HackableObject
{
public:
	static SpikedLogRailed* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	SpikedLogRailed(cocos2d::ValueMap& properties);
	virtual ~SpikedLogRailed();

	void onEnter() override;
	void initializePositions() override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;

private:
	typedef HackableObject super;

	void onFrameComplete();
	int incrementSpikedLogRailedAnimation(int count, int max);

	int animationLength = 0;
	int currentAnimationIndex = 0;
	cocos2d::Sprite* beam = nullptr;
	SmartAnimationSequenceNode* spikedLog = nullptr;
	CollisionObject* spikeCollision = nullptr;
	CollisionObject* logCollision = nullptr;
};
