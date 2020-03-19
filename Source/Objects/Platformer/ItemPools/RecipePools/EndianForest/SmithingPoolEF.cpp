#include "SmithingPoolEF.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string SmithingPoolEF::PoolName = "smithing-pool-ef";

SmithingPoolEF* SmithingPoolEF::create(ValueMap& properties)
{
	SmithingPoolEF* instance = new SmithingPoolEF(properties);

	instance->autorelease();

	return instance;
}

SmithingPoolEF::SmithingPoolEF(ValueMap& properties) : super(properties, SmithingPoolEF::PoolName, SampleMethod::Unbounded, 1, 1)
{
	this->addItemToPool(ItemChance::create(WoodenSwordPlans::create(), ItemChance::Probability::Guaranteed));
}

SmithingPoolEF::~SmithingPoolEF()
{
}
