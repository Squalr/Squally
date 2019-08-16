#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class HackableData;
class SmartAnimationSequenceNode;

class SpikeLog : public HackableObject
{
public:
	static SpikeLog* create(cocos2d::ValueMap& properties);

	static const std::string MapKeySpikeLog;

protected:
	SpikeLog(cocos2d::ValueMap& properties);
	virtual ~SpikeLog();

	void onEnter() override;
	void initializePositions() override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;

private:
	typedef HackableObject super;
	int incrementSpikeLogAnimation(int count, int max);

	cocos2d::Sprite* beam;
	SmartAnimationSequenceNode* spikedLog;
	CollisionObject* spikeCollision;
	CollisionObject* logCollision;
};
