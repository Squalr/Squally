#include "AlchemyPoolTier1.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

AlchemyPoolTier1* AlchemyPoolTier1::create(SampleMethod sampleMethod, int min, int max)
{
	AlchemyPoolTier1* instance = new AlchemyPoolTier1(sampleMethod, min, max);

	instance->autorelease();

	return instance;
}

AlchemyPoolTier1::AlchemyPoolTier1(SampleMethod sampleMethod, int min, int max) : super(ValueMap(), "alchemy-pool-t1", sampleMethod, min, max)
{
	this->addItemToPool(ItemChance::create(DarkSeed::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Clover::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Honey::create(), ItemChance::Probability::Reasonable));
	this->addItemToPool(ItemChance::create(Feather::create(), ItemChance::Probability::Reasonable));
}

AlchemyPoolTier1::~AlchemyPoolTier1()
{
}
