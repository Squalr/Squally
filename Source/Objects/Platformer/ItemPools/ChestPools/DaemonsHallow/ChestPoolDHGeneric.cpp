#include "ChestPoolDHGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/MergePool.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier6/AlchemyPoolTier6.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier6/CardPoolTier6.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier6/SmithingPoolTier6.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier6/PotionPoolTier6.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string ChestPoolDHGeneric::PoolName = "dh-generic";

ChestPoolDHGeneric* ChestPoolDHGeneric::create(ValueMap& properties)
{
	ChestPoolDHGeneric* instance = new ChestPoolDHGeneric(properties);

	instance->autorelease();

	return instance;
}

ChestPoolDHGeneric::ChestPoolDHGeneric(ValueMap& properties) : super(
	properties, ChestPoolDHGeneric::PoolName, SampleMethod::Guarantee, 2, 3,
	{
		CardPoolTier6::create(SampleMethod::Random, 1, 1),
		MergePool::create(SampleMethod::Random, 3, 5,
		{
			AlchemyPoolTier6::create(),
			SmithingPoolTier6::create(),
			PotionPoolTier6::create()
		})
	})
{
}

ChestPoolDHGeneric::~ChestPoolDHGeneric()
{
}
