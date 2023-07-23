#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class HackableData;
class SmartAnimationSequenceNode;

class LavaFlow : public HackableObject
{
public:
	static LavaFlow* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	LavaFlow(cocos2d::ValueMap& properties);
	virtual ~LavaFlow();

	void onEnter() override;
	void update(float dt) override;
	void initializePositions() override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;

private:
	typedef HackableObject super;

	void checkLavaFlow();

	SmartAnimationSequenceNode* ripple = nullptr;

	static const cocos2d::Vec2 SpikesUpPosition;
	static const cocos2d::Vec2 SpikesDownPosition;
};
