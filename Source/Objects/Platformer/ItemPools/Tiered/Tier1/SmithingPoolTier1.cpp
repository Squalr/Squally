#include "SmithingPoolTier1.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

SmithingPoolTier1* SmithingPoolTier1::create(SampleMethod sampleMethod, int min, int max)
{
	SmithingPoolTier1* instance = new SmithingPoolTier1(sampleMethod, min, max);

	instance->autorelease();

	return instance;
}

SmithingPoolTier1::SmithingPoolTier1(SampleMethod sampleMethod, int min, int max) : super(ValueMap(), "smithing-pool-t1", sampleMethod, min, max)
{
	// Misc
	this->addItemToPool(ItemChance::create(Wood::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Coal::create(), ItemChance::Probability::Common));

	// Metals
	this->addItemToPool(ItemChance::create(Copper::create(), ItemChance::Probability::Rare));

	// Gems
	this->addItemToPool(ItemChance::create(Quartz::create(), ItemChance::Probability::Epic));
}

SmithingPoolTier1::~SmithingPoolTier1()
{
}
