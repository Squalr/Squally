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
	int incrementSpikeLogAnimation(int count, int max);

	cocos2d::Sprite* beam;
	SmartAnimationSequenceNode* spikedLog;
	CollisionObject* spikeCollision;
	CollisionObject* logCollision;
};
