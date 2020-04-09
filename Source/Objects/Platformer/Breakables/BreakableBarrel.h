#pragma once

#include "Objects/Platformer/Breakables/BreakableBase.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class SmartAnimationSequenceNode;
class WorldSound;

class BreakableBarrel : public BreakableBase
{
public:
	static BreakableBarrel* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	BreakableBarrel(cocos2d::ValueMap& properties);
	virtual ~BreakableBarrel();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onBreak() override;

private:
	typedef BreakableBase super;

	cocos2d::Sprite* barrelSprite;
	WorldSound* breakSound;
	SmartAnimationSequenceNode* explosion;
};
