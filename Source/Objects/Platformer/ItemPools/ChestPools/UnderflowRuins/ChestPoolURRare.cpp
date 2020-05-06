#include "ChestPoolURRare.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string ChestPoolURRare::PoolName = "ur-rare";

ChestPoolURRare* ChestPoolURRare::create(ValueMap& properties)
{
	ChestPoolURRare* instance = new ChestPoolURRare(properties);

	instance->autorelease();

	return instance;
}

ChestPoolURRare::ChestPoolURRare(ValueMap& properties) : super(
	properties, ChestPoolURRare::PoolName, SampleMethod::Guarantee, 2, 3,
	{
	})
{
	this->addItemToPool(ItemChance::create(Quartz::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Copper::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Copper::create(), ItemChance::Probability::Guaranteed));
}

ChestPoolURRare::~ChestPoolURRare()
{
}
