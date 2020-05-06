#include "ChestPoolURGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/MergePool.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier2/AlchemyPoolTier2.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier2/CardPoolTier2.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier2/SmithingPoolTier2.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier2/PotionPoolTier2.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string ChestPoolURGeneric::PoolName = "ur-generic";

ChestPoolURGeneric* ChestPoolURGeneric::create(ValueMap& properties)
{
	ChestPoolURGeneric* instance = new ChestPoolURGeneric(properties);

	instance->autorelease();

	return instance;
}

ChestPoolURGeneric::ChestPoolURGeneric(ValueMap& properties) : super(
	properties, ChestPoolURGeneric::PoolName, SampleMethod::Guarantee, 2, 3,
	{
		CardPoolTier2::create(SampleMethod::Random, 1, 1),
		MergePool::create(SampleMethod::Random, 3, 5,
		{
			AlchemyPoolTier2::create(),
			SmithingPoolTier2::create(),
			PotionPoolTier2::create()
		})
	})
{
}

ChestPoolURGeneric::~ChestPoolURGeneric()
{
}
