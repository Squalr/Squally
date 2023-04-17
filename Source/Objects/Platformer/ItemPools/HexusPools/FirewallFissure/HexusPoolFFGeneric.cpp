#include "HexusPoolFFGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Objects/Platformer/ItemPools/CurrencyPools/FirewallFissure/CurrencyPoolFFGeneric.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier6/AlchemyPoolTier6.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier6/CardPoolTier6.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier6/SmithingPoolTier6.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier6/PotionPoolTier6.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

HexusPoolFFGeneric* HexusPoolFFGeneric::create(ValueMap& properties)
{
	HexusPoolFFGeneric* instance = new HexusPoolFFGeneric(properties);

	instance->autorelease();

	return instance;
}

HexusPoolFFGeneric::HexusPoolFFGeneric(ValueMap& properties) : super(properties, "hexus-pool-ff-generic", SampleMethod::Random, 1, 2,
	{ AlchemyPoolTier6::create(SampleMethod::Random, 1, 1), SmithingPoolTier6::create(SampleMethod::Random, 1, 2) }, CurrencyPoolFFGeneric::create(properties))
{
}

HexusPoolFFGeneric::~HexusPoolFFGeneric()
{
}
