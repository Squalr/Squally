#include "PlatformerEnemy.h"

#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

const std::string PlatformerEnemy::MapKeyBattleMap = "battle_map";

PlatformerEnemy::PlatformerEnemy(
	cocos2d::ValueMap* initProperties,
	std::string scmlResource, 
	PlatformerCollisionType collisionType, 
	cocos2d::Size size, 
	float scale,
	cocos2d::Vec2 collisionOffset)
	: PlatformerEntity(initProperties, scmlResource, collisionType, size, scale, collisionOffset)
{
	this->battleMapResource = "";

	if (GameUtils::keyExists(initProperties, PlatformerEnemy::MapKeyBattleMap))
	{
		this->battleMapResource = initProperties->at(PlatformerEnemy::MapKeyBattleMap).asString();
	}
}

PlatformerEnemy::~PlatformerEnemy()
{
}

std::string PlatformerEnemy::getBattleMapResource()
{
	return "Platformer/Maps/" + this->battleMapResource + ".tmx";
}