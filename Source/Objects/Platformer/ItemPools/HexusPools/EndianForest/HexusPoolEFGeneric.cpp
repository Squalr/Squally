#include "HexusPoolEFGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Objects/Platformer/ItemPools/CurrencyPools/EndianForest/CurrencyPoolEFHexus.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier1/AlchemyPoolTier1.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier1/CardPoolTier1.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier1/SmithingPoolTier1.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier1/PotionPoolTier1.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

HexusPoolEFGeneric* HexusPoolEFGeneric::create(ValueMap& properties)
{
	HexusPoolEFGeneric* instance = new HexusPoolEFGeneric(properties);

	instance->autorelease();

	return instance;
}

HexusPoolEFGeneric::HexusPoolEFGeneric(ValueMap& properties) : super(properties, "hexus-pool-ef-generic", SampleMethod::Guarantee, 2, 2,
	{ CardPoolTier1::create() }, CurrencyPoolEFHexus::create(properties))
{
}

HexusPoolEFGeneric::~HexusPoolEFGeneric()
{
}
