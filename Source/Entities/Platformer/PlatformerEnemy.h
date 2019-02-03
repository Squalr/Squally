#pragma once

#include "Entities/Platformer/PlatformerEntity.h"

// Base class for enemies
class PlatformerEnemy : public PlatformerEntity
{
public:
	std::string getBattleMapResource();
	std::vector<std::string> getAllyResources();

	static const std::string MapKeyBattleMap;
	static const std::string MapKeyAlly1;
	static const std::string MapKeyAlly2;
	static const std::string MapKeyAlly3;

protected:
	PlatformerEnemy(cocos2d::ValueMap* initProperties,
		std::string scmlResource,
		std::string emblemResource,
		PlatformerCollisionType collisionType,
		cocos2d::Size size,
		float scale,
		cocos2d::Vec2 collisionOffset,
		int baseHealth,
		int baseSpecial);

	~PlatformerEnemy();

	std::string battleMapResource;
	std::vector<std::string> allyResources;

private:
	typedef PlatformerEntity super;
};
