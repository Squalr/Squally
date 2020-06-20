#include "EquipmentPoolTier2.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

EquipmentPoolTier2* EquipmentPoolTier2::create(SampleMethod sampleMethod, int min, int max)
{
	EquipmentPoolTier2* instance = new EquipmentPoolTier2(sampleMethod, min, max);

	instance->autorelease();

	return instance;
}

EquipmentPoolTier2::EquipmentPoolTier2(SampleMethod sampleMethod, int min, int max) : super(ValueMap(), "equipment-pool-t2", sampleMethod, min, max)
{
	this->addItemToPool(ItemChance::create(OldShoe::create(), ItemChance::Probability::Uncommon));
	this->addItemToPool(ItemChance::create(BucketHelm::create(), ItemChance::Probability::Uncommon));
}

EquipmentPoolTier2::~EquipmentPoolTier2()
{
}
