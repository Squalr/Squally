#include "PocketPoolURGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Inventory/MergePool.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier2/AlchemyPoolTier2.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier2/CardPoolTier2.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier2/SmithingPoolTier2.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier2/PotionPoolTier2.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string PocketPoolURGeneric::PoolName = "ur-generic";

PocketPoolURGeneric* PocketPoolURGeneric::create(ValueMap& properties)
{
	PocketPoolURGeneric* instance = new PocketPoolURGeneric(properties);

	instance->autorelease();

	return instance;
}

PocketPoolURGeneric::PocketPoolURGeneric(ValueMap& properties) : super(properties, PocketPoolURGeneric::PoolName, SampleMethod::Guarantee, 1, 1,
	{
		CardPoolTier2::create(SampleMethod::Random, 1, 1),
		MergePool::create(SampleMethod::Guarantee, 1, 2,
		{
			AlchemyPoolTier2::create(),
			SmithingPoolTier2::create(),
			PotionPoolTier2::create()
		})
	})
{
}

PocketPoolURGeneric::~PocketPoolURGeneric()
{
}
