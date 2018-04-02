#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Entities/Entity.h"
#include "Objects/Collision/CategoryGroup.h"

using namespace cocos2d;

// Base class for enemies
class Enemy : public Entity
{
protected:
	Enemy();
	~Enemy();
	bool contactBegin(CollisionData data) override;
	bool contactUpdate(CollisionData data) override;
	bool contactEnd(CollisionData data) override;

	void initializeEnemy(std::string baseIdleResource, float idleFrameSpeed, std::string baseWalkResource, float walkFrameSpeed, bool isFlying);

	void update(float) override;
	Sprite* sprite;

	Animation* walkAnimation;
	Animation* idleAnimation;
};
