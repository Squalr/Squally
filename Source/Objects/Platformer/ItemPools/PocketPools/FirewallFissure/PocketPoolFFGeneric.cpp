#include "PocketPoolFFGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Inventory/MergePool.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier6/AlchemyPoolTier6.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier6/SmithingPoolTier6.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier6/PotionPoolTier6.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string PocketPoolFFGeneric::PoolName = "ff-generic";

PocketPoolFFGeneric* PocketPoolFFGeneric::create(ValueMap& properties)
{
	PocketPoolFFGeneric* instance = new PocketPoolFFGeneric(properties);

	instance->autorelease();

	return instance;
}

PocketPoolFFGeneric::PocketPoolFFGeneric(ValueMap& properties) : super(properties, PocketPoolFFGeneric::PoolName, SampleMethod::Guarantee, 1, 1,
	{
		MergePool::create(SampleMethod::Guarantee, 1, 2,
		{
			AlchemyPoolTier6::create(),
			SmithingPoolTier6::create(),
			// PotionPoolTier6::create()
		})
	})
{
}

PocketPoolFFGeneric::~PocketPoolFFGeneric()
{
}
