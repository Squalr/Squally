#pragma once

#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class Sprite;
};

class SmartAnimationSequenceNode;

class MineLantern : public GameObject
{
public:
	static MineLantern* create(cocos2d::ValueMap& properties);

	void lanternOn();
	void lanternOff();

	static const std::string MapKey;

protected:
	MineLantern(cocos2d::ValueMap& properties);
	virtual ~MineLantern();

	void onEnter() override;
	void initializePositions() override;
	void update(float dt) override;

private:
	typedef GameObject super;

	void updateMineLanternVisibility();
	void optimizationHideOffscreenMineLantern();

	cocos2d::Sprite* lanternBack = nullptr;
	cocos2d::Sprite* glow = nullptr;
	SmartAnimationSequenceNode* fire = nullptr;
	cocos2d::Sprite* lantern = nullptr;

	bool isOn = false;
	bool isCulled = false;
};
