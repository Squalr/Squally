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
	void initializeEnemy2(std::string scmlResource, std::string idleAnimation, std::string walkAnimation, bool isFlying);

	void update(float) override;
	Sprite* sprite;
	AnimationNode* animationNode;

	Animation* walkAnimation;
	Animation* idleAnimation;
};
