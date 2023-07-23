#include "ChestPoolLCRare.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier5/AlchemyPoolTier5.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier5/SmithingPoolTier5.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier5/PotionPoolTier5.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string ChestPoolLCRare::PoolName = "lc-rare";

ChestPoolLCRare* ChestPoolLCRare::create(ValueMap& properties)
{
	ChestPoolLCRare* instance = new ChestPoolLCRare(properties);

	instance->autorelease();

	return instance;
}

ChestPoolLCRare::ChestPoolLCRare(ValueMap& properties) : super(
	properties, ChestPoolLCRare::PoolName, SampleMethod::Random, 3, 5,
	{
		AlchemyPoolTier5::create(SampleMethod::Random, 1, 1),
		SmithingPoolTier5::create(SampleMethod::Random, 1, 2)
	})
{
	this->addItemToPool(ItemChance::create(Ruby::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Diamond::create(), ItemChance::Probability::Guaranteed));
}

ChestPoolLCRare::~ChestPoolLCRare()
{
}
