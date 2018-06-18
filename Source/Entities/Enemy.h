#pragma once
#include "cocos2d.h"

#include "Entities/Entity.h"
#include "Resources.h"
#include "Objects/Collision/CategoryGroup.h"

using namespace cocos2d;

// Base class for enemies
class Enemy : public Entity
{
protected:
	Enemy(ValueMap* initProperties,
		std::string scmlResource,
		bool isFlying,
		Size size = Size(256.0f, 256.0f),
		float scale = 1.0f,
		Vec2 collisionOffset = Vec2(0.0f, 0.0f));

	~Enemy();
};
