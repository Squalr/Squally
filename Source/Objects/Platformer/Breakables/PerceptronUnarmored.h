#pragma once

#include "Objects/Platformer/Breakables/BreakableBase.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class SmartAnimationNode;
class SmartAnimationSequenceNode;
class SmartParticles;
class WorldSound;

class PerceptronUnarmored : public BreakableBase
{
public:
	static PerceptronUnarmored* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	PerceptronUnarmored(cocos2d::ValueMap& properties, int requiredHits = 1);
	virtual ~PerceptronUnarmored();

	void initializePositions() override;
	void initializeListeners() override;
	cocos2d::Vec2 getButtonOffset() override;
	void onBreak() override;

private:
	typedef BreakableBase super;

	WorldSound* breakSound = nullptr;
	SmartAnimationSequenceNode* explosion = nullptr;
	SmartAnimationNode* perceptron = nullptr;
};
