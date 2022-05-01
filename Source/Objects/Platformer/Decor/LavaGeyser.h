#pragma once

#include "Engine/Maps/GameObject.h"

class SmartAnimationSequenceNode;

class LavaGeyser : public GameObject
{
public:
	static LavaGeyser* create(cocos2d::ValueMap& properties);

	void runAnimation();

	static const std::string MapKey;

protected:
	LavaGeyser(cocos2d::ValueMap& properties);
	virtual ~LavaGeyser();

	void initializePositions() override;

private:
	typedef GameObject super;

	SmartAnimationSequenceNode* baseAnimation = nullptr;
	std::vector<SmartAnimationSequenceNode*> midAnimations;
	SmartAnimationSequenceNode* topAnimation = nullptr;
};
