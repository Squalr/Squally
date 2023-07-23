#include "ChestPoolLCGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/MergePool.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier5/AlchemyPoolTier5.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier5/SmithingPoolTier5.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier5/PotionPoolTier5.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string ChestPoolLCGeneric::PoolName = "lc-generic";

ChestPoolLCGeneric* ChestPoolLCGeneric::create(ValueMap& properties)
{
	ChestPoolLCGeneric* instance = new ChestPoolLCGeneric(properties);

	instance->autorelease();

	return instance;
}

ChestPoolLCGeneric::ChestPoolLCGeneric(ValueMap& properties) : super(
	properties, ChestPoolLCGeneric::PoolName, SampleMethod::Guarantee, 2, 3,
	{
		MergePool::create(SampleMethod::Random, 3, 5,
		{
			AlchemyPoolTier5::create(),
			SmithingPoolTier5::create(),
			PotionPoolTier5::create()
		})
	})
{
}

ChestPoolLCGeneric::~ChestPoolLCGeneric()
{
}
