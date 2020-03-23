#include "SmithingPoolT1.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

SmithingPoolT1* SmithingPoolT1::create(SampleMethod sampleMethod, int min, int max)
{
	SmithingPoolT1* instance = new SmithingPoolT1(sampleMethod, min, max);

	instance->autorelease();

	return instance;
}

SmithingPoolT1::SmithingPoolT1(SampleMethod sampleMethod, int min, int max) : super(ValueMap(), "smithing-pool-t1", sampleMethod, min, max)
{
	this->addItemToPool(ItemChance::create(Wood::create(), ItemChance::Probability::VeryCommon));
	this->addItemToPool(ItemChance::create(Coal::create(), ItemChance::Probability::Reasonable));
	this->addItemToPool(ItemChance::create(Copper::create(), ItemChance::Probability::Rare));
	this->addItemToPool(ItemChance::create(Tin::create(), ItemChance::Probability::Epic));
	this->addItemToPool(ItemChance::create(Quartz::create(), ItemChance::Probability::Epic));
}

SmithingPoolT1::~SmithingPoolT1()
{
}
