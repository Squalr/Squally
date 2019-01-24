#pragma once

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
		cocos2d::Size size,
		float scale,
		cocos2d::Vec2 collisionOffset,
		int baseHealth,
		int baseSpecial);

	~PlatformerEnemy();

	std::string battleMapResource;

private:
	typedef PlatformerEntity super;
};
