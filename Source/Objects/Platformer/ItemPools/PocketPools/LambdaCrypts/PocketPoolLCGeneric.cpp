#include "PocketPoolLCGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Inventory/MergePool.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier5/AlchemyPoolTier5.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier5/SmithingPoolTier5.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier5/PotionPoolTier5.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string PocketPoolLCGeneric::PoolName = "lc-generic";

PocketPoolLCGeneric* PocketPoolLCGeneric::create(ValueMap& properties)
{
	PocketPoolLCGeneric* instance = new PocketPoolLCGeneric(properties);

	instance->autorelease();

	return instance;
}

PocketPoolLCGeneric::PocketPoolLCGeneric(ValueMap& properties) : super(properties, PocketPoolLCGeneric::PoolName, SampleMethod::Guarantee, 1, 1,
	{
		MergePool::create(SampleMethod::Guarantee, 1, 2,
		{
			AlchemyPoolTier5::create(),
			SmithingPoolTier5::create(),
			// PotionPoolTier5::create()
		})
	})
{
}

PocketPoolLCGeneric::~PocketPoolLCGeneric()
{
}
