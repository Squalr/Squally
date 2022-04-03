#pragma once

#include "Objects/Platformer/Breakables/BreakableBase.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class SmartAnimationSequenceNode;
class WorldSound;

class BreakableCageTall : public BreakableBase
{
public:
	static BreakableCageTall* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	BreakableCageTall(cocos2d::ValueMap& properties, int requiredHits = 1);
	virtual ~BreakableCageTall();

	void initializePositions() override;
	void initializeListeners() override;
	cocos2d::Vec2 getButtonOffset() override;
	void onBreak() override;

	cocos2d::Node* cagedContentNode = nullptr;

private:
	typedef BreakableBase super;

	WorldSound* breakSound = nullptr;
	SmartAnimationSequenceNode* explosion = nullptr;
	CollisionObject* cageBottom = nullptr;
	CollisionObject* cageSideBottom = nullptr;
	CollisionObject* cageSideTop = nullptr;
	CollisionObject* cageTop = nullptr;
};
