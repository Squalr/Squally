#include "HexusPoolURGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Objects/Platformer/ItemPools/CurrencyPools/UnderflowRuins/CurrencyPoolURGeneric.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier2/AlchemyPoolTier2.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier2/CardPoolTier2.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier2/SmithingPoolTier2.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier2/PotionPoolTier2.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

HexusPoolURGeneric* HexusPoolURGeneric::create(ValueMap& properties)
{
	HexusPoolURGeneric* instance = new HexusPoolURGeneric(properties);

	instance->autorelease();

	return instance;
}

HexusPoolURGeneric::HexusPoolURGeneric(ValueMap& properties) : super(properties, "hexus-pool-ur-generic", SampleMethod::Random, 1, 2,
	{ AlchemyPoolTier2::create(SampleMethod::Random, 1, 1), SmithingPoolTier2::create(SampleMethod::Random, 1, 2) }, CurrencyPoolURGeneric::create(properties))
{
}

HexusPoolURGeneric::~HexusPoolURGeneric()
{
}
