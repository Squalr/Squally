#include "PocketPoolBPGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Inventory/MergePool.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier7/AlchemyPoolTier7.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier7/SmithingPoolTier7.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier7/PotionPoolTier7.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string PocketPoolBPGeneric::PoolName = "bp-generic";

PocketPoolBPGeneric* PocketPoolBPGeneric::create(ValueMap& properties)
{
	PocketPoolBPGeneric* instance = new PocketPoolBPGeneric(properties);

	instance->autorelease();

	return instance;
}

PocketPoolBPGeneric::PocketPoolBPGeneric(ValueMap& properties) : super(properties, PocketPoolBPGeneric::PoolName, SampleMethod::Guarantee, 1, 1,
	{
		MergePool::create(SampleMethod::Guarantee, 1, 2,
		{
			AlchemyPoolTier7::create(),
			SmithingPoolTier7::create(),
			// PotionPoolTier7::create()
		})
	})
{
}

PocketPoolBPGeneric::~PocketPoolBPGeneric()
{
}
