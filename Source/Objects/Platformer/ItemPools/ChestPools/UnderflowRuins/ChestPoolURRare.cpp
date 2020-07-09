#include "ChestPoolURRare.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier2/AlchemyPoolTier2.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier2/CardPoolTier2.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier2/SmithingPoolTier2.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier2/PotionPoolTier2.h"
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
	properties, ChestPoolURRare::PoolName, SampleMethod::Random, 3, 5,
	{
		AlchemyPoolTier2::create(SampleMethod::Random, 1, 1),
		SmithingPoolTier2::create(SampleMethod::Random, 1, 2)
	})
{
	this->addItemToPool(ItemChance::create(Emerald::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Iron::create(), ItemChance::Probability::Guaranteed));
}

ChestPoolURRare::~ChestPoolURRare()
{
}
