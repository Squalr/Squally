#include "EquipmentPoolTier1.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

EquipmentPoolTier1* EquipmentPoolTier1::create(SampleMethod sampleMethod, int min, int max)
{
	EquipmentPoolTier1* instance = new EquipmentPoolTier1(sampleMethod, min, max);

	instance->autorelease();

	return instance;
}

EquipmentPoolTier1::EquipmentPoolTier1(SampleMethod sampleMethod, int min, int max) : super(ValueMap(), "equipment-pool-t1", sampleMethod, min, max)
{
	this->addItemToPool(ItemChance::create(OldShoe::create(), ItemChance::Probability::Uncommon));
	this->addItemToPool(ItemChance::create(BucketHelm::create(), ItemChance::Probability::Uncommon));
}

EquipmentPoolTier1::~EquipmentPoolTier1()
{
}
