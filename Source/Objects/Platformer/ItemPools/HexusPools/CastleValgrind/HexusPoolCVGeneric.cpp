#include "HexusPoolCVGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Objects/Platformer/ItemPools/CurrencyPools/CastleValgrind/CurrencyPoolCVHexus.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier4/AlchemyPoolTier4.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier4/CardPoolTier4.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier4/SmithingPoolTier4.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier4/PotionPoolTier4.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

HexusPoolCVGeneric* HexusPoolCVGeneric::create(ValueMap& properties)
{
	HexusPoolCVGeneric* instance = new HexusPoolCVGeneric(properties);

	instance->autorelease();

	return instance;
}

HexusPoolCVGeneric::HexusPoolCVGeneric(ValueMap& properties) : super(properties, "hexus-pool-cv-generic", SampleMethod::Guarantee, 2, 2,
	{ CardPoolTier4::create() }, CurrencyPoolCVHexus::create(properties))
{
}

HexusPoolCVGeneric::~HexusPoolCVGeneric()
{
}
