#pragma once

#include "Engine/Maps/GameObject.h"

class CollisionObject;
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

	void onEnter() override;
	void initializePositions() override;

private:
	typedef GameObject super;

	SmartAnimationSequenceNode* baseAnimation = nullptr;
	SmartAnimationSequenceNode* fallAnimation = nullptr;
	CollisionObject* hitbox = nullptr;
};
