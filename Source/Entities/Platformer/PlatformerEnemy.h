#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEntity.h"
#include "Resources/EntityResources.h"

using namespace cocos2d;

// Base class for enemies
class PlatformerEnemy : public PlatformerEntity
{
protected:
	PlatformerEnemy(ValueMap* initProperties,
		std::string scmlResource,
		CategoryName categoryName,
		Size size = Size(256.0f, 256.0f),
		float scale = 1.0f,
		Vec2 collisionOffset = Vec2(0.0f, 0.0f));

	~PlatformerEnemy();
};
