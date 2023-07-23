#pragma once

#include "Engine/Maps/GameObject.h"

class SmartAnimationNode;

class RobotClaw : public GameObject
{
public:
	static RobotClaw* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	RobotClaw(cocos2d::ValueMap& properties);
	virtual ~RobotClaw();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef GameObject super;

	SmartAnimationNode* mineClawAnimations = nullptr;
};
