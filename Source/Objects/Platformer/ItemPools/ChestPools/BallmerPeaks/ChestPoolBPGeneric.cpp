#include "ChestPoolBPGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/MergePool.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier7/AlchemyPoolTier7.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier7/CardPoolTier7.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier7/SmithingPoolTier7.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier7/PotionPoolTier7.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string ChestPoolBPGeneric::PoolName = "bp-generic";

ChestPoolBPGeneric* ChestPoolBPGeneric::create(ValueMap& properties)
{
	ChestPoolBPGeneric* instance = new ChestPoolBPGeneric(properties);

	instance->autorelease();

	return instance;
}

ChestPoolBPGeneric::ChestPoolBPGeneric(ValueMap& properties) : super(
	properties, ChestPoolBPGeneric::PoolName, SampleMethod::Guarantee, 2, 3,
	{
		CardPoolTier7::create(SampleMethod::Random, 1, 1),
		MergePool::create(SampleMethod::Random, 3, 5,
		{
			AlchemyPoolTier7::create(),
			SmithingPoolTier7::create(),
			PotionPoolTier7::create()
		})
	})
{
}

ChestPoolBPGeneric::~ChestPoolBPGeneric()
{
}
