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
	this->addItemToPool(ItemChance::create(DarkSeed::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Clover::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Honey::create(), ItemChance::Probability::Reasonable));
	this->addItemToPool(ItemChance::create(Feather::create(), ItemChance::Probability::Reasonable));
}

AlchemyPoolTier3::~AlchemyPoolTier3()
{
}
