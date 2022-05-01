#pragma once

#include "Engine/Maps/GameObject.h"

class SmartAnimationSequenceNode;

class LavaFall : public GameObject
{
public:
	static LavaFall* create(cocos2d::ValueMap& properties);

	void runAnimation();

	static const std::string MapKey;

protected:
	LavaFall(cocos2d::ValueMap& properties);
	virtual ~LavaFall();

	void initializePositions() override;

private:
	typedef GameObject super;

	std::vector<SmartAnimationSequenceNode*> animationLinks;
};
