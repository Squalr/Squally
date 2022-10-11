#include "HexusPoolLCGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Objects/Platformer/ItemPools/CurrencyPools/LambdaCrypts/CurrencyPoolLCGeneric.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier5/AlchemyPoolTier5.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier5/CardPoolTier5.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier5/SmithingPoolTier5.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier5/PotionPoolTier5.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

HexusPoolLCGeneric* HexusPoolLCGeneric::create(ValueMap& properties)
{
	HexusPoolLCGeneric* instance = new HexusPoolLCGeneric(properties);

	instance->autorelease();

	return instance;
}

HexusPoolLCGeneric::HexusPoolLCGeneric(ValueMap& properties) : super(properties, "hexus-pool-lc-generic", SampleMethod::Random, 1, 2,
	{ AlchemyPoolTier5::create(SampleMethod::Random, 1, 1), SmithingPoolTier5::create(SampleMethod::Random, 1, 2) }, CurrencyPoolLCGeneric::create(properties))
{
}

HexusPoolLCGeneric::~HexusPoolLCGeneric()
{
}
