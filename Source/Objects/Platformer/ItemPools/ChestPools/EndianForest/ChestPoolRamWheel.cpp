#include "ChestPoolRamWheel.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string ChestPoolRamWheel::PoolName = "ef-ram-wheel";

ChestPoolRamWheel* ChestPoolRamWheel::create(ValueMap& properties)
{
	ChestPoolRamWheel* instance = new ChestPoolRamWheel(properties);

	instance->autorelease();

	return instance;
}

ChestPoolRamWheel::ChestPoolRamWheel(ValueMap& properties) : super(
	properties, ChestPoolRamWheel::PoolName, SampleMethod::Guarantee, 1, 1,
	{
	})
{
	this->addItemToPool(ItemChance::create(RamWheel::create(), ItemChance::Probability::Guaranteed));
}

ChestPoolRamWheel::~ChestPoolRamWheel()
{
}
