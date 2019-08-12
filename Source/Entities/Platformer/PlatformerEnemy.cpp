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
#include "Objects/Platformer/Collectables/IOU.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItemDeserializer.h"

#include "Resources/MapResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string PlatformerEnemy::MapKeyBattleArgs = "battle-args";
const std::string PlatformerEnemy::MapKeyBattleMap = "battle-map";
const std::string PlatformerEnemy::MapKeyEnemy1 = "enemy-1";
const std::string PlatformerEnemy::MapKeyEnemy2 = "enemy-2";
const std::string PlatformerEnemy::MapKeyAlly3 = "ally-3";

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
	this->combatEntityList = std::vector<std::string>();
	this->battleMapArgs = StrUtils::splitOn(GameUtils::getKeyOrDefault(this->properties, PlatformerEnemy::MapKeyBattleArgs, Value("")).asString(), ", ");
	this->battleMapResource = GameUtils::getKeyOrDefault(this->properties, PlatformerEnemy::MapKeyBattleMap, Value(MapResources::EndianForest_Battlegrounds)).asString();
	this->dropTable = std::vector<std::tuple<std::string, float>>();
	this->iouTable = std::tuple<int, int>();
	this->combatEntityList.push_back(this->properties.at(PlatformerEnemy::MapKeyName).asString());

	if (GameUtils::keyExists(this->properties, PlatformerEnemy::MapKeyEnemy1))
	{
		this->combatEntityList.push_back(this->properties.at(PlatformerEnemy::MapKeyEnemy1).asString());
	}

	if (GameUtils::keyExists(this->properties, PlatformerEnemy::MapKeyEnemy2))
	{
		this->combatEntityList.push_back(this->properties.at(PlatformerEnemy::MapKeyEnemy2).asString());
	}

	if (GameUtils::keyExists(this->properties, PlatformerEnemy::MapKeyAlly3))
	{
		this->combatEntityList.push_back(this->properties.at(PlatformerEnemy::MapKeyAlly3).asString());
	}
}

PlatformerEnemy::~PlatformerEnemy()
{
}

void PlatformerEnemy::onEnter()
{
	super::onEnter();

	this->buildDropInventory();
	this->buildIOUDrop();
}

void PlatformerEnemy::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();
}

void PlatformerEnemy::initializePositions()
{
	super::initializePositions();
}

void PlatformerEnemy::initializeListeners()
{
	super::initializeListeners();
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

	return "Platformer/Maps/" + this->battleMapResource + ".tmx";
}

std::vector<std::string> PlatformerEnemy::getBattleMapArgs()
{
	return this->battleMapArgs;
}

std::vector<std::string> PlatformerEnemy::getCombatEntityList()
{
	return this->combatEntityList;
}

void PlatformerEnemy::onObjectStateLoaded()
{
	super::onObjectStateLoaded();
}

std::tuple<std::string, float> PlatformerEnemy::createDrop(std::string itemKey, float probability)
{
	return std::make_tuple(itemKey, probability);
}

void PlatformerEnemy::buildDropInventory()
{
	for (auto it = this->dropTable.begin(); it != this->dropTable.end(); it++)
	{
		if (RandomHelper::random_real(0.0f, 1.0f) <= std::get<1>(*it))
		{
			PlatformerItemDeserializer::getInstance()->deserialize(InventoryEvents::RequestItemDeserializationArgs(std::get<0>(*it), [=](Item* item)
			{
				this->getInventory()->forceInsert(item);
			}));
		}
	}
}

void PlatformerEnemy::buildIOUDrop()
{
	this->getCurrencyInventory()->addCurrency(IOU::getIdentifier(), RandomHelper::random_int(std::get<0>(this->iouTable), std::get<1>(this->iouTable)));
}
