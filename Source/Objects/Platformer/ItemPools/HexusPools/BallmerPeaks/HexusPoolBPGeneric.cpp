#include "HexusPoolBPGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier7/AlchemyPoolTier7.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier7/CardPoolTier7.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier7/SmithingPoolTier7.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier7/PotionPoolTier7.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

HexusPoolBPGeneric* HexusPoolBPGeneric::create()
{
	HexusPoolBPGeneric* instance = new HexusPoolBPGeneric();

	instance->autorelease();

	return instance;
}

HexusPoolBPGeneric::HexusPoolBPGeneric() : super(ValueMap(), "hexus-pool-bp-generic", SampleMethod::Random, 1, 2,
	{ CardPoolTier7::create(SampleMethod::Guarantee, 1, 1), AlchemyPoolTier7::create(SampleMethod::Random, 1, 1), SmithingPoolTier7::create(SampleMethod::Random, 1, 2) })
{
}

HexusPoolBPGeneric::~HexusPoolBPGeneric()
{
}
