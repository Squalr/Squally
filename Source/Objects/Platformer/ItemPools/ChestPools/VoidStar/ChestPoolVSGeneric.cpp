#include "ChestPoolVSGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/MergePool.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier8/AlchemyPoolTier8.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier8/CardPoolTier8.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier8/SmithingPoolTier8.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier8/PotionPoolTier8.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string ChestPoolVSGeneric::PoolName = "vs-generic";

ChestPoolVSGeneric* ChestPoolVSGeneric::create(ValueMap& properties)
{
	ChestPoolVSGeneric* instance = new ChestPoolVSGeneric(properties);

	instance->autorelease();

	return instance;
}

ChestPoolVSGeneric::ChestPoolVSGeneric(ValueMap& properties) : super(
	properties, ChestPoolVSGeneric::PoolName, SampleMethod::Guarantee, 2, 3,
	{
		CardPoolTier8::create(SampleMethod::Random, 1, 1),
		MergePool::create(SampleMethod::Random, 3, 5,
		{
			AlchemyPoolTier8::create(),
			SmithingPoolTier8::create(),
			PotionPoolTier8::create()
		})
	})
{
}

ChestPoolVSGeneric::~ChestPoolVSGeneric()
{
}
