#include "ChestPoolBPRare.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier7/AlchemyPoolTier7.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier7/CardPoolTier7.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier7/SmithingPoolTier7.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier7/PotionPoolTier7.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string ChestPoolBPRare::PoolName = "bp-rare";

ChestPoolBPRare* ChestPoolBPRare::create(ValueMap& properties)
{
	ChestPoolBPRare* instance = new ChestPoolBPRare(properties);

	instance->autorelease();

	return instance;
}

ChestPoolBPRare::ChestPoolBPRare(ValueMap& properties) : super(
	properties, ChestPoolBPRare::PoolName, SampleMethod::Random, 3, 5,
	{
		AlchemyPoolTier7::create(SampleMethod::Random, 1, 1),
		SmithingPoolTier7::create(SampleMethod::Random, 1, 2)
	})
{
	this->addItemToPool(ItemChance::create(Ruby::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Diamond::create(), ItemChance::Probability::Guaranteed));
}

ChestPoolBPRare::~ChestPoolBPRare()
{
}
