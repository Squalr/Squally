#pragma once

#include "Engine/Hackables/HackableObject.h"

class CollisionObject;
class SmartAnimationNode;
class WorldSound;

class Ram : public HackableObject
{
public:
	static Ram* create(cocos2d::ValueMap& properties);

	SmartAnimationNode* getAnimations();

	static const std::string MapKeyRam;

protected:
	Ram(cocos2d::ValueMap& properties);
	virtual ~Ram();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef HackableObject super;

	SmartAnimationNode* ramAnimations;

	CollisionObject* collision;

	static const float AnimOffset;
};
