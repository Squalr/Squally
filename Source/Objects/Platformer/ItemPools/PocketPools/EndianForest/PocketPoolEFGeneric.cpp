#include "PocketPoolEFGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Inventory/MergePool.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier1/AlchemyPoolTier1.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier1/CardPoolTier1.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier1/SmithingPoolTier1.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier1/PotionPoolTier1.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string PocketPoolEFGeneric::PoolName = "ef-generic";

PocketPoolEFGeneric* PocketPoolEFGeneric::create(ValueMap& properties)
{
	PocketPoolEFGeneric* instance = new PocketPoolEFGeneric(properties);

	instance->autorelease();

	return instance;
}

PocketPoolEFGeneric::PocketPoolEFGeneric(ValueMap& properties) : super(properties, PocketPoolEFGeneric::PoolName, SampleMethod::Guarantee, 1, 1,
	{
		CardPoolTier1::create(SampleMethod::Random, 1, 1),
		MergePool::create(SampleMethod::Guarantee, 1, 2,
		{
			AlchemyPoolTier1::create(),
			SmithingPoolTier1::create(),
			// PotionPoolTier1::create(),
		})
	})
{
}

PocketPoolEFGeneric::~PocketPoolEFGeneric()
{
}
