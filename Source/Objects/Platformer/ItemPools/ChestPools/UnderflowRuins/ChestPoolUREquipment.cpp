#include "ChestPoolUREquipment.h"

#include "cocos/base/CCValue.h"

#include "Objects/Platformer/ItemPools/Tiered/Tier2/EquipmentPoolTier2.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string ChestPoolUREquipment::PoolName = "ur-equipment";

ChestPoolUREquipment* ChestPoolUREquipment::create(ValueMap& properties)
{
	ChestPoolUREquipment* instance = new ChestPoolUREquipment(properties);

	instance->autorelease();

	return instance;
}

ChestPoolUREquipment::ChestPoolUREquipment(ValueMap& properties) : super(
	properties, ChestPoolUREquipment::PoolName, SampleMethod::Guarantee, 1, 1,
	{
		EquipmentPoolTier2::create(SampleMethod::Guarantee, 1, 1)
	})
{
}

ChestPoolUREquipment::~ChestPoolUREquipment()
{
}
