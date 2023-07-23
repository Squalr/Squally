#include "SmithingPoolDemonHeart.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string SmithingPoolDemonHeart::PoolName = "smithing-pool-demon-heart";

SmithingPoolDemonHeart* SmithingPoolDemonHeart::create(ValueMap& properties)
{
	SmithingPoolDemonHeart* instance = new SmithingPoolDemonHeart(properties);

	instance->autorelease();

	return instance;
}

SmithingPoolDemonHeart::SmithingPoolDemonHeart(ValueMap& properties) : super(properties, SmithingPoolDemonHeart::PoolName, SampleMethod::Unbounded, 1, 1)
{
	// Allows for stability in item ordering
	this->toggleDisableShuffle(true);
	
	this->addItemToPool(ItemChance::create(DemonHeartPlans::create(), ItemChance::Probability::Guaranteed));
}

SmithingPoolDemonHeart::~SmithingPoolDemonHeart()
{
}
