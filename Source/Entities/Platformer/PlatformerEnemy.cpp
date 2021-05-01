#include "PlatformerEnemy.h"

#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/CurrencyInventory.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Scenes/Platformer/Components/Entities/Inventory/EntityInventoryBehavior.h"

#include "Resources/MapResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string PlatformerEnemy::PropertyBattleMap = "battle-map";
const std::string PlatformerEnemy::PropertyBattleTag = "battle-tag";
const std::string PlatformerEnemy::PropertyDropPool = "drop-pool";
const std::string PlatformerEnemy::PlatformerEnemyTag = "platformer-enemy";

PlatformerEnemy::PlatformerEnemy(
	ValueMap& properties,
	std::string entityName,
	std::string scmlResource,
	std::string emblemResource,
	Size size, 
	float scale,
	Vec2 collisionOffset,
	float hoverHeight)
	: super(
		properties,
		entityName,
		scmlResource,
		emblemResource,
		size,
		scale,
		collisionOffset,
		hoverHeight)
{
	this->battleMapResource = GameUtils::getKeyOrDefault(this->properties, PlatformerEnemy::PropertyBattleMap, Value(MapResources::EndianForest_Combat_Intro)).asString();
	this->battleMapTag = GameUtils::getKeyOrDefault(this->properties, PlatformerEnemy::PropertyBattleTag, Value("")).asString();
	this->dropPool = GameUtils::getKeyOrDefault(this->properties, PlatformerEnemy::PropertyDropPool, Value("error")).asString();

	// Tag all entities by class and by their name to optimize object queries (ObjectEvents.h)
	this->addTag(PlatformerEnemy::PlatformerEnemyTag);

	// Tag enemies of the same party (same battle tag)
	this->addTag(this->battleMapTag);
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

	if (StrUtils::endsWith(this->battleMapResource, ".tmx", true))
	{
		return this->battleMapResource;
	}

	return "Public/Platformer/Maps/" + this->battleMapResource + ".tmx";
}

std::string PlatformerEnemy::getBattleTag()
{
	return this->battleMapTag;
}

std::string PlatformerEnemy::getDropPool()
{
	return this->dropPool;
}

void PlatformerEnemy::setDropPool(std::string dropPool)
{
	this->dropPool = dropPool;
}
