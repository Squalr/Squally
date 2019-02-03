#include "PlatformerEnemy.h"

#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

const std::string PlatformerEnemy::MapKeyBattleMap = "battle_map";
const std::string PlatformerEnemy::MapKeyAlly1 = "ally-1";
const std::string PlatformerEnemy::MapKeyAlly2 = "ally-2";
const std::string PlatformerEnemy::MapKeyAlly3 = "ally-3";

PlatformerEnemy::PlatformerEnemy(
	cocos2d::ValueMap* initProperties,
	std::string scmlResource,
	std::string emblemResource,
	PlatformerCollisionType collisionType, 
	cocos2d::Size size, 
	float scale,
	cocos2d::Vec2 collisionOffset,
	int baseHealth,
	int baseSpecial)
	: super(initProperties, scmlResource, emblemResource, collisionType, size, scale, collisionOffset, baseHealth, baseSpecial)
{
	this->battleMapResource = "";
	this->allyResources = std::vector<std::string>();

	if (GameUtils::keyExists(initProperties, PlatformerEnemy::MapKeyBattleMap))
	{
		this->battleMapResource = initProperties->at(PlatformerEnemy::MapKeyBattleMap).asString();
	}

	if (GameUtils::keyExists(initProperties, PlatformerEnemy::MapKeyAlly1))
	{
		this->allyResources.push_back(initProperties->at(PlatformerEnemy::MapKeyAlly1).asString());
	}

	if (GameUtils::keyExists(initProperties, PlatformerEnemy::MapKeyAlly2))
	{
		this->allyResources.push_back(initProperties->at(PlatformerEnemy::MapKeyAlly2).asString());
	}

	if (GameUtils::keyExists(initProperties, PlatformerEnemy::MapKeyAlly3))
	{
		this->allyResources.push_back(initProperties->at(PlatformerEnemy::MapKeyAlly3).asString());
	}
}

PlatformerEnemy::~PlatformerEnemy()
{
}

std::string PlatformerEnemy::getBattleMapResource()
{
	if (this->battleMapResource == "")
	{
		return this->battleMapResource;
	}

	return "Platformer/Maps/" + this->battleMapResource + ".tmx";
}

std::vector<std::string> PlatformerEnemy::getAllyResources()
{
	return this->allyResources;
}
