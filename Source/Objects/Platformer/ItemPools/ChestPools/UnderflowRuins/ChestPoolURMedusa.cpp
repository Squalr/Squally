#include "ChestPoolURMedusa.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier2/AlchemyPoolTier2.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier2/SmithingPoolTier2.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier2/PotionPoolTier2.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string ChestPoolURMedusa::PoolName = "ur-medusa";

ChestPoolURMedusa* ChestPoolURMedusa::create(ValueMap& properties)
{
	ChestPoolURMedusa* instance = new ChestPoolURMedusa(properties);

	instance->autorelease();

	return instance;
}

ChestPoolURMedusa::ChestPoolURMedusa(ValueMap& properties) : super(
	properties, ChestPoolURMedusa::PoolName, SampleMethod::Random, 4, 6,
	{
		AlchemyPoolTier2::create(SampleMethod::Random, 1, 1),
		SmithingPoolTier2::create(SampleMethod::Random, 1, 2)
	})
{
	this->addItemToPool(ItemChance::create(Emerald::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Iron::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(AquaMarineNecklace::create(), ItemChance::Probability::Guaranteed));
}

ChestPoolURMedusa::~ChestPoolURMedusa()
{
}
