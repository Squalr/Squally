#pragma once

#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class Sprite;
};

class SmartAnimationSequenceNode;

class Torch : public GameObject
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
	void update(float dt) override;

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
