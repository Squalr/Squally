#pragma once

#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class Sprite;
};

class SmartAnimationSequenceNode;

class FireplaceFire : public GameObject
{
public:
	static FireplaceFire* create(cocos2d::ValueMap& properties);

	void torchOn();
	void torchOff();

	static const std::string MapKey;

protected:
	FireplaceFire(cocos2d::ValueMap& properties);
	virtual ~FireplaceFire();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef GameObject super;
	
	cocos2d::Sprite* glow;
	SmartAnimationSequenceNode* fire;

	bool isOn;
	bool isCulled;
};
