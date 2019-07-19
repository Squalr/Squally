#pragma once

#include "Objects/Platformer/Breakables/BreakableBase.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class SmartAnimationSequenceNode;
class Sound;

class BreakableCage : public BreakableBase
{
public:
	static BreakableCage* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyBreakableCage;

protected:
	BreakableCage(cocos2d::ValueMap& initProperties, int requiredHits = 1);
	virtual ~BreakableCage();

	void initializePositions() override;
	void initializeListeners() override;
	cocos2d::Vec2 getButtonOffset() override;
	void onBreak() override;
	cocos2d::Node* contentNode;

private:
	typedef BreakableBase super;

	Sound* breakSound;
	SmartAnimationSequenceNode* explosion;
	CollisionObject* cageBottom;
	CollisionObject* cage;
	CollisionObject* cageTop;
};
