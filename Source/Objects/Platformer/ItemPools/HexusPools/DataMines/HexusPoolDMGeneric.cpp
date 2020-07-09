#include "HexusPoolDMGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier3/AlchemyPoolTier3.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier3/CardPoolTier3.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier3/SmithingPoolTier3.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier3/PotionPoolTier3.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

HexusPoolDMGeneric* HexusPoolDMGeneric::create()
{
	HexusPoolDMGeneric* instance = new HexusPoolDMGeneric();

	instance->autorelease();

	return instance;
}

HexusPoolDMGeneric::HexusPoolDMGeneric() : super(ValueMap(), "hexus-pool-dm-generic", SampleMethod::Random, 1, 2,
	{ CardPoolTier3::create(SampleMethod::Guarantee, 1, 1), AlchemyPoolTier3::create(SampleMethod::Random, 1, 1), SmithingPoolTier3::create(SampleMethod::Random, 1, 2) })
{
}

HexusPoolDMGeneric::~HexusPoolDMGeneric()
{
}
