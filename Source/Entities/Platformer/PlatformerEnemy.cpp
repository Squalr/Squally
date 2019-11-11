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

const std::string PlatformerEnemy::MapKeyBattleAttachedBehavior = "battle-behavior";
const std::string PlatformerEnemy::MapKeyBattleMap = "battle-map";
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
	this->battleBehavior = GameUtils::getKeyOrDefault(this->properties, PlatformerEnemy::MapKeyBattleAttachedBehavior, Value("")).asString();
	this->battleMapResource = GameUtils::getKeyOrDefault(this->properties, PlatformerEnemy::MapKeyBattleMap, Value(MapResources::Combat_Intro)).asString();
	this->dropTable = std::vector<std::tuple<std::string, float>>();
	this->iouTable = std::tuple<int, int>();
	this->dropInventory = Inventory::create();

	// Tag all entities by class and by their name to optimize object queries (ObjectEvents.h)
	this->addTag(PlatformerEnemy::PlatformerEnemyTag);

	this->addChild(this->dropInventory);
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

	return "Private/Platformer/Maps/" + this->battleMapResource + ".tmx";
}

std::string PlatformerEnemy::getBattleBehavior()
{
	return this->battleBehavior;
}

Inventory* PlatformerEnemy::getDropInventory()
{
	return this->dropInventory;
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
				this->dropInventory->forceInsert(item);
			}));
		}
	}
}

void PlatformerEnemy::buildIOUDrop()
{
	this->getCurrencyInventory()->addCurrency(IOU::getIdentifier(), RandomHelper::random_int(std::get<0>(this->iouTable), std::get<1>(this->iouTable)));
}
