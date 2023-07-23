#include "ChestPoolCVGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/MergePool.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier4/AlchemyPoolTier4.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier4/SmithingPoolTier4.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier4/PotionPoolTier4.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string ChestPoolCVGeneric::PoolName = "cv-generic";

ChestPoolCVGeneric* ChestPoolCVGeneric::create(ValueMap& properties)
{
	ChestPoolCVGeneric* instance = new ChestPoolCVGeneric(properties);

	instance->autorelease();

	return instance;
}

ChestPoolCVGeneric::ChestPoolCVGeneric(ValueMap& properties) : super(
	properties, ChestPoolCVGeneric::PoolName, SampleMethod::Guarantee, 2, 3,
	{
		MergePool::create(SampleMethod::Random, 3, 5,
		{
			AlchemyPoolTier4::create(),
			SmithingPoolTier4::create(),
			PotionPoolTier4::create()
		})
	})
{
}

ChestPoolCVGeneric::~ChestPoolCVGeneric()
{
}
