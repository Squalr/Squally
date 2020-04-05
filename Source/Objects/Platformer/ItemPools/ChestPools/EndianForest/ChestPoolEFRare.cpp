#include "ChestPoolEFRare.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
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
	{
	})
{
	this->addItemToPool(ItemChance::create(Quartz::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Copper::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Copper::create(), ItemChance::Probability::Guaranteed));
}

ChestPoolEFRare::~ChestPoolEFRare()
{
}
