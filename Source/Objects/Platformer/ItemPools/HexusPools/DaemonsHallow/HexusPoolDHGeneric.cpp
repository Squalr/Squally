#include "HexusPoolDHGeneric.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier6/AlchemyPoolTier6.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier6/CardPoolTier6.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier6/SmithingPoolTier6.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier6/PotionPoolTier6.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

HexusPoolDHGeneric* HexusPoolDHGeneric::create()
{
	HexusPoolDHGeneric* instance = new HexusPoolDHGeneric();

	instance->autorelease();

	return instance;
}

HexusPoolDHGeneric::HexusPoolDHGeneric() : super(ValueMap(), "hexus-pool-dh-generic", SampleMethod::Random, 1, 2,
	{ CardPoolTier6::create(SampleMethod::Guarantee, 1, 1), AlchemyPoolTier6::create(SampleMethod::Random, 1, 1), SmithingPoolTier6::create(SampleMethod::Random, 1, 2) })
{
}

HexusPoolDHGeneric::~HexusPoolDHGeneric()
{
}
