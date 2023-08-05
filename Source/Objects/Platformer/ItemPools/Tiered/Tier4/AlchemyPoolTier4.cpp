#include "AlchemyPoolTier4.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

AlchemyPoolTier4* AlchemyPoolTier4::create(SampleMethod sampleMethod, int min, int max)
{
	AlchemyPoolTier4* instance = new AlchemyPoolTier4(sampleMethod, min, max);

	instance->autorelease();

	return instance;
}

AlchemyPoolTier4::AlchemyPoolTier4(SampleMethod sampleMethod, int min, int max) : super(ValueMap(), "alchemy-pool-t4", sampleMethod, min, max)
{
	this->addItemToPool(ItemChance::create(GoldWeed::create(), ItemChance::Probability::VeryCommon));
	this->addItemToPool(ItemChance::create(RatTail::create(), ItemChance::Probability::VeryCommon));

	// Phasing in
	this->addItemToPool(ItemChance::create(BlackMushroom::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Mandrake::create(), ItemChance::Probability::Rare));

	// Phasing out
	this->addItemToPool(ItemChance::create(DarkSeed::create(), ItemChance::Probability::Uncommon));
	this->addItemToPool(ItemChance::create(SandRoot::create(), ItemChance::Probability::Uncommon));

	// Bomb phasing in
	this->addItemToPool(ItemChance::create(Pepper::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(GunpowderT4::create(), ItemChance::Probability::Common));

	// Bomb phasing out
	this->addItemToPool(ItemChance::create(StrongChitin::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(GunpowderT3::create(), ItemChance::Probability::Rare));
}

AlchemyPoolTier4::~AlchemyPoolTier4()
{
}
