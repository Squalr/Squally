#include "AlchemyPoolTier6.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

AlchemyPoolTier6* AlchemyPoolTier6::create(SampleMethod sampleMethod, int min, int max)
{
	AlchemyPoolTier6* instance = new AlchemyPoolTier6(sampleMethod, min, max);

	instance->autorelease();

	return instance;
}

AlchemyPoolTier6::AlchemyPoolTier6(SampleMethod sampleMethod, int min, int max) : super(ValueMap(), "alchemy-pool-t6", sampleMethod, min, max)
{
	this->addItemToPool(ItemChance::create(BlackBlood::create(), ItemChance::Probability::VeryCommon));
	this->addItemToPool(ItemChance::create(DemonRoot::create(), ItemChance::Probability::VeryCommon));

	// Phasing in
	// this->addItemToPool(ItemChance::create(FrostBerries::create(), ItemChance::Probability::Rare)); // Excluded for lore
	// this->addItemToPool(ItemChance::create(Snowball::create(), ItemChance::Probability::Rare)); // Excluded for lore

	// Phasing out
	this->addItemToPool(ItemChance::create(BlackMushroom::create(), ItemChance::Probability::Uncommon));
	this->addItemToPool(ItemChance::create(Mandrake::create(), ItemChance::Probability::Uncommon));

	// Bomb phasing in
	this->addItemToPool(ItemChance::create(PhoenixFeather::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(GunpowderT6::create(), ItemChance::Probability::Common));

	// Bomb phasing out
	this->addItemToPool(ItemChance::create(Stinger::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(GunpowderT5::create(), ItemChance::Probability::Rare));
}

AlchemyPoolTier6::~AlchemyPoolTier6()
{
}
