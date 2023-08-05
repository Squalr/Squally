#include "AlchemyPoolTier5.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

AlchemyPoolTier5* AlchemyPoolTier5::create(SampleMethod sampleMethod, int min, int max)
{
	AlchemyPoolTier5* instance = new AlchemyPoolTier5(sampleMethod, min, max);

	instance->autorelease();

	return instance;
}

AlchemyPoolTier5::AlchemyPoolTier5(SampleMethod sampleMethod, int min, int max) : super(ValueMap(), "alchemy-pool-t5", sampleMethod, min, max)
{
	this->addItemToPool(ItemChance::create(BlackMushroom::create(), ItemChance::Probability::VeryCommon));
	this->addItemToPool(ItemChance::create(Mandrake::create(), ItemChance::Probability::VeryCommon));

	// Phasing in
	this->addItemToPool(ItemChance::create(BlackBlood::create(), ItemChance::Probability::Rare));
	// this->addItemToPool(ItemChance::create(DemonRoot::create(), ItemChance::Probability::Rare)); // Excluded for lore

	// Phasing out
	this->addItemToPool(ItemChance::create(GoldWeed::create(), ItemChance::Probability::Uncommon));
	this->addItemToPool(ItemChance::create(RatTail::create(), ItemChance::Probability::Uncommon));

	// Bomb phasing in
	this->addItemToPool(ItemChance::create(Stinger::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(GunpowderT5::create(), ItemChance::Probability::Common));

	// Bomb phasing out
	this->addItemToPool(ItemChance::create(Pepper::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(GunpowderT4::create(), ItemChance::Probability::Rare));
}

AlchemyPoolTier5::~AlchemyPoolTier5()
{
}
