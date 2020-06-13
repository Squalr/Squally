#include "HexusPoolURGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier2/AlchemyPoolTier2.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier2/CardPoolTier2.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier2/SmithingPoolTier2.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier2/PotionPoolTier2.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

HexusPoolURGeneric* HexusPoolURGeneric::create()
{
	HexusPoolURGeneric* instance = new HexusPoolURGeneric();

	instance->autorelease();

	return instance;
}

HexusPoolURGeneric::HexusPoolURGeneric() : super(ValueMap(), "hexus-pool-ur-generic", SampleMethod::Random, 1, 2,
	{ CardPoolTier2::create(SampleMethod::Guarantee, 1, 1), AlchemyPoolTier2::create(SampleMethod::Random, 1, 1), SmithingPoolTier2::create(SampleMethod::Random, 1, 2) })
{
}

HexusPoolURGeneric::~HexusPoolURGeneric()
{
}
