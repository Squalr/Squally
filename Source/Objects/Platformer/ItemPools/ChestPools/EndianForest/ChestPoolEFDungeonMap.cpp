#include "ChestPoolEFDungeonMap.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string ChestPoolEFDungeonMap::PoolName = "ef-dungeon-map";

ChestPoolEFDungeonMap* ChestPoolEFDungeonMap::create(ValueMap& properties)
{
	ChestPoolEFDungeonMap* instance = new ChestPoolEFDungeonMap(properties);

	instance->autorelease();

	return instance;
}

ChestPoolEFDungeonMap::ChestPoolEFDungeonMap(ValueMap& properties) : super(
	properties, ChestPoolEFDungeonMap::PoolName, SampleMethod::Guarantee, 1, 1)
{
	this->addItemToPool(ItemChance::create(TempleMap::create(), ItemChance::Probability::Guaranteed));
}

ChestPoolEFDungeonMap::~ChestPoolEFDungeonMap()
{
}
