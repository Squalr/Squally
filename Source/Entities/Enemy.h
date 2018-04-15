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
	Enemy(std::string scmlResource, std::string entityName, bool isFlying);
	~Enemy();
	bool contactBegin(CollisionData data) override;
	bool contactUpdate(CollisionData data) override;
	bool contactEnd(CollisionData data) override;

	void update(float) override;

	AnimationNode* animationNode;
};
