#include "WeaponPoolTier2.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

WeaponPoolTier2* WeaponPoolTier2::create(SampleMethod sampleMethod, int min, int max)
{
	WeaponPoolTier2* instance = new WeaponPoolTier2(sampleMethod, min, max);

	instance->autorelease();

	return instance;
}

WeaponPoolTier2::WeaponPoolTier2(SampleMethod sampleMethod, int min, int max) : super(ValueMap(), "weapon-pool-t2", sampleMethod, min, max)
{
	this->addItemToPool(ItemChance::create(WoodenSword::create(), ItemChance::Probability::Uncommon));
	this->addItemToPool(ItemChance::create(WoodenAxe::create(), ItemChance::Probability::Uncommon));
	this->addItemToPool(ItemChance::create(WoodenClub::create(), ItemChance::Probability::Uncommon));
	this->addItemToPool(ItemChance::create(WoodenWand::create(), ItemChance::Probability::Uncommon));
	
	this->addItemToPool(ItemChance::create(CopperSword::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(CopperAxe::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(CopperMallet::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(QuartzWand::create(), ItemChance::Probability::Epic));
}

WeaponPoolTier2::~WeaponPoolTier2()
{
}
