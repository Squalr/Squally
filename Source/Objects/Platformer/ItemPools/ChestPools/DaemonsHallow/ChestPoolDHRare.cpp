#include "ChestPoolDHRare.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier6/AlchemyPoolTier6.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier6/CardPoolTier6.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier6/SmithingPoolTier6.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier6/PotionPoolTier6.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string ChestPoolDHRare::PoolName = "dh-rare";

ChestPoolDHRare* ChestPoolDHRare::create(ValueMap& properties)
{
	ChestPoolDHRare* instance = new ChestPoolDHRare(properties);

	instance->autorelease();

	return instance;
}

ChestPoolDHRare::ChestPoolDHRare(ValueMap& properties) : super(
	properties, ChestPoolDHRare::PoolName, SampleMethod::Random, 3, 5,
	{
		AlchemyPoolTier6::create(SampleMethod::Random, 1, 1),
		SmithingPoolTier6::create(SampleMethod::Random, 1, 2)
	})
{
	this->addItemToPool(ItemChance::create(Ruby::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Diamond::create(), ItemChance::Probability::Guaranteed));
}

ChestPoolDHRare::~ChestPoolDHRare()
{
}
