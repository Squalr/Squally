#pragma once
#include "cocos2d.h"

#include "Entities/Platformer/PlatformerEntity.h"

// Base class for enemies
class PlatformerEnemy : public PlatformerEntity
{
public:
	std::string getBattleMapResource();

	static const std::string MapKeyBattleMap;

protected:
	PlatformerEnemy(cocos2d::ValueMap* initProperties,
		std::string scmlResource,
		PlatformerCollisionType collisionType,
		cocos2d::Size size = cocos2d::Size(256.0f, 256.0f),
		float scale = 1.0f,
		cocos2d::Vec2 collisionOffset = cocos2d::Vec2(0.0f, 0.0f));

	~PlatformerEnemy();

	std::string battleMapResource;
};
