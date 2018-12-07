#include "PlatformerEnemy.h"

const std::string PlatformerEnemy::MapKeyBattleMap = "battle_map";

PlatformerEnemy::PlatformerEnemy(ValueMap* initProperties, std::string scmlResource, CategoryName categoryName, Size size, float scale, Vec2 collisionOffset)
	: PlatformerEntity(initProperties, scmlResource, categoryName, size, scale, collisionOffset)
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