#include "AlchemyPoolTier2.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

AlchemyPoolTier2* AlchemyPoolTier2::create(SampleMethod sampleMethod, int min, int max)
{
	AlchemyPoolTier2* instance = new AlchemyPoolTier2(sampleMethod, min, max);

	instance->autorelease();

	return instance;
}

AlchemyPoolTier2::AlchemyPoolTier2(SampleMethod sampleMethod, int min, int max) : super(ValueMap(), "alchemy-pool-t2", sampleMethod, min, max)
{
	this->addItemToPool(ItemChance::create(Honey::create(), ItemChance::Probability::VeryCommon));
	this->addItemToPool(ItemChance::create(Acorn::create(), ItemChance::Probability::VeryCommon));

	// Phasing in
	this->addItemToPool(ItemChance::create(DarkSeed::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(SandRoot::create(), ItemChance::Probability::Rare));

	// Phasing out
	this->addItemToPool(ItemChance::create(Clover::create(), ItemChance::Probability::Uncommon));
	this->addItemToPool(ItemChance::create(Feather::create(), ItemChance::Probability::Uncommon));

	// Bomb
	this->addItemToPool(ItemChance::create(WeakChitin::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(StrongChitin::create(), ItemChance::Probability::Rare));
}

AlchemyPoolTier2::~AlchemyPoolTier2()
{
}
