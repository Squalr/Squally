#pragma once

#include "Engine/Maps/GameObject.h"

class SmartAnimationSequenceNode;

class AcidFX : public GameObject
{
public:
	static AcidFX* create(cocos2d::ValueMap& properties);

	void runAnimation();

	static const std::string MapKey;

protected:
	AcidFX(cocos2d::ValueMap& properties);
	virtual ~AcidFX();

	void initializePositions() override;

private:
	typedef GameObject super;

	SmartAnimationSequenceNode* fxAnimations = nullptr;
};
