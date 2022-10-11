#pragma once

#include "Engine/Maps/GameObject.h"

class SmartAnimationSequenceNode;

class LavaFX : public GameObject
{
public:
	static LavaFX* create(cocos2d::ValueMap& properties);

	void runAnimation();

	static const std::string MapKey;

protected:
	LavaFX(cocos2d::ValueMap& properties);
	virtual ~LavaFX();

	void initializePositions() override;

private:
	typedef GameObject super;

	SmartAnimationSequenceNode* fxAnimations = nullptr;
};
