#include "ChestPoolDMRare.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier3/AlchemyPoolTier3.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier3/CardPoolTier3.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier3/SmithingPoolTier3.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier3/PotionPoolTier3.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string ChestPoolDMRare::PoolName = "dm-rare";

ChestPoolDMRare* ChestPoolDMRare::create(ValueMap& properties)
{
	ChestPoolDMRare* instance = new ChestPoolDMRare(properties);

	instance->autorelease();

	return instance;
}

ChestPoolDMRare::ChestPoolDMRare(ValueMap& properties) : super(
	properties, ChestPoolDMRare::PoolName, SampleMethod::Random, 3, 5,
	{
		AlchemyPoolTier3::create(SampleMethod::Random, 1, 1),
		SmithingPoolTier3::create(SampleMethod::Random, 1, 2)
	})
{
	this->addItemToPool(ItemChance::create(Emerald::create(), ItemChance::Probability::Guaranteed));
	this->addItemToPool(ItemChance::create(Iron::create(), ItemChance::Probability::Guaranteed));
}

ChestPoolDMRare::~ChestPoolDMRare()
{
}
