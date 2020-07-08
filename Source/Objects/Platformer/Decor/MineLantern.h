#pragma once

#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class Sprite;
};

class HackableData;
class SmartAnimationSequenceNode;

class MineLantern : public GameObject
{
public:
	static MineLantern* create(cocos2d::ValueMap& properties);

	void torchOn();
	void torchOff();

	static const std::string MapKey;

protected:
	MineLantern(cocos2d::ValueMap& properties);
	virtual ~MineLantern();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef GameObject super;

	void updateMineLanternVisibility();
	void optimizationHideOffscreenMineLantern();

	cocos2d::Sprite* torch;
	cocos2d::Sprite* glow;
	SmartAnimationSequenceNode* fire;
	cocos2d::Sprite* lantern;

	bool isOn;
	bool isCulled;
};
