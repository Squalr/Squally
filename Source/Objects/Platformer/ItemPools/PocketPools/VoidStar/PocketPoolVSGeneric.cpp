#include "PocketPoolVSGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Inventory/MergePool.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier8/AlchemyPoolTier8.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier8/SmithingPoolTier8.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier8/PotionPoolTier8.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string PocketPoolVSGeneric::PoolName = "vs-generic";

PocketPoolVSGeneric* PocketPoolVSGeneric::create(ValueMap& properties)
{
	PocketPoolVSGeneric* instance = new PocketPoolVSGeneric(properties);

	instance->autorelease();

	return instance;
}

PocketPoolVSGeneric::PocketPoolVSGeneric(ValueMap& properties) : super(properties, PocketPoolVSGeneric::PoolName, SampleMethod::Guarantee, 1, 1,
	{
		MergePool::create(SampleMethod::Guarantee, 1, 2,
		{
			AlchemyPoolTier8::create(),
			SmithingPoolTier8::create(),
			// PotionPoolTier8::create()
		})
	})
{
}

PocketPoolVSGeneric::~PocketPoolVSGeneric()
{
}
