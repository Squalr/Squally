#include "HexusPoolLCGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Objects/Platformer/ItemPools/CurrencyPools/LambdaCrypts/CurrencyPoolLCHexus.h"
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

HexusPoolLCGeneric::HexusPoolLCGeneric(ValueMap& properties) : super(properties, "hexus-pool-lc-generic", SampleMethod::Guarantee, 2, 2,
	{ CardPoolTier5::create() }, CurrencyPoolLCHexus::create(properties))
{
}

HexusPoolLCGeneric::~HexusPoolLCGeneric()
{
}
