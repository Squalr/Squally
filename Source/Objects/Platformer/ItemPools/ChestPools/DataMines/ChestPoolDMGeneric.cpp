#include "ChestPoolDMGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/MergePool.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier3/AlchemyPoolTier3.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier3/CardPoolTier3.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier3/SmithingPoolTier3.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier3/PotionPoolTier3.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string ChestPoolDMGeneric::PoolName = "dm-generic";

ChestPoolDMGeneric* ChestPoolDMGeneric::create(ValueMap& properties)
{
	ChestPoolDMGeneric* instance = new ChestPoolDMGeneric(properties);

	instance->autorelease();

	return instance;
}

ChestPoolDMGeneric::ChestPoolDMGeneric(ValueMap& properties) : super(
	properties, ChestPoolDMGeneric::PoolName, SampleMethod::Guarantee, 2, 3,
	{
		CardPoolTier3::create(SampleMethod::Random, 1, 1),
		MergePool::create(SampleMethod::Random, 3, 5,
		{
			AlchemyPoolTier3::create(),
			SmithingPoolTier3::create(),
			PotionPoolTier3::create()
		})
	})
{
}

ChestPoolDMGeneric::~ChestPoolDMGeneric()
{
}
