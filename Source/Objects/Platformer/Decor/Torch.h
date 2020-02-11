#pragma once

#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class Sprite;
};

class HackableData;
class SmartAnimationSequenceNode;

class Torch : public GameObject
{
public:
	static Torch* create(cocos2d::ValueMap& properties);

	void torchOn();
	void torchOff();

	static const std::string MapKeyTorch;

protected:
	Torch(cocos2d::ValueMap& properties);
	~Torch();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef GameObject super;

	void updateTorchVisibility();
	void optimizationHideOffscreenTorch();

	cocos2d::Sprite* torch;
	cocos2d::Sprite* glow;
	SmartAnimationSequenceNode* fire;

	bool isOn;
	bool isCulled;
};
