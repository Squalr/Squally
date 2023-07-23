#include "ChestPoolVSRare.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier8/AlchemyPoolTier8.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier8/SmithingPoolTier8.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier8/PotionPoolTier8.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string ChestPoolVSRare::PoolName = "vs-rare";

ChestPoolVSRare* ChestPoolVSRare::create(ValueMap& properties)
{
	ChestPoolVSRare* instance = new ChestPoolVSRare(properties);

	instance->autorelease();

	return instance;
}

ChestPoolVSRare::ChestPoolVSRare(ValueMap& properties) : super(
	properties, ChestPoolVSRare::PoolName, SampleMethod::Random, 3, 5,
	{
		AlchemyPoolTier8::create(SampleMethod::Random, 1, 1),
		SmithingPoolTier8::create(SampleMethod::Random, 1, 2)
	})
{
	this->addItemToPool(ItemChance::create(Ruby::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Diamond::create(), ItemChance::Probability::Guaranteed));
}

ChestPoolVSRare::~ChestPoolVSRare()
{
}
