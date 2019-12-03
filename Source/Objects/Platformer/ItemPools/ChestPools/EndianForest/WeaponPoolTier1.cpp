#include "WeaponPoolTier1.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

WeaponPoolTier1* WeaponPoolTier1::create(SampleMethod sampleMethod)
{
	WeaponPoolTier1* instance = new WeaponPoolTier1(sampleMethod);

	instance->autorelease();

	return instance;
}

WeaponPoolTier1::WeaponPoolTier1(SampleMethod sampleMethod) : super(ValueMap(), "weapon-pool-t1", sampleMethod, 1, 1)
{
	this->addItemToPool(ItemChance::create(WoodenMallet::create(), ItemChance::Probability::Uncommon));
	this->addItemToPool(ItemChance::create(WoodCutter::create(), ItemChance::Probability::Uncommon));
	this->addItemToPool(ItemChance::create(WoodenWand::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(CompositeBow::create(), ItemChance::Probability::Legendary));
}

WeaponPoolTier1::~WeaponPoolTier1()
{
}
