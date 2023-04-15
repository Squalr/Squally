#include "SmithingPoolHellCrystal.h"

#include "cocos/base/CCValue.h"

#include "Engine/Inventory/ItemChance.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

using namespace cocos2d;

const std::string SmithingPoolHellCrystal::PoolName = "smithing-pool-hell-crystal";

SmithingPoolHellCrystal* SmithingPoolHellCrystal::create(ValueMap& properties)
{
	SmithingPoolHellCrystal* instance = new SmithingPoolHellCrystal(properties);

	instance->autorelease();

	return instance;
}

SmithingPoolHellCrystal::SmithingPoolHellCrystal(ValueMap& properties) : super(properties, SmithingPoolHellCrystal::PoolName, SampleMethod::Unbounded, 1, 1)
{
	// Allows for stability in item ordering
	this->toggleDisableShuffle(true);
	
	this->addItemToPool(ItemChance::create(HellCrystalPlans::create(), ItemChance::Probability::Guaranteed));
}

SmithingPoolHellCrystal::~SmithingPoolHellCrystal()
{
}
