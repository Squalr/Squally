#include "PocketPoolCVGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Inventory/MergePool.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier4/AlchemyPoolTier4.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier4/SmithingPoolTier4.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier4/PotionPoolTier4.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string PocketPoolCVGeneric::PoolName = "cv-generic";

PocketPoolCVGeneric* PocketPoolCVGeneric::create(ValueMap& properties)
{
	PocketPoolCVGeneric* instance = new PocketPoolCVGeneric(properties);

	instance->autorelease();

	return instance;
}

PocketPoolCVGeneric::PocketPoolCVGeneric(ValueMap& properties) : super(properties, PocketPoolCVGeneric::PoolName, SampleMethod::Guarantee, 1, 1,
	{
		MergePool::create(SampleMethod::Guarantee, 1, 2,
		{
			AlchemyPoolTier4::create(),
			SmithingPoolTier4::create(),
			// PotionPoolTier4::create()
		})
	})
{
}

PocketPoolCVGeneric::~PocketPoolCVGeneric()
{
}
