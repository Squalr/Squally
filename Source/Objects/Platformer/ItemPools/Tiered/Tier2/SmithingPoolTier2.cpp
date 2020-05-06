#include "SmithingPoolTier2.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

SmithingPoolTier2* SmithingPoolTier2::create(SampleMethod sampleMethod, int min, int max)
{
	SmithingPoolTier2* instance = new SmithingPoolTier2(sampleMethod, min, max);

	instance->autorelease();

	return instance;
}

SmithingPoolTier2::SmithingPoolTier2(SampleMethod sampleMethod, int min, int max) : super(ValueMap(), "smithing-pool-t2", sampleMethod, min, max)
{
	this->addItemToPool(ItemChance::create(Wood::create(), ItemChance::Probability::Common));
	this->addItemToPool(ItemChance::create(Coal::create(), ItemChance::Probability::Reasonable));
	this->addItemToPool(ItemChance::create(Copper::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Quartz::create(), ItemChance::Probability::Epic));
}

SmithingPoolTier2::~SmithingPoolTier2()
{
}
