#include "ChestPoolEFRare.h"

#include "cocos/base/CCValue.h"

#include "Objects/Platformer/ItemPools/Tiered/Tier2/CraftingPoolTier2.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string ChestPoolEFRare::PoolName = "ef-rare";

ChestPoolEFRare* ChestPoolEFRare::create(ValueMap& properties)
{
	ChestPoolEFRare* instance = new ChestPoolEFRare(properties);

	instance->autorelease();

	return instance;
}

ChestPoolEFRare::ChestPoolEFRare(ValueMap& properties) : super(
	properties, ChestPoolEFRare::PoolName, SampleMethod::Guarantee, 2, 3,
	{ CraftingPoolTier2::create(SampleMethod::Guarantee, 2, 3) })
{
}

ChestPoolEFRare::~ChestPoolEFRare()
{
}
