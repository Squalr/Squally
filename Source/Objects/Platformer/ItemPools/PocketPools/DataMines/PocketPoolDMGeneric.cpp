#include "PocketPoolDMGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Inventory/MergePool.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier3/AlchemyPoolTier3.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier3/CardPoolTier3.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier3/SmithingPoolTier3.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier3/PotionPoolTier3.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string PocketPoolDMGeneric::PoolName = "dm-generic";

PocketPoolDMGeneric* PocketPoolDMGeneric::create(ValueMap& properties)
{
	PocketPoolDMGeneric* instance = new PocketPoolDMGeneric(properties);

	instance->autorelease();

	return instance;
}

PocketPoolDMGeneric::PocketPoolDMGeneric(ValueMap& properties) : super(properties, PocketPoolDMGeneric::PoolName, SampleMethod::Guarantee, 1, 1,
	{
		CardPoolTier3::create(SampleMethod::Random, 1, 1),
		MergePool::create(SampleMethod::Guarantee, 1, 2,
		{
			AlchemyPoolTier3::create(),
			SmithingPoolTier3::create(),
			// PotionPoolTier3::create()
		})
	})
{
}

PocketPoolDMGeneric::~PocketPoolDMGeneric()
{
}
