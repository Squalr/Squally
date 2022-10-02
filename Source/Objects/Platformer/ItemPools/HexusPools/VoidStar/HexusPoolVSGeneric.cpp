#include "HexusPoolVSGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Objects/Platformer/ItemPools/CurrencyPools/VoidStar/CurrencyPoolVSGeneric.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier8/AlchemyPoolTier8.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier8/CardPoolTier8.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier8/SmithingPoolTier8.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier8/PotionPoolTier8.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

HexusPoolVSGeneric* HexusPoolVSGeneric::create(ValueMap& properties)
{
	HexusPoolVSGeneric* instance = new HexusPoolVSGeneric(properties);

	instance->autorelease();

	return instance;
}

HexusPoolVSGeneric::HexusPoolVSGeneric(ValueMap& properties) : super(properties, "hexus-pool-vs-generic", SampleMethod::Random, 1, 2,
	{ AlchemyPoolTier8::create(SampleMethod::Random, 1, 1), SmithingPoolTier8::create(SampleMethod::Random, 1, 2) }, CurrencyPoolVSGeneric::create(properties))
{
}

HexusPoolVSGeneric::~HexusPoolVSGeneric()
{
}
