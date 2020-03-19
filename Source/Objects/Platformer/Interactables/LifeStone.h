#pragma once

#include "Objects/Platformer/Interactables/InteractObject.h"

namespace cocos2d
{
	class Sprite;
}

class SmartAnimationSequenceNode;
class WorldSound;

class LifeStone : public InteractObject
{
public:
	static LifeStone* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	LifeStone(cocos2d::ValueMap& properties);
	virtual ~LifeStone();

	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onInteract() override;
	void onEndCollision() override;

private:
	typedef InteractObject super;

	void runHealAnimation(bool reRun = false);

	cocos2d::Sprite* lifeStone;
	SmartAnimationSequenceNode* healAnimation;
	WorldSound* healSound;
	
	bool isAnimating;
};
