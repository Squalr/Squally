#include "ChestPoolFFRare.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier6/AlchemyPoolTier6.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier6/SmithingPoolTier6.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier6/PotionPoolTier6.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string ChestPoolFFRare::PoolName = "ff-rare";

ChestPoolFFRare* ChestPoolFFRare::create(ValueMap& properties)
{
	ChestPoolFFRare* instance = new ChestPoolFFRare(properties);

	instance->autorelease();

	return instance;
}

ChestPoolFFRare::ChestPoolFFRare(ValueMap& properties) : super(
	properties, ChestPoolFFRare::PoolName, SampleMethod::Random, 3, 5,
	{
		AlchemyPoolTier6::create(SampleMethod::Random, 1, 1),
		SmithingPoolTier6::create(SampleMethod::Random, 1, 2)
	})
{
	this->addItemToPool(ItemChance::create(Ruby::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Diamond::create(), ItemChance::Probability::Guaranteed));
}

ChestPoolFFRare::~ChestPoolFFRare()
{
}
