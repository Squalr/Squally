#include "AlchemyPoolTier3.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

AlchemyPoolTier3* AlchemyPoolTier3::create(SampleMethod sampleMethod, int min, int max)
{
	AlchemyPoolTier3* instance = new AlchemyPoolTier3(sampleMethod, min, max);

	instance->autorelease();

	return instance;
}

AlchemyPoolTier3::AlchemyPoolTier3(SampleMethod sampleMethod, int min, int max) : super(ValueMap(), "alchemy-pool-t3", sampleMethod, min, max)
{
	this->addItemToPool(ItemChance::create(DarkSeed::create(), ItemChance::Probability::VeryCommon));
	this->addItemToPool(ItemChance::create(SandRoot::create(), ItemChance::Probability::VeryCommon));

	// Phasing in
	this->addItemToPool(ItemChance::create(GoldWeed::create(), ItemChance::Probability::Reasonable));
	this->addItemToPool(ItemChance::create(RatTail::create(), ItemChance::Probability::Reasonable));

	// Phasing out
	this->addItemToPool(ItemChance::create(Honey::create(), ItemChance::Probability::Uncommon));
	this->addItemToPool(ItemChance::create(Acorn::create(), ItemChance::Probability::Uncommon));

	// Bomb phasing in
	this->addItemToPool(ItemChance::create(StrongChitin::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(GunpowderT3::create(), ItemChance::Probability::Common));

	// Bomb phasing out
	this->addItemToPool(ItemChance::create(WeakChitin::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(GunpowderT2::create(), ItemChance::Probability::Rare));
}

AlchemyPoolTier3::~AlchemyPoolTier3()
{
}
