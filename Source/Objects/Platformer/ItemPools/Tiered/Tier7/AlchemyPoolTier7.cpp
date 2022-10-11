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
	this->addItemToPool(ItemChance::create(DarkSeed::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Clover::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Honey::create(), ItemChance::Probability::Reasonable));
	this->addItemToPool(ItemChance::create(Feather::create(), ItemChance::Probability::Reasonable));
}

AlchemyPoolTier7::~AlchemyPoolTier7()
{
}
