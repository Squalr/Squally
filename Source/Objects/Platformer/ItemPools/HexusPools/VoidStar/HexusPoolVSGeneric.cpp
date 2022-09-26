#include "HexusPoolVSGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier8/AlchemyPoolTier8.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier8/CardPoolTier8.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier8/SmithingPoolTier8.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier8/PotionPoolTier8.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

HexusPoolVSGeneric* HexusPoolVSGeneric::create()
{
	HexusPoolVSGeneric* instance = new HexusPoolVSGeneric();

	instance->autorelease();

	return instance;
}

HexusPoolVSGeneric::HexusPoolVSGeneric() : super(ValueMap(), "hexus-pool-vs-generic", SampleMethod::Random, 1, 2,
	{ CardPoolTier8::create(SampleMethod::Guarantee, 1, 1), AlchemyPoolTier8::create(SampleMethod::Random, 1, 1), SmithingPoolTier8::create(SampleMethod::Random, 1, 2) })
{
}

HexusPoolVSGeneric::~HexusPoolVSGeneric()
{
}
