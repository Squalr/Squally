#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class HackableData;
class SmartAnimationSequenceNode;

class SpikedLog : public HackableObject
{
public:
	static SpikedLog* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	SpikedLog(cocos2d::ValueMap& properties);
	virtual ~SpikedLog();

	void onEnter() override;
	void initializePositions() override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;

private:
	typedef HackableObject super;
	int incrementSpikedLogAnimation(int count, int max);

	cocos2d::Sprite* beam;
	SmartAnimationSequenceNode* spikedLog;
	CollisionObject* spikeCollision;
	CollisionObject* logCollision;
};
