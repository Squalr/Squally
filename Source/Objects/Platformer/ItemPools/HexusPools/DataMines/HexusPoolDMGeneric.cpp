#include "HexusPoolDMGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Objects/Platformer/ItemPools/CurrencyPools/DataMines/CurrencyPoolDMHexus.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier3/AlchemyPoolTier3.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier3/CardPoolTier3.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier3/SmithingPoolTier3.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier3/PotionPoolTier3.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

HexusPoolDMGeneric* HexusPoolDMGeneric::create(ValueMap& properties)
{
	HexusPoolDMGeneric* instance = new HexusPoolDMGeneric(properties);

	instance->autorelease();

	return instance;
}

HexusPoolDMGeneric::HexusPoolDMGeneric(ValueMap& properties) : super(properties, "hexus-pool-dm-generic", SampleMethod::Guarantee, 2, 2,
	{ CardPoolTier3::create() }, CurrencyPoolDMHexus::create(properties))
{
}

HexusPoolDMGeneric::~HexusPoolDMGeneric()
{
}
