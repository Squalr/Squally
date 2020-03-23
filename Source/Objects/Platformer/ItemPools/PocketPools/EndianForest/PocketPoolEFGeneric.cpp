#include "PocketPoolEFGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/ItemChance.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier1/AlchemyPoolT1.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier1/CardPoolTier1.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier1/SmithingPoolT1.h"
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
	{ CardPoolTier1::create(SampleMethod::Random, 0, 1), AlchemyPoolT1::create(SampleMethod::Random, 1, 2), SmithingPoolT1::create(SampleMethod::Guarantee, 1, 1), PotionPoolTier1::create(SampleMethod::Random, 0, 1) })
{
}

PocketPoolEFGeneric::~PocketPoolEFGeneric()
{
}
