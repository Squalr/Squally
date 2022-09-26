#include "AlchemyPoolTier8.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

AlchemyPoolTier8* AlchemyPoolTier8::create(SampleMethod sampleMethod, int min, int max)
{
	AlchemyPoolTier8* instance = new AlchemyPoolTier8(sampleMethod, min, max);

	instance->autorelease();

	return instance;
}

AlchemyPoolTier8::AlchemyPoolTier8(SampleMethod sampleMethod, int min, int max) : super(ValueMap(), "alchemy-pool-t8", sampleMethod, min, max)
{
	this->addItemToPool(ItemChance::create(DarkSeed::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Clover::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Honey::create(), ItemChance::Probability::Reasonable));
	this->addItemToPool(ItemChance::create(Feather::create(), ItemChance::Probability::Reasonable));
}

AlchemyPoolTier8::~AlchemyPoolTier8()
{
}
