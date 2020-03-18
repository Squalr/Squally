#include "WeaponPoolTier1.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

WeaponPoolTier1* WeaponPoolTier1::create(SampleMethod sampleMethod, int min, int max)
{
	WeaponPoolTier1* instance = new WeaponPoolTier1(sampleMethod, min, max);

	instance->autorelease();

	return instance;
}

WeaponPoolTier1::WeaponPoolTier1(SampleMethod sampleMethod, int min, int max) : super(ValueMap(), "weapon-pool-t1", sampleMethod, min, max)
{
	this->addItemToPool(ItemChance::create(WoodenRapier::create(), ItemChance::Probability::Uncommon));
	this->addItemToPool(ItemChance::create(WoodenAxe::create(), ItemChance::Probability::Uncommon));
	this->addItemToPool(ItemChance::create(WoodenClub::create(), ItemChance::Probability::Uncommon));
	this->addItemToPool(ItemChance::create(WoodenWand::create(), ItemChance::Probability::Uncommon));
	
	this->addItemToPool(ItemChance::create(CopperSword::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(CopperAxe::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(CopperMallet::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(QuartzWand::create(), ItemChance::Probability::Epic));
}

WeaponPoolTier1::~WeaponPoolTier1()
{
}
