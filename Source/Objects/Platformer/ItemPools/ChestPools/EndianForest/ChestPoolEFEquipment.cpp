#include "ChestPoolEFEquipment.h"

#include "cocos/base/CCValue.h"

#include "Objects/Platformer/ItemPools/Tiered/Tier1/CardPoolTier1.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier1/CraftingPoolTier1.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier1/PotionPoolTier1.h"
#include "Objects/Platformer/ItemPools/Tiered/Tier1/EquipmentPoolTier1.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string ChestPoolEFEquipment::PoolName = "ef-equipment";

ChestPoolEFEquipment* ChestPoolEFEquipment::create(ValueMap& properties)
{
	ChestPoolEFEquipment* instance = new ChestPoolEFEquipment(properties);

	instance->autorelease();

	return instance;
}

ChestPoolEFEquipment::ChestPoolEFEquipment(ValueMap& properties) : super(
	properties, ChestPoolEFEquipment::PoolName, SampleMethod::Guarantee, 1, 1,
	{ EquipmentPoolTier1::create(SampleMethod::Guarantee, 1, 1) })
{
}

ChestPoolEFEquipment::~ChestPoolEFEquipment()
{
}
