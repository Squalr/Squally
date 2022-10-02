#include "HexusPoolDHGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Objects/Platformer/ItemPools/CurrencyPools/DaemonsHallow/CurrencyPoolDHGeneric.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier6/AlchemyPoolTier6.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier6/CardPoolTier6.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier6/SmithingPoolTier6.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier6/PotionPoolTier6.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

HexusPoolDHGeneric* HexusPoolDHGeneric::create(ValueMap& properties)
{
	HexusPoolDHGeneric* instance = new HexusPoolDHGeneric(properties);

	instance->autorelease();

	return instance;
}

HexusPoolDHGeneric::HexusPoolDHGeneric(ValueMap& properties) : super(properties, "hexus-pool-dh-generic", SampleMethod::Random, 1, 2,
	{ AlchemyPoolTier6::create(SampleMethod::Random, 1, 1), SmithingPoolTier6::create(SampleMethod::Random, 1, 2) }, CurrencyPoolDHGeneric::create(properties))
{
}

HexusPoolDHGeneric::~HexusPoolDHGeneric()
{
}
