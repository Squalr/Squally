#include "HexusPoolBPGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Objects/Platformer/ItemPools/CurrencyPools/BallmerPeaks/CurrencyPoolBPGeneric.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier7/AlchemyPoolTier7.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier7/CardPoolTier7.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier7/SmithingPoolTier7.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier7/PotionPoolTier7.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

HexusPoolBPGeneric* HexusPoolBPGeneric::create(ValueMap& properties)
{
	HexusPoolBPGeneric* instance = new HexusPoolBPGeneric(properties);

	instance->autorelease();

	return instance;
}

HexusPoolBPGeneric::HexusPoolBPGeneric(ValueMap& properties) : super(properties, "hexus-pool-bp-generic", SampleMethod::Random, 1, 2,
	{ AlchemyPoolTier7::create(SampleMethod::Random, 1, 1), SmithingPoolTier7::create(SampleMethod::Random, 1, 2) }, CurrencyPoolBPGeneric::create(properties))
{
}

HexusPoolBPGeneric::~HexusPoolBPGeneric()
{
}
