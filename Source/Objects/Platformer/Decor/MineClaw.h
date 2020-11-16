#pragma once

#include "Engine/Maps/GameObject.h"

class SmartAnimationNode;

class MineClaw : public GameObject
{
public:
	static MineClaw* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	MineClaw(cocos2d::ValueMap& properties);
	virtual ~MineClaw();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef GameObject super;

	SmartAnimationNode* mineClawAnimations;
};
