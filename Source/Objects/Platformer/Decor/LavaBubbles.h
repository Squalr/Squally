#pragma once

#include "Engine/Maps/GameObject.h"

class SmartAnimationSequenceNode;

class LavaBubbles : public GameObject
{
public:
	static LavaBubbles* create(cocos2d::ValueMap& properties);

	void runAnimation();

	static const std::string MapKey;

protected:
	LavaBubbles(cocos2d::ValueMap& properties);
	virtual ~LavaBubbles();

	void initializePositions() override;

private:
	typedef GameObject super;

	SmartAnimationSequenceNode* bubbleAnimations = nullptr;
};
