#include "AlchemyPoolTier7.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

AlchemyPoolTier7* AlchemyPoolTier7::create(SampleMethod sampleMethod, int min, int max)
{
	AlchemyPoolTier7* instance = new AlchemyPoolTier7(sampleMethod, min, max);

	instance->autorelease();

	return instance;
}

AlchemyPoolTier7::AlchemyPoolTier7(SampleMethod sampleMethod, int min, int max) : super(ValueMap(), "alchemy-pool-t7", sampleMethod, min, max)
{
	this->addItemToPool(ItemChance::create(FrostBerries::create(), ItemChance::Probability::VeryCommon));
	this->addItemToPool(ItemChance::create(Snowball::create(), ItemChance::Probability::VeryCommon));

	// Phasing in
	// this->addItemToPool(ItemChance::create(VoidFlower::create(), ItemChance::Probability::Rare)); // Excluded for lore

	// Phasing out
	this->addItemToPool(ItemChance::create(BlackBlood::create(), ItemChance::Probability::Uncommon));
	this->addItemToPool(ItemChance::create(DemonRoot::create(), ItemChance::Probability::Uncommon));

	// Bomb phasing in
	this->addItemToPool(ItemChance::create(Meteorite::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(GunpowderT7::create(), ItemChance::Probability::Common));

	// Bomb phasing out
	this->addItemToPool(ItemChance::create(PhoenixFeather::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(GunpowderT6::create(), ItemChance::Probability::Rare));
}

AlchemyPoolTier7::~AlchemyPoolTier7()
{
}
