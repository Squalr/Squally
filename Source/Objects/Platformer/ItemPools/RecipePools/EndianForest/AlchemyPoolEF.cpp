#include "AlchemyPoolEF.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string AlchemyPoolEF::PoolName = "alchemy-pool-ef";

AlchemyPoolEF* AlchemyPoolEF::create(ValueMap& properties)
{
	AlchemyPoolEF* instance = new AlchemyPoolEF(properties);

	instance->autorelease();

	return instance;
}

AlchemyPoolEF::AlchemyPoolEF(ValueMap& properties) : super(properties, AlchemyPoolEF::PoolName, SampleMethod::Unbounded, 1, 1)
{
	this->addItemToPool(ItemChance::create(CopperToQuartzPlans::create(), ItemChance::Probability::Guaranteed));
}

AlchemyPoolEF::~AlchemyPoolEF()
{
}
