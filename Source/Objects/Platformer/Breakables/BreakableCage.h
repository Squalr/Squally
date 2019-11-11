#pragma once

#include "Objects/Platformer/Breakables/BreakableBase.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class SmartAnimationSequenceNode;
class WorldSound;

class BreakableCage : public BreakableBase
{
public:
	static BreakableCage* create(cocos2d::ValueMap& properties);

	static const std::string MapKeyBreakableCage;

protected:
	BreakableCage(cocos2d::ValueMap& properties, int requiredHits = 1);
	virtual ~BreakableCage();

	void initializePositions() override;
	void initializeListeners() override;
	cocos2d::Vec2 getButtonOffset() override;
	void onBreak() override;
	cocos2d::Node* contentNode;

private:
	typedef BreakableBase super;

	WorldSound* breakSound;
	SmartAnimationSequenceNode* explosion;
	CollisionObject* cageBottom;
	CollisionObject* cage;
	CollisionObject* cageTop;
};
