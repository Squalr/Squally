#include "ChestPoolEFSpecial.h"

#include "cocos/base/CCValue.h"

#include "Objects/Platformer/ItemPools/Tiered/Tier1/CardPoolTier1.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier1/CraftingPoolTier1.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier1/PotionPoolTier1.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier1/EquipmentPoolTier1.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string ChestPoolEFSpecial::PoolName = "ef-special";

ChestPoolEFSpecial* ChestPoolEFSpecial::create(ValueMap& properties)
{
	ChestPoolEFSpecial* instance = new ChestPoolEFSpecial(properties);

	instance->autorelease();

	return instance;
}

ChestPoolEFSpecial::ChestPoolEFSpecial(ValueMap& properties) : super(
	properties, ChestPoolEFSpecial::PoolName, SampleMethod::Guarantee, 1, 1,
	{ EquipmentPoolTier1::create(SampleMethod::Guarantee, 1, 1) })
{
}

ChestPoolEFSpecial::~ChestPoolEFSpecial()
{
}
