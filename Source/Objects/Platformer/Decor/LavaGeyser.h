#pragma once

#include "Engine/Maps/GameObject.h"

class CollisionObject;
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

	void onEnter() override;
	void initializePositions() override;

private:
	typedef GameObject super;

	static const float BaseSize;

	SmartAnimationSequenceNode* baseAnimation = nullptr;
	SmartAnimationSequenceNode* midAnimation = nullptr;
	SmartAnimationSequenceNode* topAnimation = nullptr;
	CollisionObject* hitbox = nullptr;
};
