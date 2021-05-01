#pragma once

#include "Objects/Platformer/Interactables/ToggleableObject.h"

namespace cocos2d
{
	class Sprite;
};

class SmartAnimationSequenceNode;

class Torch : public ToggleableObject
{
public:
	static Torch* create(cocos2d::ValueMap& properties);

	void torchOn();
	void torchOff();

	static const std::string MapKey;

protected:
	Torch(cocos2d::ValueMap& properties);
	virtual ~Torch();

	void onEnter() override;
	void initializePositions() override;
	void onEnable(bool isInit, bool isInstant = true) override;
	void onDisable(bool isInit, bool isInstant = true) override;
	void onOptimizationHide() override;
	void onOptimizationShow() override;

private:
	typedef ToggleableObject super;

	void startFx();
	void stopFx();

	cocos2d::Sprite* torch;
	cocos2d::Sprite* glow;
	SmartAnimationSequenceNode* fire;
};
